//
// Created by ilya on 12/18/25.
//

#include "Engine.h"


void Engine::register_command(Wrapper* w, const std::string& name){
    commands_[name] = [w](const std::map<std::string,int>& args) {
        return w->invoke(args);
    };
}


std::string Engine::execute(const std::string& name, const std::map<std::string,int>& args){
    auto it = commands_.find(name);
    if (it == commands_.end()) throw std::runtime_error("command not found: " + name);
    return it->second(args);
}

