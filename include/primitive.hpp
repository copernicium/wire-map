#pragma once

#include <cassert>
#include <iostream>
#include "util.hpp"
#include "parameter.hpp"

namespace wiremap{
    namespace attributes{
        template<typename T, typename... AttributeChecks>
        struct Attribute{
            static void verify(T&){}
        };

        template<typename T, typename First, typename... AttributeChecks>
        struct Attribute<T, First, AttributeChecks...>{
            static void verify(T& v){
                First::verify(v);
                Attribute<T, AttributeChecks...>::verify(v);
            }
        };
    }

    namespace detail{
        struct ObjectBase{
            virtual ~ObjectBase() = default;
        };

        template<typename T>
        inline constexpr bool is_wiremap_primitive_v = std::is_base_of_v<detail::ObjectBase,T>;

        template<typename T, auto DefaultValue,  typename... Attributes> // TODO should default value be part of the type definition?
        struct Primitive: public ObjectBase, public Attributes...{
            static_assert(std::is_convertible_v<decltype(DefaultValue),T>, "Default value different than value type");

            using value_type = T;

        protected:
            T value;
            T default_value;
            bool valid;

        public:
            Primitive(const T& v, const T& default_v)noexcept: value(v), default_value(default_v),valid(true){
                attributes::Attribute<T,Attributes...>::verify(value);
                attributes::Attribute<T,Attributes...>::verify(default_value);
            }

            Primitive(const T& v)noexcept: Primitive(v, DefaultValue){}

			Primitive(const std::shared_ptr<ParameterBase>& parameter){
				if(parameter == nullptr){
					assert(0);
				}
				std::shared_ptr<Parameter<Primitive<T, DefaultValue, Attributes...>>> inner = std::dynamic_pointer_cast<Parameter<Primitive<T, DefaultValue, Attributes...>>>(parameter);
				if(inner == nullptr){
					assert(0);
				}
				value = inner->get().value;
				default_value = inner->get().default_value;
				valid = inner->get().valid;
			}

			Primitive(const Primitive<T, DefaultValue, Attributes...>& OTHER)noexcept: value(OTHER.value), default_value(OTHER.default_value), valid(OTHER.valid){}

			Primitive<T, DefaultValue, Attributes...> operator=(const Primitive<T, DefaultValue, Attributes...>& OTHER){
				if(&OTHER == this){
					return *this;
				}
				value = OTHER.value;
				default_value = OTHER.default_value;
				valid = OTHER.valid;
				return *this;
			}

            Primitive()noexcept: default_value(DefaultValue),valid(false){}

            constexpr const T& getDefault()const noexcept{
                return default_value;
            }

            constexpr const T& require()const noexcept{
                if(valid){
                    return value;
                }
                return default_value;
            }

            constexpr const T& get()const noexcept{
                assert(valid);
                return value;
            }

            constexpr T& get()noexcept{
                assert(valid);
                return value;
            }

            constexpr operator bool()const noexcept{
                return valid;
            }

            Primitive<T, DefaultValue, Attributes...>& operator+=(const Primitive<T, DefaultValue, Attributes...>& B){
                assert(default_value == B.default_value);
                if(!valid || !B.valid){
                    valid = false;
                    return *this;
                }
                value = value + B.value;
                return *this;
            }

            template<typename OpT, auto OpDefaultValue, typename... OpAttributes>
                friend Primitive<OpT, OpDefaultValue, OpAttributes...> operator+(Primitive<OpT, OpDefaultValue, OpAttributes...>, const Primitive<OpT, OpDefaultValue, OpAttributes...>&);

            Primitive<T, DefaultValue, Attributes...>& operator-=(const Primitive<T, DefaultValue, Attributes...>& B){
                assert(default_value == B.default_value);
                if(!valid || !B.valid){
                    valid = false;
                    return *this;
                }
                value = value - B.value;
                return *this;
            }

            template<typename OpT, auto OpDefaultValue, typename... OpAttributes>
				friend Primitive<OpT, OpDefaultValue, OpAttributes...> operator-(Primitive<OpT, OpDefaultValue, OpAttributes...>, const Primitive<OpT, OpDefaultValue, OpAttributes...>&);

