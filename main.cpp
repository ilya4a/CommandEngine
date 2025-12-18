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

int main() {
    Subject subj;

    Engine engine;

    Wrapper::ArgMap defaults = { {"arg1", 0}, {"arg2", 0} };
    Wrapper* w = new Wrapper(defaults);

    engine.register_command(w, "command1");

    std::cout << engine.execute("command1", { {"arg1", 4}, {"arg2", 5} }) << std::endl;

    delete w;
    return 0;
}
