#include <iostream>

#include "parser.h"
#include "coordinate.h"
#include <vector>
int main(int argc, char* argv[])
{    
    //check argc if there is filepath

    //create instance of parser, read lines of input and store results as coordinates
    std::vector<Coordinate> coordinates;
    Parser parser;

    //process lines
    parser.parseInput();

    //print to cout all coordinates in vector by calling to string method
    return 0;
}

