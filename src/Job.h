#ifndef PROJECTTITLE_JOB_H
#define PROJECTTITLE_JOB_H



#include <string>
#include "DesignByContract.h"



class Job {



public:



    Job(int jobNumber, int pageCount, const std::string& userName, const std::string& type) :
            jobNumber_(jobNumber), pageCount_(pageCount), userName_(userName), type_(type) {}



    //REQUIRE (jobNumber_ > 0, "JobNumber cannot be a negative value");
    int getJobNumber() const;



    //REQUIRE (pageCount_ >= 0, "PageCount cannot be a negative value");
    int getPageCount() const;



    //REQUIRE (!userName_.empty(), "Invalid username value");
    const std::string& getUserName() const;



    //REQUIRE (!type_.empty(), "Invalid type value");
    std::string getType() const;



    //REQUIRE (jobNumber > 0, "JobNumber cannot be a negative value");
    void setJobNumber(int jobNumber);



    //REQUIRE (pageCount > 0, "PageCount cannot be a negative value");
    //ENSURE (pageCount_ == pageCount, "PageCount not updated correctly");
    void setPageCount(int pageCount);



    //REQUIRE (!userName.empty(), "Invalid username value");
    //ENSURE (userName_ == userName, "Username not updated correctly");
    void setUserName(const std::string& userName);



    //REQUIRE (!type.empty(), "Invalid type value");
    //ENSURE (type_ == type, "Type not updated correctly");
    void setType(const std::string& type);



    //REQUIRE (pageCount_ > 0, "PageCount cannot be a negative value");
    virtual void processPage() = 0;



    //REQUIRE (pageCount_ >= 0, "PageCount cannot be a negative value");
    bool isCompleted() const;



    //REQUIRE (totalpages_ > 0, "Totalpages cannot be a negative value");
    //ENSURE (totalpages_ == Totalpages, "Totalpages not updated correctly");
    void setTotalPages(int Totalpages);



    //REQUIRE (totalpages_ > 0, "Totalpages cannot be a negative value");
    int getTotalPages();



private:



    int jobNumber_;



    int pageCount_;



    std::string userName_;



    std::string type_;



    int totalpages_;



};

class ColorJob : public Job {



public:



    ColorJob(int jobNumber, int pageCount, const std::string& userName)
            : Job(jobNumber, pageCount, userName, "color") {}



    // REQUIRE (getPageCount() > 0, "PageCount cannot be a negative value");
    void processPage();



};

class BWJob : public Job {



public:



    BWJob(int jobNumber, int pageCount, const std::string& userName)
            : Job(jobNumber, pageCount, userName, "bw") {}



    // REQUIRE (getPageCount() > 0, "PageCount cannot be a negative value");
    void processPage();



};

class ScanJob : public Job{



public:



    ScanJob(int jobNumber, int pageCount, const std::string& userName)
            : Job(jobNumber, pageCount, userName, "scan") {}



    // REQUIRE (getPageCount() > 0, "PageCount cannot be a negative value");
    void processPage();



};

class JobFactory{



public:



    static Job* createJob(const std::string& type, int jobNumber, int pageCount, const std::string& userName);



};

#endif //PROJECTTITLE_JOB_H
