#ifndef PROJECTTITLE_PRINTER_H
#define PROJECTTITLE_PRINTER_H
#include "LoadError.h"
#include "DesignByContract.h"
#include "Job.h"
#include <vector>

class Printer {
public:
    Printer(const std::string& name, int emissions, int speed, float cost, const std::string& type) :
            name_(name), emissions_(emissions), speed_(speed), cost_(cost), type_(type) {}

    Printer(){}

    //REQUIRE (!name_.empty(), "Invalid name value");
    //ENSURE (getName() == name_, "Name was not correctly returned");
    std::string getName() const;

    //REQUIRE (emissions_ >= 0, "Invalid emissions value");
    int getEmissions() const;

    //REQUIRE (speed_ > 0, "Invalid speed value");
    int getSpeed() const;

    //REQUIRE (cost_ > 0, "Invalid cost value");
    int getCostPerPage() const;

    //REQUIRE(cost > 0 && cost <= 100, "Invalid cost value");
    //ENSURE(cost == getCostPerPage(), "Cost value not updated correctly");
    void setCostPerPage(int cost);

    //REQUIRE(emissions >= 0, "Invalid emissions value");
    //ENSURE(emissions == getEmissions(), "Emissions value not updated correctly");
    void setEmissions(int emissions);

    //REQUIRE (speed > 0 && speed <= 1000, "Invalid speed value");
    //ENSURE (speed == getSpeed(), "Speed value not updated correctly");
    void setSpeed(int speed);

    //REQUIRE (!name.empty(), "Invalid name value");
    //REQUIRE (name.length() <= 50, "Name is too long");
    //ENSURE (name == getName(), "Name value not updated correctly");
    void setName(std::string name);

    //REQUIRE (job.getJobNumber() >= 0, "Invalid job number");
    //REQUIRE (job != nullptr, "Job cannot be null");
    //ENSURE (printerjobs_.back().getJobNumber() == job.getJobNumber(), "Job number not added correctly");
    void addJobToPrinter(Job* job);

    //REQUIRE (!type.empty(), "Invalid type value");
    //ENSURE (type == getType(), "Type value not updated correctly");
    void setTypes(const std::string& type);

    //REQUIRE (!type_.empty(), "Invalid type value");
    std::string getType() const;

    //REQUIRE (!printerjobs_.empty(), "No current job");
    //ENSURE (printerjobs_.front().getJobNumber() == getCurrentJob().getJobNumber(), "Current job not returned correctly");
    const Job* getCurrentJob() const;

    //REQUIRE (printerjobs_.size() >= 0, "Invalid job count");
    //ENSURE (printerjobs_.size() == getJobQueue().size(), "Job queue not returned correctly");
    std::vector<Job*> getJobQueue() const;

    //REQUIRE (printerjobs_.size() >= 0, "Invalid job count");
    std::vector<Job*> getPrinterJobs() const;

    //REQUIRE (job.getJobNumber() >= 0, "Invalid job number");
    //REQUIRE (job != nullptr, "Job cannot be null");
    //ENSURE (completedJobs_.back().getJobNumber() == job.getJobNumber(), "Job number not added correctly");
    void addCompletedJob(Job* job);

    //REQUIRE (job.getJobNumber() >= 0, "Invalid job number");
    //REQUIRE (job != nullptr, "Job cannot be null");
    //ENSURE (getStatus(job) == "Job is currently being processed" || getStatus(job) == "Job is currently in queue #" + std::to_string(getQueueNumber(job)), "Status not returned correctly");
    std::string getStatus(const Job* job) const;

    //REQUIRE (jobR.getJobNumber() >= 0, "Invalid job number");
    //REQUIRE (job != nullptr, "Job cannot be null");
    int getQueueNumber(const Job* jobR) const;

    //REQUIRE (job.getTotalPages() >= 0, "Invalid page count");
    //REQUIRE (job != nullptr, "Job cannot be null");
    int calculateCO2(Job* job);

    //REQUIRE (job.getTotalPages() >= 0, "Invalid page count");
    //REQUIRE (job != nullptr, "Job cannot be null");
    std::string calculateCost(Job* job);

    //REQUIRE (emissions_ >= 0, "Invalid emissions value");
    //ENSURE (CO2_emissions == getCO2Emissions(), "CO2 emissions not updated correctly");
    void incrementCO2Emissions();

    //REQUIRE (CO2_emissions >= 0, "Invalid CO2 emissions value");
    int getCO2Emissions() const;

    //REQUIRE (printerjobs_.size() >= 0, "Invalid job count");
    int getQueuePages();

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

class ColorPrinter : public Printer {
public:
    ColorPrinter(const std::string& name, int emissions, int speed, float cost)
            : Printer(name, emissions, speed, cost, "color"){}
};

class BWPrinter : public Printer {
public:
    BWPrinter(const std::string& name, int emissions, int speed, float cost)
            : Printer(name, emissions, speed, cost, "bw"){}
};

class Scanner : public Printer {
public:
    Scanner(const std::string& name, int emissions, int speed, float cost)
            : Printer(name, emissions, speed, cost, "scan"){}
};

class PrinterFactory {
public:
    static Printer* createPrinter(const std::string& name, int emissions, int speed, float cost, const std::string& type);
};

#endif //PROJECTTITLE_PRINTER_H