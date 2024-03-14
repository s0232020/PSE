#include "Include.h"

int main() {
    PrintingSystem system;
    LoadError error = system.loadFromFile("missing_job_number.xml");
    std::string errorMessage = system.getLoadErrorMessage(error);
    std::cout << errorMessage << std::endl;
    std::cout << system.getJobCount() << std::endl;
    std::cout << system.getPrinterCount() << std::endl;
    for (const Printer& printer : system.printers_) {
        std::cout << printer.getName() << std::endl;
    }
    return 0;
}