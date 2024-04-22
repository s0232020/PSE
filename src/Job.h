#ifndef PROJECTTITLE_JOB_H
#define PROJECTTITLE_JOB_H

class Job {
    /**
     * This is a class with getter functions like getJobNumber, getPageCount and getUserrName which will be usefull for
     * testing the validity and consistency of our printer and xml parser.
     **/
public:

    Job(){}

    Job(int jobNumber, int pageCount, const std::string& userName) :
            jobNumber_(jobNumber), pageCount_(pageCount), userName_(userName) {}

    int getJobNumber() const
    {
        REQUIRE (jobNumber_ >= 0, "Invalid job number value");
        return jobNumber_;
    }

    int getPageCount() const
    {
        REQUIRE (pageCount_ >= 0, "Invalid page count value");
        return pageCount_;
    }


    const std::string& getUserName() const
    {
        REQUIRE (!userName_.empty(), "Invalid user name value");
        return userName_;
    }

    const std::string& getStatus() const
    {
        if (pageCount_ == 0)
        {
            return "Completed";
        }
        else
        {
            return "In progress";
        }
    }

    int getTotalPages() const
    {
        return pageCount_;
    }

    void setJobNumber(int jobNumber)
    {
        REQUIRE(jobNumber >= 0, "Invalid job number value");
        jobNumber_ = jobNumber;
        ENSURE(jobNumber == getJobNumber(), "Job number value not updated correctly");
    }

    void setPageCount(int pageCount)
    {
        REQUIRE(pageCount >= 0, "Invalid page count value");
        pageCount_ = pageCount;
        ENSURE(pageCount == getPageCount(), "Page count value not updated correctly");
    }

    void setUserName(const std::string& userName)
    {
        REQUIRE(!userName.empty(), "Invalid user name value");
        userName_ = userName;
        ENSURE(userName == getUserName(), "User name value not updated correctly");
    }

    int getPagesRemaining() const
    {
        return pageCount_;
    }


    bool processPage()
    {
        if (pageCount_ > 0) // Might change this to if (getPageCount() > 0)
        {
            --pageCount_;
            return true;
        }
        return false;
    }

    bool isCompleted() const
    {
        if (pageCount_ == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }



private:
    int jobNumber_;
    int pageCount_;
    std::string userName_;
};

#endif //PROJECTTITLE_JOB_H
