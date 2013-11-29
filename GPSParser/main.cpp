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
            if(line.find_first_not_of(' ') != std::string::npos){
                coordinates.push_back(parser.parseInput(line));
            }
        } catch (const std::invalid_argument& e){
            std::cerr << "Exception occured on line : " << line << "  "
                      << e.what() << std::endl;
        }

        if(fileOpen){
            if(!(file.good())){
                break;
            }
            std::getline(file, line);
        } else {
            std::getline(std::cin, line);
        }
    }

    //print to cout all coordinates in vector by calling to string method

    //TODO: foreach cooordinates toString / toSVG ...

    std::ofstream svgFile;
    svgFile.open("map.svg", std::fstream::out);
    if (!(svgFile.is_open()))
        {
            std::cerr << "Cannot open file map.svg for writing." << std::endl;
            return 1;
        }

    svgFile << "<!DOCTYPE html><html><body><svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">" << std::endl;
    svgFile << "<line x1=\"360\" y1=\"0\" x2=\"360\" y2=\"360\" style=\"stroke:black;stroke-width:1\" />" << std::endl;
    svgFile << "<line x1=\"0\" y1=\"180\" x2=\"720\" y2=\"180\" style=\"stroke:black;stroke-width:1\" />" << std::endl;

    for(std::vector<Coordinate>::iterator it = coordinates.begin(); it != coordinates.end(); ++it) {
        svgFile << it -> toSVG();
    }

    svgFile << "</svg></body></html>";
    svgFile.close();


    if(fileOpen){
        file.close();
    }
    return 0;
}

