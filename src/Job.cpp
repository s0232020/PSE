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
    REQUIRE (pageCount > 0, "PageCount cannot be a negative value");
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

bool Job::processPage()
{
    REQUIRE (pageCount_ > 0, "PageCount cannot be a negative value");
    if (pageCount_ > 0) {
        --pageCount_;
        return true;
    }
    return false;
}

bool Job::isCompleted() const
{
    REQUIRE (pageCount_ >= 0, "PageCount cannot be a negative value");
    return pageCount_ == 0;
}

void Job::processScanPage()
{
    REQUIRE (pageCount_ > 0, "PageCount cannot be a negative value");
    --pageCount_;
    ENSURE (pageCount_ >= 0, "PageCount cannot be a negative value");
}

void Job::processColorPage()
{
    REQUIRE (pageCount_ > 0, "PageCount cannot be a negative value");
    --pageCount_;
    ENSURE (pageCount_ >= 0, "PageCount cannot be a negative value");
}

void Job::processBWPage()
{
    REQUIRE (pageCount_ > 0, "PageCount cannot be a negative value");
    --pageCount_;
    ENSURE (pageCount_ >= 0, "PageCount cannot be a negative value");
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