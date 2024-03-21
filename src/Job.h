#ifndef PROJECTTITLE_JOB_H
#define PROJECTTITLE_JOB_H
#include "Include.h"
class Job {
    /**
     * This is a class with getter functions like getJobNumber, getPageCount and getUserrName which will be usefull for
     * testing the validity and consistency of our printer and xml parser.
     **/
public:

    Job(){}

    Job(int jobNumber, int pageCount, const std::string& userName) :
            jobNumber_(jobNumber), pageCount_(pageCount), userName_(userName) {}

    int getJobNumber() const { return jobNumber_; }

    int getPageCount() const { return pageCount_; }

    const std::string& getUserName() const { return userName_; }

    bool processPage() {
        if (pageCount_ > 0) {
            --pageCount_;
            return true;
        }
        return false;
    }

    bool isCompleted() const {
        if (pageCount_ == 0){
            return true;
        }
        else {
            return false;
        }
    }



private:
    int jobNumber_;
    int pageCount_;
    std::string userName_;
};

#endif //PROJECTTITLE_JOB_H
