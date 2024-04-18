#include "PrintingSystem.h"

int main() {
    PrintingSystem system;
    system.loadFromFile("valid.xml");
    system.addJobsToPrinters(system);
    system.generateStatusReport("valid_output.txt");
    system.processJob("Office_Printer5");
    return 0;
}