//
// Created by Muaz Moin on 22/04/2024.
//

#ifndef PROJECTTITLE_CLIMATECOMPENSATIONINITIATIVE_H
#define PROJECTTITLE_CLIMATECOMPENSATIONINITIATIVE_H

#include <string>

class ClimateCompensationInitiative {
private:
    std::string name_;
    int ID_;

public:
    // Constructor
    ClimateCompensationInitiative(const std::string& name, int ID)
            : name_(name), ID_(ID) {}

    // Getter methods
    std::string getName() const {
        return name_;
    }

    int getID() const {
        return ID_;
    }
};


#endif //PROJECTTITLE_CLIMATECOMPENSATIONINITIATIVE_H
