#include "Include.h"

class PrintingSystemTest : public ::testing::Test {
    /**
     * Made by Jelle
     * This is a class for testing the xml files
     * **/
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


