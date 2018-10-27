#pragma once

namespace wiremap{
    struct Function{}; //TODO

    bool operator==(const Function&,const Function&){
        return true;
    }

    bool operator!=(const Function& A,const Function& B){
        return !(A == B);
    }
}
