#ifndef TRANSPORTCONTAINER_H
#define TRANSPORTCONTAINER_H

#include <vector>
#include <string>
#include "Transport.h"

class TransportContainer {
private:
    std::vector<Transport*> vehicles;

public:
    ~TransportContainer();

    void add(Transport* vehicle);
    void remove(const std::string& condition);
    void printAll() const;
    int getSize() const { return vehicles.size(); }
};

#endif