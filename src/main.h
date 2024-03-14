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
    void loadFromFile(const std::string& filename) {
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
        while (element != nullptr) {
            const char* elementName = element->Value();
            if (strcmp(elementName, "DEVICE") == 0) {
                if (!element->FirstChildElement("name")){
                    loadError = LoadError::MISSING_NAME;
                }
                element = element->NextSiblingElement();
                if (!element->FirstChildElement("emissions")){
                    loadError = LoadError::MISSING_EMISSIONS;
                }
                element = element->NextSiblingElement();
                if (!element->FirstChildElement("speed")){
                    loadError = LoadError::MISSING_SPEED;
                }
                // Store all the elements in variables
                const char* name = element->FirstChildElement("name")->GetText();
                int emissions = std::atoi(element->FirstChildElement("emissions")->GetText());
                int speed = std::atoi(element->FirstChildElement("speed")->GetText());
                if (speed < 0){
                    loadError = LoadError::NEGATIVE_VALUE_SPEED;
                }
                if (emissions < 0){
                    loadError = LoadError::NEGATIVE_VALUE_EMISSIONS;
                }
                Printer printer(name, emissions, speed);
                printers_.push_back(printer);
                DeviceSeen = true;
            }
            else if (strcmp(elementName, "JOB") == 0) {
                if (!element->FirstChildElement("jobNumber")){
                    loadError = LoadError::MISSING_JOB_NUMBER;
                }
                element = element->NextSiblingElement();
                if (!element->FirstChildElement("pageCount")){
                    loadError = LoadError::MISSING_PAGE_COUNT;
                }
                element = element->NextSiblingElement();
                if (!element->FirstChildElement("userName")){
                    loadError = LoadError::MISSING_USER_NAME;
                }
                // Store all the elements in variables
                int jobNumber = std::atoi(element->FirstChildElement("jobNumber")->GetText());
                int pageCount = std::atoi(element->FirstChildElement("pageCount")->GetText());
                const char* userName = element->FirstChildElement("userName")->GetText();
                if (jobNumber < 0){
                    loadError = LoadError::NEGATIVE_VALUE_JOB_NUMBER;
                }
                if (pageCount < 0){
                    loadError = LoadError::NEGATIVE_VALUE_PAGE_COUNT;
                }
                Job job(jobNumber, pageCount, userName);
                jobs_.push_back(job);
                JobSeen = true;
            }
        }
        if (!DeviceSeen) { // Check to see if there is a device in the xml file
            loadError = LoadError::MISSING_DEVICE;
        }
        if (!JobSeen) {
            loadError = LoadError::MISSING_JOB;
        }
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
