//
// Created by miguel on 10/10/17.
//
#ifndef ENABLE_IF_98
#define ENABLE_IF_98

namespace std
{
    template<bool Condition, typename T = void>
    struct enable_if {typedef T type;};

    template<typename T>
    struct enable_if<true,T> {typedef T type;};

}
#endif