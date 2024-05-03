#ifndef PROJECTTITLE_LOGGER_H
#define PROJECTTITLE_LOGGER_H

#include <iostream>
#include "Job.h"
#include "Printer.h"

class Logger {
public:
    static void logJobCompletion(Job* job, Printer* printer, int pageCount);
};

#endif //PROJECTTITLE_LOGGER_H