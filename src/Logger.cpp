#include "Logger.h"

void Logger::logJobCompletion(Job* job, Printer* printer, int pageCount) {
    std::cout << "Printer \"" << printer->getName() << "\" finished " << printer->getType() << " job:\n";
    std::cout << "Number: " << job->getJobNumber() << "\n";
    std::cout << "Submitted by \"" << job->getUserName() << "\"\n";
    std::cout << pageCount << " pages\n";
    std::cout << "CO2 emissions: " << printer->getCO2Emissions() << "\n\n";
}

void Logger::logGenerateStatusReport(std::ofstream* outputFile, PrintingSystem* system)
{
    // Print header
    *outputFile << "# === [System Status] === #\n\n";

    // Print device information
    *outputFile << "--== Devices ==--\n";
    for (const Printer* printer : system->getPrinters())
    {
        *outputFile << printer->getName() << ":\n";
        *outputFile << "* CO2: " << printer->getEmissions() << "g/page\n";
        *outputFile << "* Pages per minute: " << printer->getSpeed() << "\n";
        *outputFile << "* Type: " << printer->getType() << "\n";
        *outputFile << "* Cost per page: " << printer->getCostPerPage() << " cents\n\n";
    }

    // Print job information
    *outputFile << "--== Jobs ==--\n";
    for (Printer* printer : system->getPrinters())
    {
        for (Job* job : printer->getJobQueue())
        {
            *outputFile << "[Job #" << job->getJobNumber() << "]\n";
            *outputFile << "* Owner: " << job->getUserName() << std::endl;
            *outputFile << "* Device: " << printer->getName() << std::endl;
            *outputFile << "* Status: " << printer->getStatus(job) << std::endl;
            *outputFile << "* Total pages: " << job->getTotalPages() << std::endl;
            *outputFile << "* Total CO2: " << printer->calculateCO2(job) << "g CO2\n";
            *outputFile << "Total cost: " << printer->calculateCost(job) << "\n\n";
        }
    }

    // Close output file
    *outputFile << "# ======================= #\n";
}
