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


TEST_F(PrintingSystemTest, MissingSystemTest){
    system.loadFromFile("missing_system.xml");
    EXPECT_EQ(LoadError::MISSING_SYSTEM, system.loadFromFile("missing_system.xml"));
}

