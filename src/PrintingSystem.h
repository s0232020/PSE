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

    //REQUIRE (printers_.size() >= 0, "Invalid printer count");
    int getPrinterCount() const;

    //REQUIRE (jobs_.size() >= 0, "Invalid job count");
    int getJobCount() const;

    //REQUIRE (printer.getName() != "", "Invalid printer name");
    //ENSURE (printers_.back().getName() == printer.getName(), "Printer name not added correctly");
    void addPrinter(Printer &printer);

    //REQUIRE (job.getUserName() != "", "Invalid user name");
    //ENSURE (jobs_.back().getUserName() == job.getUserName(), "User name not added correctly");
    void addJob(Job &job);


    //REQUIRE (printers_.size() > 0, "Invalid printer count");
    std::vector<Printer>& getPrinters();

    //REQUIRE (jobs_.size() > 0, "Invalid job count");
    std::vector<Job>& getJobs();

    //REQUIRE (jobNumber >= 0, "Invalid job number");
    void deleteJob(int jobNumber);

    //REQUIRE (printerName != "", "Invalid printer name");
    void deletePrinter(const std::string& printerName);

    //REQUIRE (printers_.size() > 0, "Invalid printer count");
    int calculateTotalCO2Emissions();

    //REQUIRE (job.getJobNumber() >= 0, "Invalid job number");
    //ENSURE (uncompletedJobs_.back().getJobNumber() == job.getJobNumber(), "Job number not added correctly");
    void addUncompletedJob(Job& job);

private:
    std::vector<Printer> printers_;
    std::vector<Job> jobs_;
    std::vector<Job> uncompletedJobs_;
    std::vector<ClimateCompensationInitiative> climateCompensationInitiatives_;
    int CO2_emissions = 0;


};
#endif //PROJECTTITLE_PRINTINGSYSTEM_H
