#include "PrintingSystem.h"
#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>



class PrintingSystemTest : public ::testing::Test {



public:



    bool matchFiles(std::string expectedFileName, std::string filename)
    {
        std::ifstream expectedFile(expectedFileName);
        std::string filenametxt = filename + ".txt";



        systemTest->loadFromFileXML(filename);
        systemTest->addJobsToPrinters(systemTest);



        if (std::filesystem::exists(filenametxt))
        {
            std::ifstream validFile(filenametxt);
            validFile.close();
            std::filesystem::remove(filenametxt);
        }



        systemTest->generateStatusReport(filenametxt);
        std::ifstream validFile(filenametxt);



        // Check if both files are open
        if (!expectedFile.is_open() || !validFile.is_open())
        {
            std::cout << "Failed to open one or more files" << std::endl;
            return false;
        }



        // Read characters from each file and compare them
        char expectedChar, Char;
        while (expectedFile.get(expectedChar) && validFile.get(Char))
        {
            if (expectedChar != Char)
            {
                expectedFile.close();
                validFile.close();
                std::filesystem::remove(filenametxt);
                return false;
            }
        }



        expectedFile.close();
        validFile.close();
        return true;



    }



    int calculateExpectedAddedPages()
    {
        int total_pages = 0;



        for (const Job* job : systemTest->getJobs())
        {
            total_pages += job->getPageCount();
        }



        return total_pages;
    }



    bool matchFilesReleaseTarget(std::string expected_output, std::string actual_output)
    {



        std::ifstream expected_outputtxt(expected_output);
        std::ifstream actual_outputtxt(actual_output);



        if (!expected_outputtxt.is_open() || !actual_outputtxt.is_open())
        {
            std::cout << "Failed to open file: line 69" << std::endl;
            return false;
        }



        char expectedChar, actualChar;
        while (expected_outputtxt.get(expectedChar) && actual_outputtxt.get(actualChar))
        {
            if (expectedChar != actualChar)
            {
                expected_outputtxt.close();
                actual_outputtxt.close();
                return false;
            }
        }



        expected_outputtxt.close();
        actual_outputtxt.close();
        return true;



    }



protected:



    std::streambuf* orig_cout;



    std::ofstream out_file;



    virtual void SetUp() override
    {
        // Save old buf
        orig_cout = std::cout.rdbuf();
        // Open the output file
        out_file.open("test_output.txt");
        // Redirect std::cout to the output file
        std::cout.rdbuf(out_file.rdbuf());
    }



    virtual void TearDown() override
    {
        // Restore old buf
        std::cout.rdbuf(orig_cout);
        // Close the output file
        out_file.close();
    }



    PrintingSystem* systemTest = new PrintingSystem;
};



TEST_F(PrintingSystemTest, MissingName)
{



    std::vector<LoadError> error = systemTest->loadFromFileXML("missing_name.xml");



    if (error.empty()) {std::cout << "Error on the missing name test" << std::endl; FAIL();} // There should definitely be an error



    else if (error.size() > 1) FAIL(); // The test fails because there are multiple errors.



    else if (error.size() == 1) // In this case there is exactly 1 error, which should be the MISSING_NAME error
    {
        LoadError loadError = error.front();
        EXPECT_EQ(LoadError::MISSING_NAME, loadError);
    }



}



TEST_F(PrintingSystemTest, MissingSpeed)
{



    std::vector<LoadError> error = systemTest->loadFromFileXML("missing_speed.xml");



    if (error.empty()) {std::cout << "Error on the missing speed test" << std::endl; FAIL();} // There should definitely be an error



    else if (error.size() > 1) FAIL(); // The test fails because there are multiple errors.



    else if (error.size() == 1) // In this case there is exactly 1 error, which should be the MISSING_SPEED error
    {
        LoadError loadError = error.front();
        EXPECT_EQ(LoadError::MISSING_SPEED, loadError);
    }



}



TEST_F(PrintingSystemTest, MissingEmissions)
{



    std::vector<LoadError> error = systemTest->loadFromFileXML("missing_emissions.xml");



    if (error.empty()) {std::cout << "Error on the missing emissions test" << std::endl; FAIL();} // There should definitely be an error



    else if (error.size() > 1) FAIL(); // The test fails because there are multiple errors.



    else if (error.size() == 1) // In this case there is exactly 1 error, which should be the MISSING_EMISSIONS error
    {
        LoadError loadError = error.front();
        EXPECT_EQ(LoadError::MISSING_EMISSIONS, loadError);
    }



}



