#include "Include.h"


class PrintingSystemTest : public ::testing::Test {
    /**
     * This is a class for testing the xml files
     **/
public:
    bool matchFiles(std::string expectedFileName, std::string filename){
        std::ifstream expectedFile(expectedFileName);
        std::string filenametxt = filename + ".txt";
        if(!std::ifstream(filenametxt)){
            system.loadFromFile(filename);
            system.generateStatusReport(filenametxt);
        }
        std::ifstream validFile(filenametxt);

        // Check if both files are open
        if (!expectedFile.is_open() || !validFile.is_open()) {
            std::cerr << "Failed to open one or more files" << std::endl;
        }

        // Read characters from each file and compare them
        char expectedChar, Char;
        int position = 0;
        while (expectedFile.get(expectedChar) && validFile.get(Char)) {
            if (expectedChar != Char) {
                return false;
            }
            position++;
        }

        return true;
        expectedFile.close();
        validFile.close();
    }

protected:
    virtual void SetUp() override {}
    virtual void TearDown() override {}
    PrintingSystem system;
};


TEST_F(PrintingSystemTest, MissingTests){
    LoadError error = system.loadFromFile("missing_name.xml");
    EXPECT_EQ(LoadError::MISSING_NAME, error);

    error = system.loadFromFile("missing_speed.xml");
    EXPECT_EQ(LoadError::MISSING_SPEED, error);

    error = system.loadFromFile("missing_emissions.xml");
    EXPECT_EQ(LoadError::MISSING_EMISSIONS, error);

    error = system.loadFromFile("missing_device.xml");
    EXPECT_EQ(LoadError::MISSING_DEVICE, error);

    error = system.loadFromFile("missing_user.xml");
    EXPECT_EQ(LoadError::MISSING_USER_NAME, error);

    error = system.loadFromFile("missing_job_number.xml");
    EXPECT_EQ(LoadError::MISSING_JOB_NUMBER, error);

    error = system.loadFromFile("missing_page_count.xml");
    EXPECT_EQ(LoadError::MISSING_PAGE_COUNT, error);

    error = system.loadFromFile("negative_emissions.xml");
    EXPECT_EQ(LoadError::NEGATIVE_VALUE_EMISSIONS, error);

    error = system.loadFromFile("negative_page_count.xml");
    EXPECT_EQ(LoadError::NEGATIVE_VALUE_PAGE_COUNT, error);

    error = system.loadFromFile("negative_job_number.xml");
    EXPECT_EQ(LoadError::NEGATIVE_VALUE_JOB_NUMBER, error);

    error = system.loadFromFile("negative_speed.xml");
    EXPECT_EQ(LoadError::NEGATIVE_VALUE_SPEED, error);

    error = system.loadFromFile("valid.xml");
    EXPECT_EQ(LoadError::NO_ERROR, error);
}

TEST_F(PrintingSystemTest, HappyDay) {
    // Assert whether files match or not
    EXPECT_TRUE(matchFiles("expected_output.txt", "valid.xml"));
    EXPECT_FALSE(matchFiles("non_expected_output.txt", "valid.xml"));
}