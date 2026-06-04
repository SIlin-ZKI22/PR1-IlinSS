#ifndef FILECOMMANDREADER_H
#define FILECOMMANDREADER_H

#include <string>
#include "TransportContainer.h"

class FileCommandReader {
private:
    std::string filename;

    void processCommand(const std::string& line, TransportContainer& container);
    void processAdd(std::istringstream& iss, TransportContainer& container);

public:
    explicit FileCommandReader(const std::string& fname);
    void readAndExecute(TransportContainer& container);
};

#endif