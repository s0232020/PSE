#ifndef PROJECTTITLE_MAIN_H
#define PROJECTTITLE_MAIN_H
#include "Include.h"
class Printer {
    /**
     * Made by Jelle
     * This is a class with getter functions like getName, getEmissions and getSpeed which will be usefull for
     * testing the validity and consistency of our printer and xml parser.
     * The emissions are specified in the following unit: gram CO2 per page
     * The speeds are specified in the following unit: pages per minute
     * **/
public:
    Printer(const std::string& name, int emissions, int speed) :
            name_(name), emissions_(emissions), speed_(speed) {}
    std::string getName() const {
        return name_;
    }
    int getEmissions() const {
        return emissions_;
    }
    int getSpeed() const {
        return speed_;
    }
    void setEmissions(int emissions) { emissions_ = emissions; }
    void setSpeed(int speed) { speed_ = speed; }
private:
    std::string name_;
    int emissions_;
    int speed_;
};

class Job {
    /**
     * Made by Jelle
     * This is a class with getter functions like getJobNumber, getPageCount and getUserrName which will be usefull for
     * testing the validity and consistency of our printer and xml parser.
     * **/
public:
    Job(int jobNumber, int pageCount, const std::string& userName) :
            jobNumber_(jobNumber), pageCount_(pageCount), userName_(userName) {}
    int getJobNumber() const { return jobNumber_; }
    int getPageCount() const { return pageCount_; }
    const std::string& getUserName() const { return userName_; }
private:
    int jobNumber_;
    int pageCount_;
    std::string userName_;
};
enum class LoadError {
    NO_ERROR,
    MISSING_SYSTEM,
    MISSING_DEVICE,
    MISSING_NAME,
    MISSING_EMISSIONS,
    MISSING_SPEED,
    MISSING_JOB,
    MISSING_JOB_NUMBER,
    MISSING_PAGE_COUNT,
    MISSING_USER_NAME,
    NEGATIVE_VALUE_SPEED,
    NEGATIVE_VALUE_EMISSIONS,
    NEGATIVE_VALUE_JOB_NUMBER,
    NEGATIVE_VALUE_PAGE_COUNT,
    FAILED_TO_OPEN_FILE
};
class PrintingSystem {
    /**
     * Made by Jelle
     * This is a simple class for our printing system which at the time of writing has 1 function called
     * loadFromFile which is a basic xml parser, and 2 getter functions called getPrinterCount and getJobCount
     * which will return the amount of printers and jobs
     * **/
public:
    LoadError loadFromFile(const std::string& filename) {
        /**
         Made by Jelle
         This function is going to parse a xml file and is going to store the printer and it's jobs with it's different
         parameters (name, emissions, speed for device and jobNumber, pageCount and userName for job)
         The function will return false when something goes wrong or the xml file is not valid,
         or true when everything goes as expected and the xml file is valid.
         This will be usefull when testing.
        **/
        LoadError loadError = LoadError::NO_ERROR;
        bool DeviceSeen = false;
        bool JobSeen = false;
        TiXmlDocument doc;
        if (!doc.LoadFile(filename.c_str())){
            loadError = LoadError::FAILED_TO_OPEN_FILE;
        }

        TiXmlElement* systemElement = doc.FirstChildElement("SYSTEM");
        if (!systemElement) {
            loadError = LoadError::MISSING_SYSTEM;
        }
        TiXmlElement* element = systemElement->FirstChildElement();
        std::string name = "";
        int emissions = 0;
        int speed = 0;
        int jobNumber = 0;
        int pageCount = 0;
        const char* userName = "";
        while (element != nullptr) {
            const char* elementName = element->Value();
            TiXmlElement* nameElement = element->FirstChildElement("name");
            TiXmlElement* emissionsElement = element->FirstChildElement("emissions");
            TiXmlElement* speedElement = element->FirstChildElement("speed");
            if (strcmp(elementName, "DEVICE") == 0) {
                if (!nameElement){
                    loadError = LoadError::MISSING_NAME;
                }
                if (nameElement){
                    name = nameElement->GetText();
                }
                if (!emissionsElement){
                    loadError = LoadError::MISSING_EMISSIONS;
                }
                if (emissionsElement){
                    emissions = std::atoi(emissionsElement->GetText());
                    if (emissions < 0){
                        loadError = LoadError::NEGATIVE_VALUE_EMISSIONS;
                    }
                }
                if (!speedElement){
                    loadError = LoadError::MISSING_SPEED;
                }
                if (speedElement){
                    speed = std::atoi(speedElement->GetText());
                    if (speed < 0){
                        loadError = LoadError::NEGATIVE_VALUE_SPEED;
                    }
                }
                Printer printer(name, emissions, speed);
                printers_.push_back(printer);
                DeviceSeen = true;
            }
            else if (strcmp(elementName, "JOB") == 0) {
                TiXmlElement* jobNumberElement = element->FirstChildElement("jobNumber");
                TiXmlElement* pageCountElement = element->FirstChildElement("pageCount");
                TiXmlElement* userNameElement = element->FirstChildElement("userName");
                if (!jobNumberElement){
                    loadError = LoadError::MISSING_JOB_NUMBER;
                }
                if (jobNumberElement){
                    jobNumber = std::atoi(jobNumberElement->GetText());
                    if (jobNumber < 0){
                        loadError = LoadError::NEGATIVE_VALUE_JOB_NUMBER;
                    }
                }
                if (!pageCountElement){
                    loadError = LoadError::MISSING_PAGE_COUNT;
                }
                if (pageCountElement){
                    pageCount = std::atoi(pageCountElement->GetText());
                    if (pageCount < 0){
                        loadError = LoadError::NEGATIVE_VALUE_PAGE_COUNT;
                    }
                }
                if (!userNameElement){
                    loadError = LoadError::MISSING_USER_NAME;
                }
                if (userNameElement){
                    userName = userNameElement->GetText();
                }
                Job job(jobNumber, pageCount, userName);
                jobs_.push_back(job);
                JobSeen = true;
            }
            element = element->NextSiblingElement();
        }
        if (!DeviceSeen) {
            loadError = LoadError::MISSING_DEVICE;
        }
        if (!JobSeen) {
            loadError = LoadError::MISSING_JOB;
        }
        return loadError;
    }
    std::string getLoadErrorMessage(LoadError error) {
        switch (error) {
            case LoadError::MISSING_SYSTEM:
                return "System missing";
            case LoadError::MISSING_DEVICE:
                return "Device missing";
            case LoadError::MISSING_NAME:
                return "Name missing";
            case LoadError::MISSING_EMISSIONS:
                return "Emissions missing";
            case LoadError::MISSING_SPEED:
                return "Speed missing";
            case LoadError::MISSING_JOB:
                return "Job missing";
            case LoadError::MISSING_JOB_NUMBER:
                return "Job number missing";
            case LoadError::MISSING_PAGE_COUNT:
                return "Page count missing";
            case LoadError::MISSING_USER_NAME:
                return "User name missing";
            case LoadError::NEGATIVE_VALUE_SPEED:
                return "Negative value for speed";
            case LoadError::NEGATIVE_VALUE_EMISSIONS:
                return "Negative value for emissions";
            case LoadError::NEGATIVE_VALUE_JOB_NUMBER:
                return "Negative value for job number";
            case LoadError::NEGATIVE_VALUE_PAGE_COUNT:
                return "Negative value for page count";
            case LoadError::NO_ERROR:
            default:
                return "No error";
        }
    }

    int getPrinterCount() const { // Keep count of how many devices there are
        return printers_.size();
    }
    int getJobCount() const { // Keep count of how many jobs there are
        return jobs_.size();
    }
std::vector<Printer> printers_;
std::vector<Job> jobs_;
};

#endif //PROJECTTITLE_MAIN_H
