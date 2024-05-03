#include "PrintingSystem.h"

int main() {
    PrintingSystem* system = new PrintingSystem;


    system->loadFromFile("valid.xml");
    //system.loadFromFile("job_with_no_suitable_printer.xml");
    //system.loadFromFile("missing_cost.xml");
    //system.loadFromFile("missing_name.xml");
    //system.loadFromFile("no_jobs.xml");
    //system.loadFromFile("negative_speed.xml");
    //system.loadFromFile("zero_job_number.xml");
    //system.loadFromFile("negative_emissions.xml");


    system->addJobsToPrinters(system);
    system->generateStatusReport("valid_output.txt");
    system->processAutomatically(system);
    return 0;
}