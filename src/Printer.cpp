#include "Printer.h"

std::string Printer::getName() const
{
    REQUIRE (!name_.empty(), "Invalid name value");
    return name_;
}

int Printer::getEmissions() const
{
    REQUIRE (emissions_ >= 0, "Invalid emissions value");
    return emissions_;
}

int Printer::getSpeed() const
{
    REQUIRE (speed_ > 0, "Invalid speed value");
    return speed_;
}

int Printer::getCostPerPage() const
{
    REQUIRE (cost_ > 0, "Invalid cost value");
    return cost_;
}

void Printer::setCostPerPage(int cost)
{
    REQUIRE(cost >= 0, "Invalid cost value");
    cost_ = cost;
    ENSURE(cost == getCostPerPage(), "Cost value not updated correctly");
}

void Printer::setEmissions(int emissions)
{
    REQUIRE(emissions >= 0, "Invalid emissions value");
    emissions_ = emissions;
    ENSURE(emissions == getEmissions(), "Emissions value not updated correctly");
}

void Printer::setSpeed(int speed)
{
    REQUIRE (speed >= 0, "Invalid speed value");
    speed_ = speed;
    ENSURE (speed == getSpeed(), "Speed value not updated correctly");
}

void Printer::setName(std::string name)
{
    REQUIRE (!name.empty(), "Invalid name value");
    name_ = name;
    ENSURE (name == getName(), "Name value not updated correctly");
}

void Printer::addJobToPrinter(const Job& job)
{
    REQUIRE (job.getJobNumber() >= 0, "Invalid job number");
    printerjobs_.emplace_back(job);
    ENSURE (printerjobs_.back().getJobNumber() == job.getJobNumber(), "Job number not added correctly");
}

void Printer::setTypes(const std::string &type)
{
    REQUIRE (!type.empty(), "Invalid type value");
    type_ = type;
    ENSURE (type == getType(), "Type value not updated correctly");
}

std::string Printer::getType() const
{
    REQUIRE (!type_.empty(), "Invalid type value");
    return type_;
}

const Job Printer::getCurrentJob() const
{
    REQUIRE (!printerjobs_.empty(), "No current job");
    return printerjobs_.front();
    ENSURE (printerjobs_.front().getJobNumber() == getCurrentJob().getJobNumber(), "Current job not returned correctly");
}

std::vector<Job> Printer::getJobQueue() const
{
    REQUIRE (printerjobs_.size() >= 0, "Invalid job count");
    return printerjobs_;
    ENSURE (printerjobs_.size() == getJobQueue().size(), "Job queue not returned correctly");
}

std::vector<Job*> Printer::getPrinterJobs() const
{
    REQUIRE (printerjobs_.size() >= 0, "Invalid job count");
    return printerjobs_;
}

void Printer::addCompletedJob(Job &job)
{
    REQUIRE (job.getJobNumber() >= 0, "Invalid job number");
    completedJobs_.emplace_back(job);
    printerjobs_.erase(printerjobs_.begin());
    ENSURE (completedJobs_.back().getJobNumber() == job.getJobNumber(), "Job number not added correctly");
}

std::string Printer::getStatus(const Job& job) const
{
    REQUIRE (job.getJobNumber() >= 0, "Invalid job number");
    if (getCurrentJob().getJobNumber() == job.getJobNumber())
    {
        return "Job is currently being processed";
    } else {
        return "Job is currently in queue #" + std::to_string(getQueueNumber(job));
    }
    ENSURE (getStatus(job) == "Job is currently being processed" || getStatus(job) == "Job is currently in queue #" + std::to_string(getQueueNumber(job)), "Status not returned correctly");
}

int Printer::getQueueNumber(const Job& jobR) const
{
    REQUIRE (jobR.getJobNumber() >= 0, "Invalid job number");
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

int Printer::calculateCO2(Job job)
{
    REQUIRE (job.getTotalPages() >= 0, "Invalid page count");
    return job.getTotalPages() * emissions_;
}

std::string Printer::calculateCost(Job job)
{
    REQUIRE (job.getTotalPages() >= 0, "Invalid page count");
    int result = job.getTotalPages() * cost_;
    return std::to_string(result) + " cents";
}

void Printer::incrementCO2Emissions()
{
    REQUIRE (emissions_ >= 0, "Invalid emissions value");
    CO2_emissions += emissions_;
    ENSURE (CO2_emissions == getCO2Emissions(), "CO2 emissions not updated correctly");
}

int Printer::getCO2Emissions()
{
    REQUIRE (CO2_emissions >= 0, "Invalid CO2 emissions value");
    return CO2_emissions;
}

int Printer::getQueuePages()
{
    REQUIRE (printerjobs_.size() >= 0, "Invalid job count");
    int total_pages = 0;
    for (const Job& job : printerjobs_) {
        total_pages += job.getPageCount();
    }
    return total_pages;
}