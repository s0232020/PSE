#ifndef PROJECTTITLE_JOB_H
#define PROJECTTITLE_JOB_H

#include <string>

class Job {
public:
    Job() {}

    Job(int jobNumber, int pageCount, const std::string& userName, const std::string& type) :
            jobNumber_(jobNumber), pageCount_(pageCount), userName_(userName), type_(type) {}

    int getJobNumber() const {
        return jobNumber_;
    }

    int getPageCount() const {
        return pageCount_;
    }

    const std::string& getUserName() const {
        return userName_;
    }

    std::string getType() const
    {
        REQUIRE (!type_.empty(), "Invalid type value");
        return type_;
    }

    void setJobNumber(int jobNumber) {
        jobNumber_ = jobNumber;
    }

    void setPageCount(int pageCount) {
        pageCount_ = pageCount;
    }

    void setUserName(const std::string& userName) {
        userName_ = userName;
    }

    void setType(const std::string& type) {
        type_ = type;
    }

    bool processPage() {
        if (pageCount_ > 0) {
            --pageCount_;
            return true;
        }
        return false;
    }

    bool isCompleted() const {
        return pageCount_ == 0;
    }

    void processScanPage()
    {
        --pageCount_;
    }

    void processColorPage()
    {
        --pageCount_;
    }

    void processBWPage()
    {
        --pageCount_;
    }

    void setTotalPages(int Totalpages)
    {
        totalpages_ = Totalpages;
        ENSURE (totalpages_ == Totalpages, "Totalpages not updated correctly");
    }

    int getTotalPages()
    {
        REQUIRE (totalpages_ > 0, "Totalpages cannot be a negative value");
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
