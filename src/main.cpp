#include "PrintingSystem.h"

int main() {
    PrintingSystem* system = new PrintingSystem;


    system->loadFromFileXML("valid.xml");
    //system->loadFromFileXML("job_with_no_suitable_printer.xml");
    //system->loadFromFileXML("missing_cost.xml");
    //system->loadFromFileXML("missing_name.xml");
    //system->loadFromFileXML("no_jobs.xml");
    //system->loadFromFileXML("negative_speed.xml");
    //system->loadFromFileXML("zero_job_number.xml");
    //system->loadFromFileXML("negative_emissions.xml");


    system->addJobsToPrinters(system);
    system->generateStatusReport("valid_output.txt");
    system->processAutomatically(system);
    return 0;
}