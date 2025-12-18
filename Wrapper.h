#ifndef LAB2_WRAPPER_H
#define LAB2_WRAPPER_H

#include <string>
#include <map>

class Wrapper {
public:
    using ArgMap = std::map<std::string,int>;

    Wrapper() = default;

    Wrapper(const ArgMap& defaults)
            : defaults_(defaults)
    {}

    std::string invoke(const ArgMap& args) const {
        int sum = 0;
        if (!defaults_.empty()) {
            for (const auto& kv : defaults_) {
                const std::string& name = kv.first;
                int value = kv.second;
                auto it = args.find(name);
                if (it != args.end()) value = it->second;
                sum += value;
            }
        } else {
            for (const auto& kv : args) sum += kv.second;
        }
        return std::to_string(sum);
    }

    const ArgMap& defaults() const { return defaults_; }

private:
    ArgMap defaults_;
};

#endif //LAB2_WRAPPER_H
