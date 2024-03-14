#include "Include.h"

int main() {
    PrintingSystem system;
    system.loadFromFile("valid.xml");
    std::cout << system.getJobCount() << std::endl;
    std::cout << system.getPrinterCount() << std::endl;
    for (const Printer& printer : system.printers_) {
        std::cout << printer.getName() << std::endl;
    }
    return 0;
}