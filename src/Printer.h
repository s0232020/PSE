#ifndef PROJECTTITLE_PRINTER_H
#define PROJECTTITLE_PRINTER_H
#include "LoadError.h"
#include <iostream>
#include "DesignByContract.h"
#include "Job.h"
#include <vector>

class Printer {
public:
    Printer(const std::string& name, int emissions, int speed, float cost, const std::string& type) :
            name_(name), emissions_(emissions), speed_(speed), cost_(cost), type_(type) {}

    Printer(){}

    std::string getName() const; //REQUIRE (!name_.empty(), "Invalid name value");
    int getEmissions() const; //REQUIRE (emissions_ >= 0, "Invalid emissions value");
    int getSpeed() const; //REQUIRE (speed_ > 0, "Invalid speed value");
    int getCostPerPage() const; //REQUIRE (cost_ > 0, "Invalid cost value");
    void setCostPerPage(int cost); //REQUIRE(cost >= 0, "Invalid cost value"); ENSURE(cost == getCostPerPage(), "Cost value not updated correctly");
    void setEmissions(int emissions); //REQUIRE(emissions >= 0, "Invalid emissions value"); ENSURE(emissions == getEmissions(), "Emissions value not updated correctly");
    void setSpeed(int speed); //REQUIRE (speed >= 0, "Invalid speed value"); ENSURE (speed == getSpeed(), "Speed value not updated correctly");
    void setName(std::string name); //REQUIRE (!name.empty(), "Invalid name value"); ENSURE (name == getName(), "Name value not updated correctly");
    void addJobToPrinter(Job* job); //REQUIRE (job.getJobNumber() >= 0, "Invalid job number"); ENSURE (printerjobs_.back().getJobNumber() == job.getJobNumber(), "Job number not added correctly");
    void setTypes(const std::string& type); //REQUIRE (!type.empty(), "Invalid type value"); ENSURE (type == getType(), "Type value not updated correctly");
    std::string getType() const; //REQUIRE (!type_.empty(), "Invalid type value");
    const Job getCurrentJob() const; //REQUIRE (!printerjobs_.empty(), "No current job"); ENSURE (printerjobs_.front().getJobNumber() == getCurrentJob().getJobNumber(), "Current job not returned correctly");
    std::vector<Job*> getJobQueue() const; //REQUIRE (printerjobs_.size() >= 0, "Invalid job count"); ENSURE (printerjobs_.size() == getJobQueue().size(), "Job queue not returned correctly");
    std::vector<Job*> getPrinterJobs() const; //REQUIRE (printerjobs_.size() >= 0, "Invalid job count");
    void addCompletedJob(Job* job); //REQUIRE (job.getJobNumber() >= 0, "Invalid job number"); ENSURE (completedJobs_.back().getJobNumber() == job.getJobNumber(), "Job number not added correctly");
    std::string getStatus(const Job* job) const; //REQUIRE (job.getJobNumber() >= 0, "Invalid job number"); ENSURE (getStatus(job) == "Job is currently being processed" || getStatus(job) == "Job is currently in queue #" + std::to_string(getQueueNumber(job)), "Status not returned correctly");
    int getQueueNumber(const Job* jobR) const; //REQUIRE (jobR.getJobNumber() >= 0, "Invalid job number");
    int calculateCO2(Job job); //REQUIRE (job.getTotalPages() >= 0, "Invalid page count");
    std::string calculateCost(Job job); //REQUIRE (job.getTotalPages() >= 0, "Invalid page count");
    void incrementCO2Emissions(); //REQUIRE (emissions_ >= 0, "Invalid emissions value"); ENSURE (CO2_emissions == getCO2Emissions(), "CO2 emissions not updated correctly");
    int getCO2Emissions() const; //REQUIRE (CO2_emissions >= 0, "Invalid CO2 emissions value");
    int getQueuePages(); //REQUIRE (printerjobs_.size() >= 0, "Invalid job count");

private:
    std::vector<Job*> completedJobs_;
    std::vector<Job*> printerjobs_;
    std::string name_;
    int emissions_;
    int speed_;
    float cost_;
    std::string type_;
    int CO2_emissions = 0;
};

#endif //PROJECTTITLE_PRINTER_H