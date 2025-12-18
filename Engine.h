//
// Created by ilya on 12/18/25.
//

#ifndef LAB2_ENGINE_H
#define LAB2_ENGINE_H


#include <string>
#include <functional>
#include <map>
#include <stdexcept>
#include "Wrapper.h"

class Engine {
public:
    void register_command(Wrapper* w, const std::string& name);
    std::string execute(const std::string& name, const std::map<std::string,int>& args);

private:
    std::unordered_map<std::string, std::function<std::string(const std::map<std::string,int>&)>> commands_;
};


#endif //LAB2_ENGINE_H
