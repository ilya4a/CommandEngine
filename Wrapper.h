#ifndef LAB2_WRAPPER_H
#define LAB2_WRAPPER_H

#include <string>
#include <map>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <functional>
#include <type_traits>
#include "traits.h"

class Wrapper {

public:

    template<typename C, typename MemFn>
    Wrapper(C* obj, MemFn mem, std::initializer_list<std::pair<std::string,int>> params) {
        using traits = function_traits<MemFn>;
        using R = typename traits::return_type;
        using ArgsTuple = typename traits::args_tuple;
        constexpr std::size_t N = traits::arity;

        for (auto &p : params) {
            param_names_.push_back(p.first);
            defaults_[p.first] = p.second;
        }

        if (param_names_.size() != N) {
            throw std::runtime_error("Wrapper ctor: number of parameter names differs from method arity");
        }

        static_assert(all_int<std::tuple_element_t<0, ArgsTuple>>::value || N==0,
                      "first parameter type is not int (but simplified task assumes all params are int)");

        check_all_args_are_int<ArgsTuple>();

        call_ = [obj, mem, names=param_names_, defs=defaults_](const std::map<std::string,int>& args_map) -> std::string {
            std::vector<int> vals;
            vals.reserve(names.size());
            for (const auto &n : names) {
                auto it = args_map.find(n);
                if (it != args_map.end()) vals.push_back(it->second);
                else {
                    auto d_it = defs.find(n);
                    if (d_it != defs.end()) vals.push_back(d_it->second);
                    else throw std::runtime_error("Missing argument and no default: " + n);
                }
            }
            return call_invoke<R>(obj, mem, vals);
        };
    }

    std::string invoke(const std::map<std::string,int>& args) const {
        return call_(args);
    }

private:
    std::vector<std::string> param_names_;
    std::unordered_map<std::string,int> defaults_;
    std::function<std::string(const std::map<std::string,int>&)> call_;

    template<typename Tuple>
    static void check_all_args_are_int() {
        constexpr std::size_t N = std::tuple_size<Tuple>::value;
        if constexpr (N > 0) check_all_args_are_int_impl<Tuple>(std::make_index_sequence<N>{});
    }

    template<typename Tuple, std::size_t... I>
    static void check_all_args_are_int_impl(std::index_sequence<I...>) {
        bool ok = (true && ... && (std::is_same<std::decay_t<std::tuple_element_t<I, Tuple>>, int>::value));
        if (!ok) {
            throw std::runtime_error("Wrapper: not all parameter types are int (task simplification expects ints)");
        }
    }

    template<typename R, typename C, typename MemFn, std::size_t... I>
    static std::string call_invoke_impl(C* obj, MemFn mem, const std::vector<int>& vals, std::index_sequence<I...>) {
        if constexpr (std::is_void<R>::value) {
            ( (obj->*mem)( (vals[I])... ) );
            return std::string{};
        } else {
            R res = ( (obj->*mem)( (vals[I])... ) );
            return to_string_any<R>(res);
        }
    }


    template<typename R, typename C, typename MemFn>
    static std::string call_invoke(C* obj, MemFn mem, const std::vector<int>& vals) {
        using traits = function_traits<MemFn>;
        constexpr std::size_t N = traits::arity;
        if (vals.size() != N) throw std::runtime_error("Wrong number of arguments provided at call");
        return call_invoke_impl<R, C, MemFn>(obj, mem, vals, std::make_index_sequence<N>{});
    }
};

#endif //LAB2_WRAPPER_H
