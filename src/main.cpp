#include "Include.h"


int main() {
    PrintingSystem system;
    system.loadFromFile("valid.xml");
    system.generateStatusReport("valid_output.txt");
    system.processJob("Office_Printer5");
    return 0;
}