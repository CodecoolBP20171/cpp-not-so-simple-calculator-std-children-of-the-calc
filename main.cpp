#include "Tester.hpp"

namespace {
    void printHelp(){
        std::cout << "To get to this help screen type 'help'." << std::endl;
        std::cout << "To quit this !!!awesome!!! program type 'exit'." << std::endl;
        std::cout << "To run automated tests type 'test'." << std::endl;
        std::cout << "Other inputs will be treated as mathematical expressions and will be evaluated." << std::endl;
    }
}

int main(){
    Tester t;
    Calculator c;
    bool running = true;
    std::cout << "NoSoSiCalc (for help type 'help')" << std::endl;
    do{
        std::cout << "$> ";
        std::string input;
        getline(std::cin, input);
        if(input == "exit") running = false;
        else if(input == "help") printHelp();
        else if (input == "test") t.run();
        else std::cout << c.evaluate(input) << std::endl;
    } while(running);
    std::cout << "Thanks, Goodbye!" << std::endl;
    return 0;
}