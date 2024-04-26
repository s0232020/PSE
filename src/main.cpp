#include "PrintingSystem.h"

int main() {
    PrintingSystem system;
    system.loadFromFile("valid.xml");
    //system.loadFromFile("job_with_no_suitable_printer.xml");
    system.addJobsToPrinters(system);
    system.generateStatusReport("valid_output.txt");
    system.processJob("Office_Printer5");
    system.processAutomatically(system);
    return 0;
}