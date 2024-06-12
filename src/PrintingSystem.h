#ifndef PROJECTTITLE_PRINTINGSYSTEM_H
#define PROJECTTITLE_PRINTINGSYSTEM_H



#include "Printer.h"
#include "ClimateCompensationInitiative.h"
#include <iostream>
#include <vector>
#include <algorithm>



class Printer;



class PrintingSystem{



public:



    // Load printers and jobs from an XML file, return the correct errors if there are any and make the correct objects
    std::vector<LoadError> loadFromFileXML(const std::string& filename);



    // Generates a status report in a .txt file with all the printers and jobs
    bool generateStatusReport(const std::string &filename);



    // Functionality to pocess a single job
    void processJob(Job* job, Printer* printer);



    // Functionality to add jobs to a specific printer
    void addJobsToPrinters(PrintingSystem* system);



    // Functionality to process all the jobs in all the printers automatically
    void processAutomatically(PrintingSystem* system);



    // Find out how many printers there are in the system
    //REQUIRE (printers_.size() >= 0, "Invalid printer count");
    int getPrinterCount() const;



    // Find out how many jobs there are in the system
    //REQUIRE (jobs_.size() >= 0, "Invalid job count");
    int getJobCount() const;



    // Add a printer to the system
    //REQUIRE (printer.getName() != "", "Invalid printer name");
    //ENSURE (printers_.back().getName() == printer.getName(), "Printer name not added correctly");
    void addPrinter(Printer* printer);



    // Add a job to the system
    //REQUIRE (job.getUserName() != "", "Invalid user name");
    //ENSURE (jobs_.back().getUserName() == job.getUserName(), "User name not added correctly");
    void addJob(Job* job);



    // Return all the printers in the system
    //REQUIRE (printers_.size() > 0, "Invalid printer count");
    std::vector<Printer*>& getPrinters();



    // Return all the jobs in the system
    //REQUIRE (jobs_.size() > 0, "Invalid job count");
    std::vector<Job*>& getJobs();



    // Delete a job from the system
    //REQUIRE (jobNumber >= 0, "Invalid job number");
    void deleteJob(int jobNumber);



    // Delete a printer from the system
    //REQUIRE (printerName != "", "Invalid printer name");
    void deletePrinter(const std::string& printerName);



    // Calculate the total CO2 emissions
    //REQUIRE (printers_.size() > 0, "Invalid printer count");
    int calculateTotalCO2Emissions();



    // Add a job to the uncompletedJobs_ vector
    //REQUIRE (job.getJobNumber() >= 0, "Invalid job number");
    //ENSURE (uncompletedJobs_.back().getJobNumber() == job.getJobNumber(), "Job number not added correctly");
    void addUncompletedJob(Job* job);



private:



    // Vector to store the different printers
    std::vector<Printer*> printers_;



    // Vector to store the different jobs
    std::vector<Job*> jobs_;



    // I'm not sure if this is actually being used anymore
    std::vector<Job*> uncompletedJobs_;



    // This is not implemented
    std::vector<ClimateCompensationInitiative> climateCompensationInitiatives_;



    // This variable keeps track of the CO2 emissions for all the jobs
    int CO2_emissions = 0;



};
#endif //PROJECTTITLE_PRINTINGSYSTEM_H
