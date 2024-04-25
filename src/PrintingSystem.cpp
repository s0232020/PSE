#include "PrintingSystem.h"
#include "ClimateCompensationInitiative.h"
#include "../TinyXML/tinyxml.h"
#include "main.h"
#include "Job.h"

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
    float cost = 0;
    std::string printerType = "";
    int jobNumber = 0;
    int pageCount = 0;
    const char* userName = "";
    std::string jobType = "";

    while (element != nullptr)
    {
        const char* elementName = element->Value();

        TiXmlElement* nameElement = element->FirstChildElement("name");
        TiXmlElement* emissionsElement = element->FirstChildElement("emissions");
        TiXmlElement* speedElement = element->FirstChildElement("speed");
        TiXmlElement* costElement = element->FirstChildElement("cost");
        TiXmlElement* printerTypeElement = element->FirstChildElement("type");



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

            if (speedElement)
            {
                speed = std::atoi(speedElement->GetText());
                if (speed < 0){
                    loadError = LoadError::NEGATIVE_VALUE_SPEED;
                }
            }

            if (!costElement)
            {
                loadError = LoadError::MISSING_COST;
            }

            if (costElement)
            {
                cost = std::atof(costElement->GetText());
            }

            if (!printerTypeElement)
            {
                loadError = LoadError::MISSING_PRINTERTYPE;
            }

            if (printerTypeElement)
            {
                printerType = printerTypeElement->GetText();
            }

            Printer printer(name, emissions, speed, cost, printerType);
            addPrinter(printer);

            DeviceSeen = true;

        }
        else if (strcmp(elementName, "JOB") == 0) {
            TiXmlElement* jobNumberElement = element->FirstChildElement("jobNumber");
            TiXmlElement* pageCountElement = element->FirstChildElement("pageCount");
            TiXmlElement* userNameElement = element->FirstChildElement("userName");
            TiXmlElement* jobTypeElement = element->FirstChildElement("type");


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

            if(!jobTypeElement)
            {
                loadError = LoadError::MISSING_JOBTYPE;
            }

            if(jobTypeElement)
            {
                jobType = jobTypeElement->GetText();
            }

            Job job(jobNumber, pageCount, userName, jobType);
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
        case LoadError::MISSING_COST:
            return "Cost missing";
        case LoadError::MISSING_PRINTERTYPE:
            return "Printer type missing";
        case LoadError::MISSING_JOBTYPE:
            return "Job type missing";
        case LoadError::NO_ERROR:
        default:
            return "No error";
    }
}

bool PrintingSystem::generateStatusReport(const std::string &filename)
{
    /**
     * This function generates a status report for the printing system.
     * It includes information about the devices (printers), jobs, and climate compensation initiatives.
     * The report is saved to a file with the given filename.
     * If the report is successfully generated, it returns true; otherwise, it returns false.
     **/

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
        Job currentJob = Job(0, 0, "", "");


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
                outputFile << "  * Total pages: " << job.getPageCount() << " pages\n\n";
            } else {
                // This is not the first job, print "Queue"
                outputFile << "* Queue:\n";
                outputFile << "  [Job #" << job.getJobNumber() << "]\n";
                outputFile << "  * Owner: " << job.getUserName() << "\n";
                outputFile << "  * Status: " << job.getStatus() << "\n";
                outputFile << "  * Total pages: " << job.getPageCount() << " pages\n\n";
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


void PrintingSystem::processJob(const std::string &printerName) {
    /**
     * This function processes the jobs in the printer job queue.
     * It processes each page of the job based on the job type (color, bw, scan).
     * After processing all pages, it moves the job to the completed job queue.
     **/
    for (auto& printer : getPrinters()) {
        if (printer.getName() == printerName) {
            while (!printer.getPrinterJobs().empty()) {
                Job job = printer.getPrinterJobs().front();
                int pageCount = job.getPageCount();
                // Process each page based on the job type
                while (job.getPageCount() > 0) {
                    if (job.getType() == "color" || job.getType() == "bw") {
                        // For printing jobs
                        job.processPage();
                    } else if (job.getType() == "scan") {
                        // For scanning jobs
                        job.scanPage();
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
    /**
     * This function adds all jobs in the system to the first printer in the system.
     * It then deletes the jobs from the system.
     **/

    // First we match the jobs to the printers



    Printer &printer = system.getPrinters().front();
    for (Job &job : system.getJobs())
    {
        printer.addJobToPrinter(job);
        system.deleteJob(job.getJobNumber());
    }
}
