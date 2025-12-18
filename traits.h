//
// Created by ilya on 12/18/25.
//

#ifndef LAB2_TRAITS_H
#define LAB2_TRAITS_H

#include <tuple>
#include <cstddef>
#include <ostream>
#include <sstream>

template<typename T> struct function_traits;

template<typename R, typename C, typename... Args>
struct function_traits<R(C::*)(Args...)> {
    using return_type = R;
    using class_type = C;
    using args_tuple = std::tuple<Args...>;
    static constexpr std::size_t arity = sizeof...(Args);
};

template<typename R, typename C, typename... Args>
struct function_traits<R(C::*)(Args...) const> {
    using return_type = R;
    using class_type = C;
    using args_tuple = std::tuple<Args...>;
    static constexpr std::size_t arity = sizeof...(Args);
};


template<typename... Ts>
struct all_int;

template<>
struct all_int<> : std::true_type {};

template<typename T, typename... Ts>
struct all_int<T, Ts...> : std::conditional_t<std::is_same<std::decay_t<T>, int>::value, all_int<Ts...>, std::false_type> {};

template<typename T, typename = void>
struct is_streamable : std::false_type {};

template<typename T>
struct is_streamable<T, std::void_t<decltype(std::declval<std::ostream&>() << std::declval<T>())>> : std::true_type {};

template<typename T>
std::string to_string_any(const T& v) {
    if constexpr (std::is_same_v<T, void>) {
        return std::string{};
    } else if constexpr (is_streamable<T>::value) {
        std::ostringstream ss;
        ss << v;
        return ss.str();
    } else {
        return std::string("<non-printable-return-type>");
    }
}

#endif //LAB2_TRAITS_H
