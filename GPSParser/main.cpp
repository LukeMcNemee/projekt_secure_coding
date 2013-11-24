#include <iostream>
#include <istream>
#include <fstream>
#include "parser.h"
#include "coordinate.h"
#include <vector>
#include <stdexcept>
int main(int argc, char* argv[])
{    
    //check argc if there is filepath    
    bool fileOpen = false;
    std::ifstream file;
    if(argc == 2){
        std::string filepath = argv[1];
        file.open(filepath.c_str(), std::fstream::in);
        if (!(file.is_open()))
        {
            std::cerr << "input file error" << std::endl;
            return 1;
        }
        fileOpen = true;
    } else {
        std::cout << "no file specified, waiting for command line input" << std::endl;
        std::cout << "write \"quit\" to quit application" << std::endl;
    }

    //create instance of parser, read lines of input and store results as coordinates
    std::vector<Coordinate> coordinates;
    Parser parser;

    //std::istream input = std::cin;

    std::string line;
    if(fileOpen){
        std::getline(file, line);
    } else {
        std::getline(std::cin, line);
    }

    //process lines
    while(line != "quit"){
        try{
            coordinates.push_back(parser.parseInput(line));
        } catch (const std::invalid_argument& e){
            std::cerr << "wrong format of input " << e.what() << std::endl;
        }

        if(fileOpen){
            std::getline(file, line);
        } else {
            std::getline(std::cin, line);
        }
    }

    //print to cout all coordinates in vector by calling to string method

    //TODO: foreach cooordinates toString / toSVG ...


    if(fileOpen){
        file.close();
    }
    return 0;
}