            Primitive<T, DefaultValue, Attributes...>& operator*=(const Primitive<T, DefaultValue, Attributes...>& B){
                assert(default_value == B.default_value);
                if(!valid || !B.valid){
                    valid = false;
                    return *this;
                }
                value = value * B.value;
                return *this;
            }

			template<typename OpT, auto OpDefaultValue, typename... OpAttributes>
                friend Primitive<OpT, OpDefaultValue, OpAttributes...> operator*(Primitive<OpT, OpDefaultValue, OpAttributes...>, const Primitive<OpT, OpDefaultValue, OpAttributes...>&);

            Primitive<T, DefaultValue, Attributes...>& operator/=(const Primitive<T, DefaultValue, Attributes...>& B){
                assert(default_value == B.default_value);
                if(!valid || !B.valid){
                    valid = false;
                    return *this;
                }
                value = value / B.value;
                return *this;
            }

            template<typename OpT, auto OpDefaultValue, typename... OpAttributes>
                friend Primitive<OpT, OpDefaultValue, OpAttributes...> operator/(Primitive<OpT, OpDefaultValue, OpAttributes...>, const Primitive<OpT, OpDefaultValue, OpAttributes...>&);

            bool operator==(const Primitive<T,DefaultValue,Attributes...>& B)const{
                if(default_value != B.default_value){
                    return false;
                }
                if(valid != B.valid){
                    return false;
                }
                if(valid && value != B.value){
                    return false;
                }
                return true;
            }

            bool operator!=(const Primitive<T,DefaultValue,Attributes...>& B)const{
                return !(*this == B);
            }
        };

        template<typename T, auto DefaultValue, typename... Attributes>
        Primitive<T, DefaultValue, Attributes...> operator+(Primitive<T, DefaultValue, Attributes...> a, const Primitive<T, DefaultValue, Attributes...>& B){
			a += B;
			return a;
        }

        template<typename T, auto DefaultValue, typename... Attributes>
        Primitive<T, DefaultValue, Attributes...> operator-(Primitive<T, DefaultValue, Attributes...> a, const Primitive<T, DefaultValue, Attributes...>& B){
			a -= B;
			return a;
        }

        template<typename T, auto DefaultValue, typename... Attributes>
        Primitive<T, DefaultValue, Attributes...> operator*(Primitive<T, DefaultValue, Attributes...> a, const Primitive<T, DefaultValue, Attributes...>& B){
			a *= B;
			return a;
        }

        template<typename T, auto DefaultValue, typename... Attributes>
        Primitive<T, DefaultValue, Attributes...> operator/(Primitive<T, DefaultValue, Attributes...> a, const Primitive<T, DefaultValue, Attributes...>& B){
			a /= B;
			return a;
        }

        template<typename T>
        struct is_object_specialization: public std::false_type{};

        template<typename T, auto D, typename... Attributes>
        struct is_object_specialization<Primitive<T, D, Attributes...>>: public std::true_type{};
    }

    namespace attributes{
        template<typename T>
        struct Integral{
            static_assert(std::is_integral_v<T>, "Integral defined with non-integral type");
            static constexpr void verify(T&)noexcept{}
        };

        template<typename T,auto DefaultValue, decltype(DefaultValue) Min, decltype(DefaultValue) Max>
        struct InRange{
            static_assert(Min <= Max);
            static_assert(Min <= DefaultValue && DefaultValue <= Max);

            static constexpr void verify(T& value)noexcept{
                if(value < Min){
                    std::cerr<<"Verification of object with attribute InRange [Min = "<<Min<<" and Max = "<<Max<<"] failed. Value was set to out of range value "<<value<<"; clipped to "<<Min<<"\n";
                    value = Min;
                } else if(value > Max){
                    std::cerr<<"Verification of object with attribute InRange [Min = "<<Min<<" and Max = "<<Max<<"] failed. Value was set to out of range value "<<value<<"; clipped to "<<Max<<"\n";
                    value = Max;
                }
            }
        };
    }
}
