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
            //(-)ddd:mm:ss (-)ddd:mm:ss

        } else if (col == 2 && deg == 0 && aph == 0 && quo == 0 && dot == 2){
            //(-)ddd:mm.mmmmm (-)ddd:mm.mmmmm

        } else if (col == 0 && deg == 2 && aph == 2 && quo == 2 && dot == 0){
            //(-)ddd°mm'ss", (-)ddd°mm'ss"

        } else if (col == 0 && deg == 2 && aph == 2 && quo == 0 && dot == 2){
            //(-)ddd°mm.mmmmm', (-)ddd°mm.mmmmm'

        } else if (col == 0 && deg == 0 && aph == 0 && quo == 0 && dot == 2){
            //(-)ddd.dddddd, (-)ddd.dddddd

        } else {
            throw std::invalid_argument("wrong pattern");
        }

    } else if (foundLetter < foundNumber){
        //letters in front

        if(col == 4 && deg == 0 && aph == 0 && quo == 0 && dot == 0){
            //[NS]ddd:mm:ss.sss [WE]ddd:mm:ss.sss

        } else if (col == 2 && deg == 0 && aph == 0 && quo == 0 && dot == 2){
            //[NS]ddd:mm.mmmmm [WE]ddd:mm.mmmmm

        } else if (col == 0 && deg == 2 && aph == 2 && quo == 2 && dot == 0){
            //[NS]ddd°mm'ss" [WE]ddd°mm'ss

        } else if (col == 0 && deg == 2 && aph == 2 && quo == 0 && dot == 2){
            //[NS]ddd°mm.mmmmm' [WE]ddd°mm.mmmmm'

        } else if (col == 0 && deg == 0 && aph == 0 && quo == 0 && dot == 2){
            //[NS]ddd.dddddd [WE]ddd.dddddd

        } else {
            throw std::invalid_argument("wrong pattern");
        }

    } else {
        //letters in back

        if(col == 4 && deg == 0 && aph == 0 && quo == 0 && dot == 0){
            //ddd:mm:ss[NS] ddd:mm:ss[WE]

        } else if (col == 2 && deg == 0 && aph == 0 && quo == 0 && dot == 2){
            //ddd:mm.mmmmm[NS] ddd:mm.mmmmm[WE]

        } else if (col == 0 && deg == 2 && aph == 2 && quo == 2 && dot == 0){
            //ddd°mm.mmmmm'[NS] ddd°mm.mmmmm'[WE]

        } else if (col == 0 && deg == 2 && aph == 2 && quo == 0 && dot == 2){
            //ddd°mm.mmmmm'[NS] ddd°mm.mmmmm'[WE]

        } else if (col == 0 && deg == 0 && aph == 0 && quo == 0 && dot == 2){
            //ddd.dddddd[NS] ddd.dddddd[WE]

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
