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

    const std::string& getType() const {
        return type_;
    }

    const std::string& getStatus() const {
        if (pageCount_ == 0) {
            return "Completed";
        } else {
            return "In progress";
        }
    }

    int getTotalPages() const {
        return pageCount_;
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

    int getPagesRemaining() const {
        return pageCount_;
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

private:
    int jobNumber_;
    int pageCount_;
    std::string userName_;
    std::string type_;
};

#endif //PROJECTTITLE_JOB_H
