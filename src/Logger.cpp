#include "Logger.h"

void Logger::logJobCompletion(Job* job, Printer* printer, int pageCount) {
    std::cout << "Printer \"" << printer->getName() << "\" finished " << printer->getType() << " job:\n";
    std::cout << "Number: " << job->getJobNumber() << "\n";
    std::cout << "Submitted by \"" << job->getUserName() << "\"\n";
    std::cout << pageCount << " pages\n";
    std::cout << "CO2 emissions: " << printer->getCO2Emissions() << "\n\n";
}
