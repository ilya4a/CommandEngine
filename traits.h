//
// Created by ilya on 12/18/25.
//

#ifndef LAB2_TRAITS_H
#define LAB2_TRAITS_H

#include <tuple>
#include <cstddef>

template<typename T> struct function_traits;

// non-const function
template<typename R, typename C, typename... Args>
struct function_traits<R(C::*)(Args...)> {
    using return_type = R;
    using class_type = C;
    using args_tuple = std::tuple<Args...>;
    static constexpr std::size_t arity = sizeof...(Args);
};

// const function
template<typename R, typename C, typename... Args>
struct function_traits<R(C::*)(Args...) const> {
    using return_type = R;
    using class_type = C;
    using args_tuple = std::tuple<Args...>;
    static constexpr std::size_t arity = sizeof...(Args);
};

#endif //LAB2_TRAITS_H