TEST_F(PrintingSystemTest, MissingDevice)
{



    std::vector<LoadError> error = systemTest->loadFromFileXML("missing_device.xml");



    if (error.empty()) {std::cout << "Error on the missing device test" << std::endl; FAIL();} // There should definitely be an error



    else if (error.size() > 1) FAIL(); // The test fails because there are multiple errors.



    else if (error.size() == 1) // In this case there is exactly 1 error, which should be the MISSING_DEVICE error
    {
        LoadError loadError = error.front();
        EXPECT_EQ(LoadError::MISSING_DEVICE, loadError);
    }



}



TEST_F(PrintingSystemTest, MissingUser)
{



    std::vector<LoadError> error = systemTest->loadFromFileXML("missing_user.xml");



    if (error.empty()) {std::cout << "Error on the missing username test" << std::endl; FAIL();} // There should definitely be an error



    else if (error.size() > 1) FAIL(); // The test fails because there are multiple errors.



    else if (error.size() == 1) // In this case there is exactly 1 error, which should be the MISSING_USER_NAME error
    {
        LoadError loadError = error.front();
        EXPECT_EQ(LoadError::MISSING_USER_NAME, loadError);
    }



}



TEST_F(PrintingSystemTest, MissingJobNumber)
{



    std::vector<LoadError> error = systemTest->loadFromFileXML("missing_job_number.xml");



    if (error.empty()) {std::cout << "Error on the missing job number test" << std::endl; FAIL();} // There should definitely be an error



    else if (error.size() > 1) FAIL(); // The test fails because there are multiple errors.



    else if (error.size() == 1) // In this case there is exactly 1 error, which should be the MISSING_JOB_NUMBER error
    {
        LoadError loadError = error.front();
        EXPECT_EQ(LoadError::MISSING_JOB_NUMBER, loadError);
    }



}



TEST_F(PrintingSystemTest, MissingPC)
{



    std::vector<LoadError> error = systemTest->loadFromFileXML("missing_page_count.xml");



    if (error.empty()) {std::cout << "Error on the missing missing page count test" << std::endl; FAIL();} // There should definitely be an error



    else if (error.size() > 1) FAIL(); // The test fails because there are multiple errors.



    else if (error.size() == 1) // In this case there is exactly 1 error, which should be the MISSING_PAGE_COUNT error
    {
        LoadError loadError = error.front();
        EXPECT_EQ(LoadError::MISSING_PAGE_COUNT, loadError);
    }



}



TEST_F(PrintingSystemTest, NegativeEmissions)
{



    std::vector<LoadError> error = systemTest->loadFromFileXML("negative_emissions.xml");



    if (error.empty()) {std::cout << "Error on the negative emissions test" << std::endl; FAIL();} // There should definitely be an error



    else if (error.size() > 1) FAIL(); // The test fails because there are multiple errors.



    else if (error.size() == 1) // In this case there is exactly 1 error, which should be the NEGATIVE_EMISSIONS_VALUE error
    {
        LoadError loadError = error.front();
        EXPECT_EQ(LoadError::NEGATIVE_VALUE_EMISSIONS, loadError);
    }



}



TEST_F(PrintingSystemTest, NegativePC)
{



    std::vector<LoadError> error = systemTest->loadFromFileXML("negative_page_count.xml");



    if (error.empty()) {std::cout << "Error on the negative page count test" << std::endl; FAIL();} // There should definitely be an error



    else if (error.size() > 1) FAIL(); // The test fails because there are multiple errors.



    else if (error.size() == 1) // In this case there is exactly 1 error, which should be the NEGATIVE_PAGE_COUNT error
    {
        LoadError loadError = error.front();
        EXPECT_EQ(LoadError::NEGATIVE_VALUE_PAGE_COUNT, loadError);
    }



}



TEST_F(PrintingSystemTest, NegativeJobNumber)
{



    std::vector<LoadError> error = systemTest->loadFromFileXML("negative_job_number.xml");



    if (error.empty()) {std::cout << "Error on the negative job number test" << std::endl; FAIL();} // There should definitely be an error



    else if (error.size() > 1) FAIL(); // The test fails because there are multiple errors.



    else if (error.size() == 1) // In this case there is exactly 1 error, which should be the NEGATIVE_VALUE_JOB_NUMBER error
    {
        LoadError loadError = error.front();
        EXPECT_EQ(LoadError::NEGATIVE_VALUE_JOB_NUMBER, loadError);
    }



}



TEST_F(PrintingSystemTest, NegativeSpeed)
{



    std::vector<LoadError> error = systemTest->loadFromFileXML("negative_speed.xml");



    if (error.empty()) {std::cout << "Error on the negative speed test" << std::endl; FAIL();} // There should definitely be an error



    else if (error.size() > 1) FAIL(); // The test fails because there are multiple errors.



    else if (error.size() == 1) // In this case there is exactly 1 error, which should be the NEGATIVE_VALUE_SPEED error
    {
        LoadError loadError = error.front();
        EXPECT_EQ(LoadError::NEGATIVE_VALUE_SPEED, loadError);
    }



}



