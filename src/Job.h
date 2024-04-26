#ifndef PROJECTTITLE_JOB_H
#define PROJECTTITLE_JOB_H

#include <string>

class Job {
public:
    Job() {}

    Job(int jobNumber, int pageCount, const std::string& userName, const std::string& type) :
            jobNumber_(jobNumber), pageCount_(pageCount), userName_(userName), type_(type) {}

    int getJobNumber() const
    {
        REQUIRE (jobNumber_ > 0, "JobNumber cannot be a negative value");
        return jobNumber_;
    }

    int getPageCount() const
    {
        REQUIRE (pageCount_ >= 0, "PageCount cannot be a negative value");
        return pageCount_;
    }

    const std::string& getUserName() const
    {
        REQUIRE (!userName_.empty(), "Invalid username value");
        return userName_;
    }

    std::string getType() const
    {
        REQUIRE (!type_.empty(), "Invalid type value");
        return type_;
    }

    void setJobNumber(int jobNumber)
    {
        REQUIRE (jobNumber > 0, "JobNumber cannot be a negative value");
        jobNumber_ = jobNumber;
    }

    void setPageCount(int pageCount)
    {
        REQUIRE (pageCount > 0, "PageCount cannot be a negative value");
        pageCount_ = pageCount;
        ENSURE (pageCount_ == pageCount, "PageCount not updated correctly");
    }

    void setUserName(const std::string& userName)
    {
        REQUIRE (!userName.empty(), "Invalid username value");
        userName_ = userName;
        ENSURE (userName_ == userName, "Username not updated correctly");
    }

    void setType(const std::string& type)
    {
        REQUIRE (!type.empty(), "Invalid type value");
        type_ = type;
        ENSURE (type_ == type, "Type not updated correctly");
    }

    bool processPage()
    {
        REQUIRE (pageCount_ > 0, "PageCount cannot be a negative value");
        if (pageCount_ > 0) {
            --pageCount_;
            return true;
        }
        return false;
    }

    bool isCompleted() const
    {
        REQUIRE (pageCount_ >= 0, "PageCount cannot be a negative value");
        return pageCount_ == 0;
    }

    void processScanPage()
    {
        REQUIRE (pageCount_ > 0, "PageCount cannot be a negative value");
        --pageCount_;
        ENSURE (pageCount_ >= 0, "PageCount cannot be a negative value");
    }

    void processColorPage()
    {
        REQUIRE (pageCount_ > 0, "PageCount cannot be a negative value");
        --pageCount_;
        ENSURE (pageCount_ >= 0, "PageCount cannot be a negative value");
    }

    void processBWPage()
    {
        REQUIRE (pageCount_ > 0, "PageCount cannot be a negative value");
        --pageCount_;
        ENSURE (pageCount_ >= 0, "PageCount cannot be a negative value");
    }

    void setTotalPages(int Totalpages)
    {
        #ifndef TESTING
        REQUIRE (totalpages_ > 0, "Totalpages cannot be a negative value");
        #endif
        totalpages_ = Totalpages;
        ENSURE (totalpages_ == Totalpages, "Totalpages not updated correctly");
    }

    int getTotalPages()
    {
        #ifndef TESTING
        REQUIRE (totalpages_ > 0, "Totalpages cannot be a negative value");
        #endif
        return totalpages_;
    }



private:
    int jobNumber_;
    int pageCount_;
    std::string userName_;
    std::string type_;
    int totalpages_;
};

#endif //PROJECTTITLE_JOB_H
