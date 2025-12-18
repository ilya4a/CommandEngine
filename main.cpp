#include <iostream>
#include "Engine.h"

struct Subject {
    int f3(int a, int b) { return a + b; }

    void f_void(int x) {
        std::cout << "f_void called with " << x << "\n";
    }

    std::string f_string(int x) const {
        return std::string("val:") + std::to_string(x);
    }
};

//PR

int main() {
    Subject subj;

    Wrapper wrapper(&subj, &Subject::f3, {{"arg1", 0},
                                          {"arg2", 0}});

    Engine engine;
    engine.register_command(&wrapper, "command1");

    std::cout << engine.execute("command1", {{"arg1", 4},
                                             {"arg2", 5}}) << std::endl; // prints "9"

    // void
    Wrapper w_void(&subj, &Subject::f_void, {{"x", 0}});
    engine.register_command(&w_void, "voidcmd");
    std::cout << "[" << engine.execute("voidcmd", {{"x", 42}}) << "]"
              << std::endl; // prints f_void called...

    // const method with string return
    Wrapper w_str(&subj, static_cast<std::string(Subject::*)(int) const>(&Subject::f_string), {{"x", 7}});
    engine.register_command(&w_str, "s");
    std::cout << engine.execute("s", {{"x", 100}}) << std::endl; // prints "val:100"

    return 0;
}