#ifndef PARSER_H
#define PARSER_H

#include "coordinate.h"

class Parser
{
public:
    Parser();

    /**
     * @brief parseInput
     * receives line with gps coordinates, recognized format
     * and processes input to method for that format
     * @param line
     * @return coordinates parsed to coordinate class
     */
    Coordinate parseInput(std::string line);

private:

    //methods for individual formats

};

#endif // PARSER_H
