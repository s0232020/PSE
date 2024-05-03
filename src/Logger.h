#ifndef PROJECTTITLE_LOGGER_H
#define PROJECTTITLE_LOGGER_H

#include <iostream>
#include "Job.h"
#include "Printer.h"
#include "PrintingSystem.h"
#include <fstream>

class Logger {
public:
    static void logJobCompletion(Job* job, Printer* printer, int pageCount);
    static void logGenerateStatusReport(std::ofstream* outputFile, PrintingSystem* system);
};

#endif //PROJECTTITLE_LOGGER_H