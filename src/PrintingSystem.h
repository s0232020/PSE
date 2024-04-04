#ifndef PROJECTTITLE_PRINTINGSYSTEM_H
#define PROJECTTITLE_PRINTINGSYSTEM_H
#include "Printer.h"
#include <iostream>
#include <vector>

const char* getLoadErrorMessage(LoadError error);

class PrintingSystem{
public:
    LoadError loadFromFile(const std::string& filename);
    bool generateStatusReport(const std::string& filename) const;
    void processJob(const std::string& jobName);

    int getPrinterCount() const
    { // Keep count of how many printers there are
        REQUIRE (printers_.size() >= 0, "Invalid printer count");
        return printers_.size();
    }

    int getJobCount() const
    { // Keep count of how many jobs there are
        REQUIRE (jobs_.size() >= 0, "Invalid job count");
        return jobs_.size();
    }

    void addPrinter(Printer &printer)
    {
        //REQUIRE (printer.getName() != "", "Invalid printer name");
        printers_.emplace_back(printer);
        //ENSURE (printers_.back().getName() == printer.getName(), "Printer name not added correctly");
    }

    void addJob(Job &job)
    {
        //REQUIRE (job.getUserName() != "", "Invalid user name");
        jobs_.emplace_back(job);
        Printer::addJobToPrinter(job);
        //ENSURE (jobs_.back().getUserName() == job.getUserName(), "User name not added correctly");
    }

    std::vector<Printer> getPrinters() const
    {
        REQUIRE (printers_.size() >= 0, "Invalid printer count");
        return printers_;
    };

    std::vector<Job> getJobs() const
    {
        REQUIRE (jobs_.size() >= 0, "Invalid job count");
        return jobs_;
    }

private:
    std::vector<Printer> printers_;
    std::vector<Job> jobs_;

};
#endif //PROJECTTITLE_PRINTINGSYSTEM_H
