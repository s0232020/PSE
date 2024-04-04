#ifndef PROJECTTITLE_PRINTER_H
#define PROJECTTITLE_PRINTER_H
#include "DesignByContract.h"
#include "Include.h"
class Printer {
    /**
     * This is a class with getter functions like getName, getEmissions and getSpeed which will be usefull for
     * testing the validity and consistency of our printer and xml parser.
     * The emissions are specified in the following unit: gram CO2 per page
     * The speeds are specified in the following unit: pages per minute
     * **/
public:
    Printer(const std::string& name, int emissions, int speed) :
            name_(name), emissions_(emissions), speed_(speed) {}

    std::string getName() const {
        REQUIRE (name_.length() >= 0);
        return name_;
    }

    int getEmissions() const
    {
        REQUIRE (emissions >= 0);
        return emissions_;
    }

    int getSpeed() const {
        return speed_;
    }

        void setEmissions(int emissions)
        {
            REQUIRE (emissions >= 0);
            emissions_ = emissions;
            ENSURE (emissions == getEmissions());
        }

    void setSpeed(int speed) { speed_ = speed; }

    void setName(std::string name) { name_ = name; }


    void addJob(const Job& job){
        printerjobs_.emplace_back(job);
    }

    void removeCurrentJob() {
        if (!printerjobs_.empty()) {
            printerjobs_.erase(printerjobs_.begin());
        }
    }

    const Job& getCurrentJob() const {
        return printerjobs_.front();
    }

    std::vector<Job> getJobQueue() const {
        return printerjobs_;
    }

    std::vector<Job> getPrinterJobs() const {
        return printerjobs_;
    }

    void addCompletedJob(Job &job) {
        completedJobs_.emplace_back(job);
        printerjobs_.erase(printerjobs_.begin());
    }

private:
    std::vector<Job> completedJobs_;
    std::vector<Job> printerjobs_;
    std::string name_;
    int emissions_;
    int speed_;
};
#endif //PROJECTTITLE_PRINTER_H
