#include "PrintingSystem.h"

int main() {
    PrintingSystem system;
    std::cout << "Loading from file: valid.xml" << std::endl;
    system.loadFromFile("valid.xml");
    Printer printer = system.getPrinters().front();
    system.getJobs();
    printer.getJobQueue();
    for (Job job : printer.getJobQueue()) {
        std::cout << job.getJobNumber() << " " << job.getUserName() << " " << job.getPageCount() << std::endl;
    }
    std::cout << "Generating status report: valid_output.txt" << std::endl;
    system.generateStatusReport("valid_output.txt");
    std::cout << printer.getName() << " " << printer.getEmissions() << " " << printer.getSpeed() << std::endl;
    std::cout << "Processing job: Office_Printer5" << std::endl;
    system.processJob("Office_Printer5");
    return 0;
}