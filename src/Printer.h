#ifndef PROJECTTITLE_PRINTER_H
#define PROJECTTITLE_PRINTER_H
#include "LoadError.h"
#include <iostream>
#include "DesignByContract.h"
#include "Job.h"
#include <vector>
class Printer {
    /**
     * This is a class with getter functions like getName, getEmissions and getSpeed which will be usefull for
     * testing the validity and consistency of our printer and xml parser.
     * The emissions are specified in the following unit: gram CO2 per page
     * The speeds are specified in the following unit: pages per minute
     * **/
public:
    Printer(const std::string& name, int emissions, int speed, float cost, std::string& type) :
            name_(name), emissions_(emissions), speed_(speed), cost_(cost), type_(type) {}

    std::string getName() const
    {
        REQUIRE (!name_.empty(), "Invalid name value");
        return name_;
    }

    int getEmissions() const
    {
        REQUIRE (emissions_ >= 0, "Invalid emissions value");
        return emissions_;
    }

    int getSpeed() const
    {
        REQUIRE (speed_ >= 0, "Invalid speed value");
        return speed_;
    }

    int getPagesPerMinute() const
    {
        return speed_;
    }

    int getCostPerPage() const
    {
        return cost_;
    }

    void setCostPerPage(int cost)
    {
        REQUIRE(cost >= 0, "Invalid cost value");
        cost_ = cost;
        ENSURE(cost == getCostPerPage(), "Cost value not updated correctly");
    }


    void setEmissions(int emissions)
    {
        REQUIRE(emissions >= 0, "Invalid emissions value");
        emissions_ = emissions;
        ENSURE(emissions == getEmissions(), "Emissions value not updated correctly");
    }


    void setSpeed(int speed)
    {
        REQUIRE (speed >= 0, "Invalid speed value");
        speed_ = speed;
        ENSURE (speed == getSpeed(), "Speed value not updated correctly");
    }

    void setName(std::string name)
    {
        REQUIRE (!name.empty(), "Invalid name value");
        name_ = name;
        ENSURE (name == getName(), "Name value not updated correctly");
    }


    void addJobToPrinter(const Job& job)
    {
        printerjobs_.emplace_back(job);
    }

    void removeCurrentJob() {
        if (!printerjobs_.empty()) {
            printerjobs_.erase(printerjobs_.begin());
        }
    }

    void setTypes(const std::string &type) {
        type_ = type;
    }

    std::string getType() const
    {
        REQUIRE (!type_.empty(), "Invalid type value");
        return type_;
    }

    const Job& getCurrentJob() const
    {
        REQUIRE (!printerjobs_.empty(), "No current job");
        return printerjobs_.front();
        ENSURE (printerjobs_.front().getJobNumber() == getCurrentJob().getJobNumber(), "Current job not returned correctly");
    }

    std::vector<Job> getJobQueue() const
    {
        REQUIRE (printerjobs_.size() >= 0, "Invalid job count");
        return printerjobs_;
        ENSURE (printerjobs_.size() == getJobQueue().size(), "Job queue not returned correctly");
    }

    std::vector<Job> getPrinterJobs() const {
        return printerjobs_;
    }

    void addCompletedJob(Job &job) {
        completedJobs_.emplace_back(job);
        printerjobs_.erase(printerjobs_.begin());
    }

    std::string getStatus(const Job& job) const
    {
        if (getCurrentJob().getJobNumber() == job.getJobNumber())
        {
            return "Job is currently being processed";
        } else {
            return "Job is currently in queue #" + std::to_string(getQueueNumber(job));
        }
    }

    int getQueueNumber(const Job& jobR) const
    {
        int result = 0;
        for (Job job : getJobQueue())
        {
            if (job.getJobNumber() == jobR.getJobNumber())
            {
                return result;
            } else {
                result++;
            }
        }
        return result;
    }

    int calculateCO2(Job job)
    {
        return job.getTotalPages() * emissions_;
    }

    std::string calculateCost(Job job)
    {
        int result = job.getTotalPages() * cost_;
        return std::to_string(result) + " cents";
    }

    void incrementCO2Emissions()
    {
        CO2_emissions += emissions_;
    }

    int getCO2Emissions()
    {
        return CO2_emissions;
    }

    int getQueuePages() {
        int total_pages = 0;
        for (const Job& job : printerjobs_) {
            total_pages += job.getPageCount();
        }
        return total_pages;
    }

private:
    std::vector<Job> completedJobs_;
    std::vector<Job> printerjobs_;
    std::string name_;
    int emissions_;
    int speed_;
    float cost_;
    std::string type_;
    int CO2_emissions = 0;
};
#endif //PROJECTTITLE_PRINTER_H
