#include "PrintingSystem.h"
#include "ClimateCompensationInitiative.h"
#include "../TinyXML/tinyxml.h"
#include "main.h"

LoadError PrintingSystem::loadFromFile(const std::string &filename)
{
    /**
     * This function loads the printing system configuration from an XML file.
     * It parses the file, extracts the data for printers and jobs, and stores them in the respective objects.
     * If the file is not valid or there's an issue with its content, it returns an appropriate LoadError.
     * Otherwise, it returns LoadError::NO_ERROR to indicate successful loading.
     **/
    LoadError loadError = LoadError::NO_ERROR;

    bool DeviceSeen = false;
    bool JobSeen = false;

    TiXmlDocument doc;

    if (!doc.LoadFile(filename.c_str()))
    {
        loadError = LoadError::FAILED_TO_OPEN_FILE;
        std::cerr << "Failed to open file" << std::endl;
    }

    TiXmlElement* systemElement = doc.FirstChildElement("SYSTEM");
    if (!systemElement)
    {
        loadError = LoadError::MISSING_SYSTEM;
    }

    TiXmlElement* element = systemElement->FirstChildElement();

    std::string name = "";
    int emissions = 0;
    int speed = 0;
    int jobNumber = 0;
    int pageCount = 0;
    const char* userName = "";

    while (element != nullptr)
    {
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
            addPrinter(printer);

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
            addJob(job);

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

const char* getLoadErrorMessage(LoadError error) {
    /**
     * This function takes a LoadError enumeration value and returns a corresponding
     * human-readable error message as a string. This can be used to display or log errors
     * when loading the printing system configuration from an XML file.
     **/
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

bool PrintingSystem::generateStatusReport(const std::string &filename)
{
    std::ofstream outputFile;
    std::string outputFilename = filename;

    // Open output file with new filename
    outputFile.open(outputFilename);

    // Check if output file is opened, if not, print error message and return false
    if (!outputFile.is_open()) {
        std::cout << "Failed to create output file: " << filename << "\n";
        return false;
    }

    // Print header
    outputFile << "# === [System Status] === #\n\n";

    // Print device information
    outputFile << "--== Devices ==--\n";
    for (const auto &printer : getPrinters())
    {
        outputFile << printer.getName() << ":\n";
        outputFile << "* CO2: " << printer.getEmissions() << "g/page\n";
        outputFile << "* Pages per minute: " << printer.getPagesPerMinute() << "\n";
        outputFile << "* Type: " << printer.getType() << "\n";
        outputFile << "* Cost per page: " << printer.getCostPerPage() << " cents\n\n";
    }

    // Print job information
    outputFile << "--== Jobs ==--\n";
    for (const auto &printer : getPrinters())
    {
        outputFile << "Printer " << printer.getName() << ":\n";
        Job currentJob = Job(0, 0, "");

        if (!printer.getPrinterJobs().empty())
        {
            currentJob = printer.getCurrentJob();
        }

        for(const auto& job : printer.getJobQueue()) {
            if(job.getJobNumber() == currentJob.getJobNumber()) {
                // This is the first job, print "Current"
                outputFile << "* Current:\n";
                outputFile << "  [Job #" << job.getJobNumber() << "]\n";
                outputFile << "  * Owner: " << job.getUserName() << "\n";
                outputFile << "  * Status: " << job.getStatus() << "\n";
                outputFile << "  * Total pages: " << job.getTotalPages() << " pages\n\n";
            } else {
                // This is not the first job, print "Queue"
                outputFile << "* Queue:\n";
                outputFile << "  [Job #" << job.getJobNumber() << "]\n";
                outputFile << "  * Owner: " << job.getUserName() << "\n";
                outputFile << "  * Status: " << job.getStatus() << "\n";
                outputFile << "  * Total pages: " << job.getTotalPages() << " pages\n\n";
            }
        }
    }

    // Print climate compensation initiatives
    outputFile << "--== Co2 Compensation initiatives ==--\n";
    // Assuming you have a method to retrieve initiatives
    for (const auto &initiative : getClimateCompensationInitiatives())
    {
        outputFile << initiative.getName() << " [#" << initiative.getID() << "]\n";
    }

    // Close output file
    outputFile << "# ======================= #\n";
    outputFile.close();

    // Return true indicating successful generation of the report
    return true;
}


void PrintingSystem::processJob(const std::string &printerName)

{
    // Find printer with the given name
    for (auto& printer : getPrinters()) {
        if (printer.getName() == printerName) {
            while (!printer.getPrinterJobs().empty()){
                Job job = printer.getPrinterJobs().front();
                int pageCount = job.getPageCount();

                // Print all pages of the job
                while (job.getPageCount() > 0) {

                    if (job.getType() == "color") {
                        job.processPage();

                    } else if (job.getType() == "bw") {
                        job.processPage();
                    }

                }


                std::cout << "Printer \"" << printer.getName() << "\" finished job:\n";
                std::cout << "Number: " << job.getJobNumber() << "\n";
                std::cout << "Submitted by \"" << job.getUserName() << "\"\n";
                std::cout << pageCount << " pages\n" << std::endl;


                printer.addCompletedJob(job);
            }
        }
    }
}


void PrintingSystem::addJobsToPrinters(PrintingSystem &system)
{
    Printer &printer = system.getPrinters().front();
    for (Job &job : system.getJobs())
    {
        printer.addJobToPrinter(job);
        system.deleteJob(job.getJobNumber());
    }
}
