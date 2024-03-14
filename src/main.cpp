#include "Include.h"

int main() {
    PrintingSystem system;
    system.loadFromFile("valid.xml");
    std::cout << system.generateStatusReport("valid_output.txt") << std::endl;
    system.processJob(system.printers_.front().getName());
    return 0;
}