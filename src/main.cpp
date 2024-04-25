#include "PrintingSystem.h"

int main() {
    PrintingSystem system;
    system.loadFromFile("missing_device_for_job_type.xml");
    system.addJobsToPrinters(system);
    system.generateStatusReport("valid_output.txt");
    system.processJob("Office_Printer5");
    system.processAutomatically(system);
    return 0;
}