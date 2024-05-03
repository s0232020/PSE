#ifndef PROJECTTITLE_PRINTINGSYSTEM_H
#define PROJECTTITLE_PRINTINGSYSTEM_H
#include "Printer.h"
#include "ClimateCompensationInitiative.h"
#include <iostream>
#include <vector>
#include <algorithm>

const char* getLoadErrorMessage(LoadError error);
class Printer;
class PrintingSystem{
public:
    LoadError loadFromFile(const std::string& filename);
    bool generateStatusReport(const std::string &filename);
    void processJob(const std::string &printerName);
    void addJobsToPrinters(PrintingSystem &system);
    void processAutomatically(PrintingSystem& system);

    int getPrinterCount() const
    {
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
        #ifndef TESTING
        REQUIRE (printer.getName() != "", "Invalid printer name");
        #endif
        printers_.emplace_back(printer);
        #ifndef TESTING
        ENSURE (printers_.back().getName() == printer.getName(), "Printer name not added correctly");
        #endif
    }

    void addJob(Job &job)
    {
        #ifndef TESTING
        REQUIRE (job.getUserName() != "", "Invalid user name");
        #endif
        jobs_.emplace_back(job);
        #ifndef TESTING
        ENSURE (jobs_.back().getUserName() == job.getUserName(), "User name not added correctly");
        #endif
    }



    std::vector<Printer>& getPrinters()
    {
        REQUIRE (printers_.size() > 0, "Invalid printer count");
        return printers_;
    };

    std::vector<Job>& getJobs()
    {
#ifndef TESTING
        REQUIRE (jobs_.size() > 0, "Invalid job count");
#endif
        return jobs_;
    };

    std::vector<ClimateCompensationInitiative> getClimateCompensationInitiatives() const
    {
        REQUIRE (climateCompensationInitiatives_.size() >= 0, "Invalid climate compensation initiative count");
        return climateCompensationInitiatives_;
    }

    std::vector<ClimateCompensationInitiative>setClimateCompensationInitiatives()
    {
        REQUIRE (climateCompensationInitiatives_.size() >= 0, "Invalid climate compensation initiative count");
        return climateCompensationInitiatives_;
    }

    void addClimateCompensationInitiative(ClimateCompensationInitiative &initiative)
    {
        climateCompensationInitiatives_.emplace_back(initiative);
    }

    void deleteJob(int jobNumber)
    {
        REQUIRE (jobNumber >= 0, "Invalid job number");
        // Find the job with the specified job number
        auto it = std::find_if(jobs_.begin(), jobs_.end(), [jobNumber](const Job& job) {
            return job.getJobNumber() == jobNumber;
        });

        // If the job was found, delete it
        if (it != jobs_.end()) {
            jobs_.erase(it);
        }
    }

    void deletePrinter(const std::string &printerName)
    {
        REQUIRE (printerName != "", "Invalid printer name");
        // Find the printer with the specified name
        auto it = std::find_if(printers_.begin(), printers_.end(), [printerName](const Printer& printer) {
            return printer.getName() == printerName;
        });

        // If the printer was found, delete it
        if (it != printers_.end()) {
            printers_.erase(it);
        }
    }

    int calculateTotalCO2Emissions()
    {
        REQUIRE (printers_.size() > 0, "Invalid printer count");
        for (Printer& printer : printers_)
        {
            CO2_emissions += printer.getCO2Emissions();
        }
        return CO2_emissions;
    }

    void addUncompletedJob(Job& job)
    {
        REQUIRE (job.getJobNumber() >= 0, "Invalid job number");
        uncompletedJobs_.emplace_back(job);
        ENSURE (uncompletedJobs_.back().getJobNumber() == job.getJobNumber(), "Job number not added correctly");
    }

private:
    std::vector<Printer> printers_;
    std::vector<Job> jobs_;
    std::vector<Job> uncompletedJobs_;
    std::vector<ClimateCompensationInitiative> climateCompensationInitiatives_;
    int CO2_emissions = 0;


};
#endif //PROJECTTITLE_PRINTINGSYSTEM_H
