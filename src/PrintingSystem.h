#ifndef PROJECTTITLE_PRINTINGSYSTEM_H
#define PROJECTTITLE_PRINTINGSYSTEM_H
#include "Include.h"
#include "Printer.h"

class PrintingSystem{
public:
    LoadError loadFromFile(const std::string& filename);
    bool generateStatusReport(const std::string& filename) const;
    void processJob(const std::string& jobName);

    int getPrinterCount() const { // Keep count of how many printers there are
        return printers_.size();
    }

    int getJobCount() const { // Keep count of how many jobs there are
        return jobs_.size();
    }

    void addPrinter(Printer &printer) {
        printers_.emplace_back(printer);
    }

    void addJob(Job &job) {
        jobs_.emplace_back(job);
    }

    std::vector<Printer> getPrinters() const {
        return printers_;
    };

    std::vector<Job> getJobs() const {
        return jobs_;
    }

private:
    std::vector<Printer> printers_;
    std::vector<Job> jobs_;

};
#endif //PROJECTTITLE_PRINTINGSYSTEM_H
