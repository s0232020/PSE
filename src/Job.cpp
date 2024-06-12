#include "Job.h"



int Job::getJobNumber() const
{

    REQUIRE (jobNumber_ > 0, "JobNumber cannot be a negative value");
    return jobNumber_;

}



int Job::getPageCount() const
{

    REQUIRE (pageCount_ >= 0, "PageCount cannot be a negative value");
    return pageCount_;

}



const std::string& Job::getUserName() const
{

    REQUIRE (!userName_.empty(), "Invalid username value");
    return userName_;

}



std::string Job::getType() const
{

    REQUIRE (!type_.empty(), "Invalid type value");
    return type_;

}



void Job::setJobNumber(int jobNumber)
{

    REQUIRE (jobNumber > 0, "JobNumber cannot be a negative value");
    jobNumber_ = jobNumber;

}



void Job::setPageCount(int pageCount)
{

    REQUIRE (pageCount >= 0, "PageCount cannot be a negative value");
    pageCount_ = pageCount;
    ENSURE (pageCount_ == pageCount, "PageCount not updated correctly");

}



void Job::setUserName(const std::string& userName)
{

    REQUIRE (!userName.empty(), "Invalid username value");
    userName_ = userName;
    ENSURE (userName_ == userName, "Username not updated correctly");

}



void Job::setType(const std::string& type)
{

    REQUIRE (!type.empty(), "Invalid type value");
    type_ = type;
    ENSURE (type_ == type, "Type not updated correctly");

}



bool Job::isCompleted() const
{

    REQUIRE (pageCount_ >= 0, "PageCount cannot be a negative value");
    return pageCount_ == 0;

}



void Job::setTotalPages(int Totalpages)
{

#ifndef TESTING
    REQUIRE (totalpages_ > 0, "Totalpages cannot be a negative value");
#endif
    totalpages_ = Totalpages;
    ENSURE (totalpages_ == Totalpages, "Totalpages not updated correctly");

}



int Job::getTotalPages()
{

#ifndef TESTING
    REQUIRE (totalpages_ > 0, "Totalpages cannot be a negative value");
#endif
    return totalpages_;

}



Job* JobFactory::createJob(const std::string& type, int jobNumber, int pageCount, const std::string& userName)
{

    if (type == "color") {
        return new ColorJob(jobNumber, pageCount, userName);
    } else if (type == "bw") {
        return new BWJob(jobNumber, pageCount, userName);
    } else if (type == "scan") {
        return new ScanJob(jobNumber, pageCount, userName);
    } else {
        // Handle unknown job type
        return nullptr;
    }

}



void ColorJob::processPage()
{

    REQUIRE (getPageCount() > 0, "PageCount cannot be a negative value");
    setPageCount(getPageCount() - 1);

}



void BWJob::processPage()
{

    REQUIRE (getPageCount() > 0, "PageCount cannot be a negative value");
    setPageCount(getPageCount() - 1);

}



void ScanJob::processPage()
{

    REQUIRE (getPageCount() > 0, "PageCount cannot be a negative value");
    setPageCount(getPageCount() - 1);

}