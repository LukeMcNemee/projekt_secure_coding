#include "parser.h"
#include <stdexcept>
#include <algorithm>
Parser::Parser()
{
}

Coordinate Parser::parseInput(std::string line){

    std::size_t foundLetter = line.find_first_of("NS");
    std::size_t foundNumber = line.find_first_of("0123456789");

    //if no numbers found in input
    if(foundNumber == std::string::npos){
        throw std::invalid_argument("no numbers found");
    }

    size_t col = Count(":", line);
    size_t deg = Count("°", line);
    size_t aph = Count("\'", line);
    size_t quo = Count("\"", line);
    size_t dot = Count(".", line);

    Coordinate coordinate;
    if(foundLetter == std::string::npos){
        //just numeric
        if(col == 4 && deg == 0 && aph == 0 && quo == 0 && dot == 0){
            coordinate = minus_colon_dms(line);

        } else if (col == 2 && deg == 0 && aph == 0 && quo == 0 && dot == 2){
            coordinate = minus_colon_dm(line);

        } else if (col == 0 && deg == 2 && aph == 2 && quo == 2 && dot == 0){
            coordinate = minus_degree_dms(line);

        } else if (col == 0 && deg == 2 && aph == 2 && quo == 0 && dot == 2){
            coordinate = minus_degree_dm(line);

        } else if (col == 0 && deg == 0 && aph == 0 && quo == 0 && dot == 2){
            coordinate = minus_d(line);

        } else {
            throw std::invalid_argument("wrong pattern");
        }

    } else if (foundLetter < foundNumber){
        //letters in front

        if(col == 4 && deg == 0 && aph == 0 && quo == 0 && dot == 0){
            coordinate = compas_colon_dms(line);

        } else if (col == 2 && deg == 0 && aph == 0 && quo == 0 && dot == 2){
            coordinate = compas_colon_dm(line);

        } else if (col == 0 && deg == 2 && aph == 2 && quo == 2 && dot == 0){
            coordinate = compas_degree_dms(line);

        } else if (col == 0 && deg == 2 && aph == 2 && quo == 0 && dot == 2){
            coordinate = compas_degree_dm(line);

        } else if (col == 0 && deg == 0 && aph == 0 && quo == 0 && dot == 2){
            coordinate = compas_d(line);

        } else {
            throw std::invalid_argument("wrong pattern");
        }

    } else {
        //letters in back

        if(col == 4 && deg == 0 && aph == 0 && quo == 0 && dot == 0){
            coordinate = colon_dms_compas(line);

        } else if (col == 2 && deg == 0 && aph == 0 && quo == 0 && dot == 2){
            coordinate = colon_dm_compas(line);

        } else if (col == 0 && deg == 2 && aph == 2 && quo == 2 && dot == 0){
            coordinate = degree_dms_compas(line);

        } else if (col == 0 && deg == 2 && aph == 2 && quo == 0 && dot == 2){
            coordinate = degree_dm_compas(line);

        } else if (col == 0 && deg == 0 && aph == 0 && quo == 0 && dot == 2){
            coordinate = d_compas(line);

        } else {
            throw std::invalid_argument("wrong pattern");
        }

    }
    return coordinate;
}

int Parser::Count( const std::string & str, const std::string & obj ) {
    int n = 0;
    std::string ::size_type pos = 0;
    while( (pos = obj.find( str, pos ))
                 != std::string::npos ) {
        n++;
        pos += str.size();
    }
    return n;
}

Coordinate Parser::minus_colon_dms(std::string line) {}
Coordinate Parser::minus_colon_dm(std::string line) {}
Coordinate Parser::minus_degree_dms(std::string line) {}
Coordinate Parser::minus_degree_dm(std::string line) {}
Coordinate Parser::minus_d(std::string line) {}

Coordinate Parser::compas_colon_dms(std::string line) {}
Coordinate Parser::compas_colon_dm(std::string line) {}
Coordinate Parser::compas_degree_dms(std::string line) {}
Coordinate Parser::compas_degree_dm(std::string line) {}
Coordinate Parser::compas_d(std::string line) {}

Coordinate Parser::colon_dms_compas(std::string line) {}
Coordinate Parser::colon_dm_compas(std::string line) {}
Coordinate Parser::degree_dms_compas(std::string line) {}
Coordinate Parser::degree_dm_compas(std::string line) {}
Coordinate Parser::d_compas(std::string line) {}
