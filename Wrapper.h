//
// Created by ilya on 12/18/25.
//

#ifndef LAB2_WRAPPER_H
#define LAB2_WRAPPER_H

#include <string>
#include <map>
#include <unordered_map>

class Wrapper {
public:
    using ArgMap = std::map<std::string,int>;

    Wrapper() = default;

    Wrapper(const ArgMap& defaults)
            : defaults_(defaults)
    {}

    std::string invoke(const ArgMap& /*args*/) const {
        return std::string{};
    }

    const ArgMap& defaults() const { return defaults_; }

private:
    ArgMap defaults_;
};


#endif //LAB2_WRAPPER_H
