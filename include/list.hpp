#pragma once

#include <initializer_list>
#include "object.hpp"

namespace wiremap{
    template<typename T, std::size_t Size>
    struct List: public detail::Container<std::array<T, Size>>{
        static_assert(detail::is_wiremap_object_v<T>, "List value type not derived from detail::ObjectBase");

        List()noexcept: detail::Container<std::array<T, Size>>(){
            this->_size = Size;
        }

        template<typename ArrT, typename = std::enable_if_t<std::is_convertible_v<ArrT, T>>>
        List(const std::array<ArrT,Size>& arr)noexcept: List(){
            for(unsigned i = 0; i < this->_size; i++){
                this->_internal[i] = arr[i];
            }
        }

        template<typename ListT, typename = std::enable_if_t<std::is_convertible_v<ListT, T>>>
        List(const std::initializer_list<ListT>& list)noexcept: List(){
            assert(list.size() == Size); //TODO std::initializer_list does not have compile-time size access
            std::copy(list.begin(), list.end(), this->_internal.begin());
        }

        ~List() = default;

        constexpr const T& operator[](const std::size_t& pos)const noexcept{
            assert(pos >= 0 && pos < this->_size);
            return this->_internal[pos];
        }

        constexpr T& operator[](const std::size_t& pos)noexcept{
            assert(pos >= 0 && pos < this->_size);
            return this->_internal[pos];
        }

        constexpr typename std::array<T, Size>::iterator begin()noexcept{
            return this->_internal.begin();
        }

        constexpr typename std::array<T, Size>::const_iterator begin()const noexcept{
            return this->_internal.begin();
        }

        constexpr typename std::array<T, Size>::const_iterator cbegin()const noexcept{
            return this->_internal.cbegin();
        }

        constexpr typename std::array<T, Size>::iterator end()noexcept{
            return this->_internal.end();
        }

        constexpr typename std::array<T, Size>::const_iterator end()const noexcept{
            return this->_internal.end();
        }

        constexpr typename std::array<T, Size>::const_iterator cend()const noexcept{
            return this->_internal.cend();
        }
    };

    namespace detail{
        template<typename T>
        struct is_list_specialization: public std::false_type{};

        template<typename T, std::size_t Size>
        struct is_list_specialization<List<T, Size>>: public std::true_type{};
    }
}