TEST_F(PrintingSystemTest, ValidFile)
{



    std::vector<LoadError> error = systemTest->loadFromFileXML("valid.xml");



    if (error.empty()) SUCCEED();



    else FAIL();



}




TEST_F(PrintingSystemTest, HappyDay)
{



    // Assert whether files match or not
    EXPECT_TRUE(matchFiles("expected_output.txt", "valid.xml"));
    EXPECT_FALSE(matchFiles("non_expected_output.txt", "valid.xml"));



}



TEST_F(PrintingSystemTest, AddJobsToPrintersPrintsErrorMessageForJobWithNoSuitablePrinter)
{
    /*
     * The test is checking if the error message is found in the output file.
     * The std::string::find method returns the position of the first occurrence
     * of the substring in the string. If the substring is not found,
     * it returns std::string::npos.
     */
    systemTest->loadFromFileXML("job_with_no_suitable_printer.xml");
    systemTest->addJobsToPrinters(systemTest);



    // Open the output file
    std::ifstream in_file("test_output.txt");
    // Read the file's contents
    std::string output((std::istreambuf_iterator<char>(in_file)), std::istreambuf_iterator<char>());



    // Check if the error message is in the file's contents
    EXPECT_NE(output.find("Error: No device exists for the job type bw. The job could not be printed."), std::string::npos);



}



TEST_F(PrintingSystemTest, MatchFilesReturnsFalseForMismatchedFiles)
{



    bool result = matchFiles("expected_output.txt", "invalid.xml");
    EXPECT_FALSE(result);



}



TEST_F(PrintingSystemTest, MatchFilesReturnsTrueForIdenticalFiles)
{



    bool result = matchFiles("expected_output.txt", "valid.xml");
    EXPECT_TRUE(result);



}



TEST_F(PrintingSystemTest, CalculateExpectedAddedPagesReturnsCorrectTotalForMultipleJobs)
{



    systemTest->loadFromFileXML("multiple_jobs.xml");
    int expectedPages = calculateExpectedAddedPages();
    EXPECT_EQ(expectedPages, 50); // assuming the total pages in multiple_jobs.xml.xml is 50



}



TEST_F(PrintingSystemTest, AddJobsToPrintersIncreasesQueuePagesForValidJobs)
{



    systemTest->loadFromFileXML("valid.xml");
    Printer* printer = systemTest->getPrinters().back();
    int initialQueuePages = printer->getQueuePages();
    systemTest->addJobsToPrinters(systemTest);
    EXPECT_GT(printer->getQueuePages(), initialQueuePages);



}



TEST_F(PrintingSystemTest, TestReleaseTargetOutput)
{



    // Save the old buffer
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();

    // Open your file
    std::ofstream out("release_target_actual_output.txt");

    // Redirect std::cout to your file
    std::cout.rdbuf(out.rdbuf());

    // Now, everything you print to std::cout will go to output.txt
    systemTest->loadFromFileXML("valid.xml");
    systemTest->addJobsToPrinters(systemTest);
    systemTest->processAutomatically(systemTest);

    // When done, restore the old std::cout buffer
    std::cout.rdbuf(oldCoutBuffer);

    bool result = matchFilesReleaseTarget("release_target_expected_output.txt", "release_target_actual_output.txt");
    EXPECT_TRUE(result);



}



TEST_F(PrintingSystemTest, AddJobsToPrintersHandlesEmptyJobList)
{



    systemTest->loadFromFileXML("no_jobs.xml");
    EXPECT_NO_THROW(systemTest->addJobsToPrinters(systemTest));



}



TEST_F(PrintingSystemTest, GenerateStatusReportCreatesFileWithCorrectName)
{



    systemTest->loadFromFileXML("valid.xml");
    systemTest->addJobsToPrinters(systemTest);
    systemTest->generateStatusReport("status_report.txt");
    EXPECT_TRUE(std::filesystem::exists("status_report.txt"));



}



TEST_F(PrintingSystemTest, ProcessAutomaticallyHandlesNoJobsInQueue)
{



    systemTest->loadFromFileXML("no_jobs.xml");
    EXPECT_NO_THROW(systemTest->processAutomatically(systemTest));



}



TEST_F(PrintingSystemTest, MatchFilesHandlesNonExistentFiles)
{



    bool result = matchFiles("non_existent.txt", "valid.xml");
    EXPECT_FALSE(result);



}



TEST_F(PrintingSystemTest, CalculateExpectedAddedPagesReturnsZeroForNoJobs)
{



    systemTest->loadFromFileXML("no_jobs.xml");
    int expectedPages = calculateExpectedAddedPages();
    EXPECT_EQ(expectedPages, 0);



}