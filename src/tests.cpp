#include "PrintingSystem.h"
#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>



class PrintingSystemTest : public ::testing::Test {
    /**
     * This is a class for testing the xml files
     **/
public:
    bool matchFiles(std::string expectedFileName, std::string filename){
        std::ifstream expectedFile(expectedFileName);
        std::string filenametxt = filename + ".txt";
        systemTest.loadFromFile(filename);
        systemTest.addJobsToPrinters(systemTest);
//        if (std::filesystem::exists(filenametxt))
//        {
//            std::ifstream validFile(filenametxt);
//            validFile.close();
//            std::filesystem::remove(filenametxt);
//        }
        systemTest.generateStatusReport(filenametxt);
        std::ifstream validFile(filenametxt);

        // Check if both files are open
        if (!expectedFile.is_open() || !validFile.is_open()) {
            std::cerr << "Failed to open one or more files" << std::endl;
        }

        // Read characters from each file and compare them
        char expectedChar, Char;
        while (expectedFile.get(expectedChar) && validFile.get(Char)) {
            if (expectedChar != Char) {
                expectedFile.close();
                validFile.close();
                std::filesystem::remove(filenametxt);
                return false;
            }
        }
        expectedFile.close();
        validFile.close();
        std::filesystem::remove(filenametxt);
        return true;
    }

protected:
    virtual void SetUp() override {}
    virtual void TearDown() override {}
    PrintingSystem systemTest;
};


TEST_F(PrintingSystemTest, MissingTests){
    LoadError error = systemTest.loadFromFile("missing_name.xml");
    EXPECT_EQ(LoadError::MISSING_NAME, error);

    error = systemTest.loadFromFile("missing_speed.xml");
    EXPECT_EQ(LoadError::MISSING_SPEED, error);

    error = systemTest.loadFromFile("missing_emissions.xml");
    EXPECT_EQ(LoadError::MISSING_EMISSIONS, error);

    error = systemTest.loadFromFile("missing_device.xml");
    EXPECT_EQ(LoadError::MISSING_DEVICE, error);

    error = systemTest.loadFromFile("missing_user.xml");
    EXPECT_EQ(LoadError::MISSING_USER_NAME, error);

    error = systemTest.loadFromFile("missing_job_number.xml");
    EXPECT_EQ(LoadError::MISSING_JOB_NUMBER, error);

    error = systemTest.loadFromFile("missing_page_count.xml");
    EXPECT_EQ(LoadError::MISSING_PAGE_COUNT, error);

    error = systemTest.loadFromFile("negative_emissions.xml");
    EXPECT_EQ(LoadError::NEGATIVE_VALUE_EMISSIONS, error);

    error = systemTest.loadFromFile("negative_page_count.xml");
    EXPECT_EQ(LoadError::NEGATIVE_VALUE_PAGE_COUNT, error);

    error = systemTest.loadFromFile("negative_job_number.xml");
    EXPECT_EQ(LoadError::NEGATIVE_VALUE_JOB_NUMBER, error);

    error = systemTest.loadFromFile("negative_speed.xml");
    EXPECT_EQ(LoadError::NEGATIVE_VALUE_SPEED, error);

    error = systemTest.loadFromFile("valid.xml");
    EXPECT_EQ(LoadError::NO_ERROR, error);
}

TEST_F(PrintingSystemTest, HappyDay) {
    // Assert whether files match or not
    EXPECT_TRUE(matchFiles("expected_output.txt", "valid.xml"));
    EXPECT_FALSE(matchFiles("non_expected_output.txt", "valid.xml"));
}