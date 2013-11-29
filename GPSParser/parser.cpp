#include "parser.h"
#include <stdexcept>
#include <algorithm>
#include <math.h>

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
    size_t deg = Count("�", line);
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
            coordinate = minus_colon_d(line);

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
            coordinate = compas_colon_d(line);

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
            coordinate = colon_d_compas(line);

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

Coordinate Parser::minus_colon_dms(std::string line) {

    enum states {start, lat_minus, lat_deg, lat_colon1, lat_min, lat_colon2, lat_sec, space, lon_minus, lon_deg, lon_colon1, lon_min, lon_colon2, lon_sec, done};
    states state = start;

    std::string deg_lat = "";
    std::string min_lat = "";
    std::string sec_lat = "";
    char compas_lat = 'N';

    std::string deg_lon = "";
    std::string min_lon = "";
    std::string sec_lon = "";
    char compas_lon = 'E';

    for(unsigned int iterator = 0; iterator <= line.size(); ++iterator) {
        char c = line[iterator];
            switch (c) {
                case ' ':
                    if(state == lat_sec) state = space;
                    else if(state == lon_sec) state = done;
                    else if(state != start && state != space && state != done) throw std::invalid_argument("Wrong space character.");
                    break;

                case '-' :
                    if(state == start) {
                        compas_lat = 'S';
                        state = lat_minus;
                    }
                    else if(state == space) {
                        compas_lon = 'W';
                        state = lon_minus;
                    }
                    else throw std::invalid_argument("Wrong '-' character.");
                    break;

                case ':' :
                    if(state == lat_deg) state = lat_colon1;
                    else if(state == lat_min) state = lat_colon2;
                    else if(state == lon_deg) state = lon_colon1;
                    else if(state == lon_min) state = lon_colon2;
                    else throw std::invalid_argument("Wrong ':' character.");
                    break;

                case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
                    if(state == start || state == lat_minus || state == lat_deg) {
                        if(deg_lat.size() >= 2) throw std::invalid_argument("Latitude degrees too long.");
                        deg_lat += c;
                        state = lat_deg;
                    }
                    else if(state == lat_colon1 || state == lat_min) {
                        if(min_lat.size() >= 2) throw std::invalid_argument("Latitude minutes too long.");
                        min_lat += c;
                        state = lat_min;
                    }
                    else if(state == lat_colon2 || state == lat_sec) {
                        if(sec_lat.size() >= 2) throw std::invalid_argument("Latitude seconds too long.");
                        sec_lat += c;
                        state = lat_sec;
                    }
                    else if(state == space || state == lon_minus || state == lon_deg) {
                        if(deg_lon.size() >= 3) throw std::invalid_argument("Longitude degrees too long.");
                        deg_lon += c;
                        state = lon_deg;
                    }
                    else if(state == lon_colon1 || state == lon_min) {
                        if(min_lon.size() >= 2) throw std::invalid_argument("Longitude minutes too long.");
                        min_lon += c;
                        state = lon_min;
                    }
                    else if(state == lon_colon2 || state == lon_sec) {
                        if(sec_lon.size() >= 2) throw std::invalid_argument("Longitude seconds too long.");
                        sec_lon += c;
                        state = lon_sec;
                    }
                    else throw std::invalid_argument("Wrong number.");
                    break;

                case '\0':
                    if(state != lon_sec && state != done) throw std::invalid_argument("Input too short.");
                    break;

                default: throw std::invalid_argument("Character not allowed.");
                    break;
            }
    }

    Coordinate coordinate;

    coordinate.setLatitudeCompas(compas_lat);
    if(atoi(deg_lat.c_str()) > 90) throw std::invalid_argument("Latitude degrees too big.");
    coordinate.setLatitudeDegrees(atoi(deg_lat.c_str()));
    if(atoi(min_lat.c_str()) > 59 || (atoi(deg_lat.c_str()) == 90 && atoi(min_lat.c_str()) != 0)) throw std::invalid_argument("Latitude minutes too big.");
    coordinate.setLatitudeMinutes(atoi(min_lat.c_str()));
    if(atoi(sec_lat.c_str()) > 59 || (atoi(deg_lat.c_str()) == 90 && atoi(sec_lat.c_str()) != 0)) throw std::invalid_argument("Latitude seconds too big.");
    coordinate.setLatitudeSeconds(atoi(sec_lat.c_str()));

    coordinate.setLongitudeCompas(compas_lon);
    if(atoi(deg_lon.c_str()) > 180) throw std::invalid_argument("Longitude degrees too big.");
    coordinate.setLongitudeDegrees(atoi(deg_lon.c_str()));
    if(atoi(min_lon.c_str()) > 59 || (atoi(deg_lon.c_str()) == 180 && atoi(min_lon.c_str()) != 0)) throw std::invalid_argument("Longitude minutes too big.");
    coordinate.setLongitudeMinutes(atoi(min_lon.c_str()));
    if(atoi(sec_lon.c_str()) > 59 || (atoi(deg_lon.c_str()) == 180 && atoi(sec_lon.c_str()) != 0)) throw std::invalid_argument("Longitude seconds too big.");
    coordinate.setLongitudeSeconds(atoi(sec_lon.c_str()));

    return coordinate;
}

Coordinate Parser::minus_colon_dm(std::string line) {

    enum states {start, lat_minus, lat_deg, lat_colon, lat_minnum, lat_dot, lat_mindec, space, lon_minus, lon_deg, lon_colon, lon_minnum, lon_dot, lon_mindec, done};
    states state = start;

    std::string deg_lat = "";
    std::string min_lat = "";
    char compas_lat = 'N';

    std::string deg_lon = "";
    std::string min_lon = "";
    char compas_lon = 'E';

    for(unsigned int iterator = 0; iterator <= line.size(); ++iterator) {
        char c = line[iterator];
            switch (c) {
                case ' ':
                    if(state == lat_minnum || state == lat_mindec) state = space;
                    else if(state == lon_minnum || state == lon_mindec) state = done;
                    else if(state != start && state != space && state != done) throw std::invalid_argument("Wrong space character.");
                    break;

                case '-' :
                    if(state == start) {
                        compas_lat = 'S';
                        state = lat_minus;
                    }
                    else if(state == space) {
                        compas_lon = 'W';
                        state = lon_minus;
                    }
                    else throw std::invalid_argument("Wrong '-' character.");
                    break;

                case ':' :
                    if(state == lat_deg) state = lat_colon;
                    else if(state == lon_deg) state = lon_colon;
                    else throw std::invalid_argument("Wrong ':' character.");
                    break;

                case '.' :
                    if(state == lat_minnum) {
                        min_lat += c;
                        state = lat_dot;
                    }
                    else if(state == lon_minnum) {
                        min_lon += c;
                        state = lon_dot;
                    }
                    else throw std::invalid_argument("Wrong '.' character.");
                    break;

                case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
                    if(state == start || state == lat_minus || state == lat_deg) {
                        if(deg_lat.size() >= 2) throw std::invalid_argument("Latitude degrees too long.");
                        deg_lat += c;
                        state = lat_deg;
                    }
                    else if(state == lat_colon || state == lat_minnum) {
                        if(min_lat.size() >= 2) throw std::invalid_argument("Latitude minutes too long.");
                        min_lat += c;
                        state = lat_minnum;
                    }
                    else if(state == lat_dot || state == lat_mindec) {
                        if(min_lat.size() < 7) min_lat += c;
                        state = lat_mindec;
                    }
                    else if(state == space || state == lon_minus || state == lon_deg) {
                        if(deg_lon.size() >= 3) throw std::invalid_argument("Longitude degrees too long.");
                        deg_lon += c;
                        state = lon_deg;
                    }
                    else if(state == lon_colon || state == lon_minnum) {
                        if(min_lon.size() >= 2) throw std::invalid_argument("Longitude minutes too long.");
                        min_lon += c;
                        state = lon_minnum;
                    }
                    else if(state == lon_dot || state == lon_mindec) {
                        if(min_lon.size() < 7) min_lon += c;
                        state = lon_mindec;
                    }
                    else throw std::invalid_argument("Wrong number.");
                    break;

                case '\0':
                    if(state != lon_minnum && state != lon_mindec && state != done) throw std::invalid_argument("Input too short.");
                    break;

                default: throw std::invalid_argument("Character not allowed.");
                    break;
            }
    }

    Coordinate coordinate;

    double float_minutes_lat = atof(min_lat.c_str());
    double float_seconds_lat = (float_minutes_lat - floor(float_minutes_lat)) * 60;

    coordinate.setLatitudeCompas(compas_lat);
    coordinate.setLatitudeDegrees(atoi(deg_lat.c_str()));
    coordinate.setLatitudeMinutes((unsigned short) floor(float_minutes_lat));
    coordinate.setLatitudeSeconds((unsigned short) floor(float_seconds_lat + 0.5));

    double float_minutes_lon = atof(min_lon.c_str());
    double float_seconds_lon = (float_minutes_lon - floor(float_minutes_lon)) * 60;

    coordinate.setLongitudeCompas(compas_lon);
    coordinate.setLongitudeDegrees(atoi(deg_lon.c_str()));
    coordinate.setLongitudeMinutes((unsigned short) floor(float_minutes_lon));
    coordinate.setLongitudeSeconds((unsigned short) floor(float_seconds_lon + 0.5));

    return coordinate;
}

Coordinate Parser::minus_colon_d(std::string line) {}
Coordinate Parser::minus_degree_dms(std::string line) {}
Coordinate Parser::minus_degree_dm(std::string line) {}
Coordinate Parser::minus_degree_d(std::string line) {}

Coordinate Parser::compas_colon_dms(std::string line) {

    enum states {start, lat_compas, lat_deg, lat_colon1, lat_min, lat_colon2, lat_sec, space, lon_compas, lon_deg, lon_colon1, lon_min, lon_colon2, lon_sec, done};
    states state = start;

    std::string deg_lat = "";
    std::string min_lat = "";
    std::string sec_lat = "";
    char compas_lat = 'N';

    std::string deg_lon = "";
    std::string min_lon = "";
    std::string sec_lon = "";
    char compas_lon = 'E';

    for(unsigned int iterator = 0; iterator <= line.size(); ++iterator) {
        char c = line[iterator];
            switch (c) {
                case ' ':
                    if(state == lat_sec) state = space;
                    else if(state == lon_sec) state = done;
                    else if(state != start && state != space && state != done) throw std::invalid_argument("Wrong space character.");
                    break;

                case 'N' : case 'S' :
                    if(state == start) {
                        compas_lat = c;
                        state = lat_compas;
                    }
                    else throw std::invalid_argument("Wrong latitude compas.");
                    break;

                case 'E' : case 'W' :
                    if(state == space) {
                        compas_lon = c;
                        state = lon_compas;
                    }
                    else throw std::invalid_argument("Wrong longitude compas.");
                    break;

                case ':' :
                    if(state == lat_deg) state = lat_colon1;
                    else if(state == lat_min) state = lat_colon2;
                    else if(state == lon_deg) state = lon_colon1;
                    else if(state == lon_min) state = lon_colon2;
                    else throw std::invalid_argument("Wrong ':' character.");
                    break;

                case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
                    if(state == lat_compas || state == lat_deg) {
                        if(deg_lat.size() >= 2) throw std::invalid_argument("Latitude degrees too long.");
                        deg_lat += c;
                        state = lat_deg;
                    }
                    else if(state == lat_colon1 || state == lat_min) {
                        if(min_lat.size() >= 2) throw std::invalid_argument("Latitude minutes too long.");
                        min_lat += c;
                        state = lat_min;
                    }
                    else if(state == lat_colon2 || state == lat_sec) {
                        if(sec_lat.size() >= 2) throw std::invalid_argument("Latitude seconds too long.");
                        sec_lat += c;
                        state = lat_sec;
                    }
                    else if(state == lon_compas || state == lon_deg) {
                        if(deg_lon.size() >= 3) throw std::invalid_argument("Longitude degrees too long.");
                        deg_lon += c;
                        state = lon_deg;
                    }
                    else if(state == lon_colon1 || state == lon_min) {
                        if(min_lon.size() >= 2) throw std::invalid_argument("Longitude minutes too long.");
                        min_lon += c;
                        state = lon_min;
                    }
                    else if(state == lon_colon2 || state == lon_sec) {
                        if(sec_lon.size() >= 2) throw std::invalid_argument("Longitude seconds too long.");
                        sec_lon += c;
                        state = lon_sec;
                    }
                    else throw std::invalid_argument("Wrong number.");
                    break;

                case '\0':
                    if(state != lon_sec && state != done) throw std::invalid_argument("Input too short.");
                    break;

                default: throw std::invalid_argument("Character not allowed.");
                    break;
            }
    }

    Coordinate coordinate;

    coordinate.setLatitudeCompas(compas_lat);
    if(atoi(deg_lat.c_str()) > 90) throw std::invalid_argument("Latitude degrees too big.");
    coordinate.setLatitudeDegrees(atoi(deg_lat.c_str()));
    if(atoi(min_lat.c_str()) > 59 || (atoi(deg_lat.c_str()) == 90 && atoi(min_lat.c_str()) != 0)) throw std::invalid_argument("Latitude minutes too big.");
    coordinate.setLatitudeMinutes(atoi(min_lat.c_str()));
    if(atoi(sec_lat.c_str()) > 59 || (atoi(deg_lat.c_str()) == 90 && atoi(sec_lat.c_str()) != 0)) throw std::invalid_argument("Latitude seconds too big.");
    coordinate.setLatitudeSeconds(atoi(sec_lat.c_str()));

    coordinate.setLongitudeCompas(compas_lon);
    if(atoi(deg_lon.c_str()) > 180) throw std::invalid_argument("Longitude degrees too big.");
    coordinate.setLongitudeDegrees(atoi(deg_lon.c_str()));
    if(atoi(min_lon.c_str()) > 59 || (atoi(deg_lon.c_str()) == 180 && atoi(min_lon.c_str()) != 0)) throw std::invalid_argument("Longitude minutes too big.");
    coordinate.setLongitudeMinutes(atoi(min_lon.c_str()));
    if(atoi(sec_lon.c_str()) > 59 || (atoi(deg_lon.c_str()) == 180 && atoi(sec_lon.c_str()) != 0)) throw std::invalid_argument("Longitude seconds too big.");
    coordinate.setLongitudeSeconds(atoi(sec_lon.c_str()));

    return coordinate;
}

Coordinate Parser::compas_colon_dm(std::string line) {

    enum states {start, lat_compas, lat_deg, lat_colon, lat_minnum, lat_dot, lat_mindec, space, lon_compas, lon_deg, lon_colon, lon_minnum, lon_dot, lon_mindec, done};
    states state = start;

    std::string deg_lat = "";
    std::string min_lat = "";
    char compas_lat = 'N';

    std::string deg_lon = "";
    std::string min_lon = "";
    char compas_lon = 'E';

    for(unsigned int iterator = 0; iterator <= line.size(); ++iterator) {
        char c = line[iterator];
            switch (c) {
                case ' ':
                    if(state == lat_minnum || state == lat_mindec) state = space;
                    else if(state == lon_minnum || state == lon_mindec) state = done;
                    else if(state != start && state != space && state != done) throw std::invalid_argument("Wrong space character.");
                    break;

                case 'N' : case 'S' :
                    if(state == start) {
                        compas_lat = c;
                        state = lat_compas;
                    }
                    else throw std::invalid_argument("Wrong latitude compas.");
                    break;

                case 'E' : case 'W' :
                    if(state == space) {
                        compas_lon = c;
                        state = lon_compas;
                    }
                    else throw std::invalid_argument("Wrong longitude compas.");
                    break;

                case ':' :
                    if(state == lat_deg) state = lat_colon;
                    else if(state == lon_deg) state = lon_colon;
                    else throw std::invalid_argument("Wrong ':' character.");
                    break;

                case '.' :
                    if(state == lat_minnum) {
                        min_lat += c;
                        state = lat_dot;
                    }
                    else if(state == lon_minnum) {
                        min_lon += c;
                        state = lon_dot;
                    }
                    else throw std::invalid_argument("Wrong '.' character.");
                    break;

                case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
                    if(state == lat_compas || state == lat_deg) {
                        if(deg_lat.size() >= 2) throw std::invalid_argument("Latitude degrees too long.");
                        deg_lat += c;
                        state = lat_deg;
                    }
                    else if(state == lat_colon || state == lat_minnum) {
                        if(min_lat.size() >= 2) throw std::invalid_argument("Latitude minutes too long.");
                        min_lat += c;
                        state = lat_minnum;
                    }
                    else if(state == lat_dot || state == lat_mindec) {
                        if(min_lat.size() < 7) min_lat += c;
                        state = lat_mindec;
                    }
                    else if(state == lon_compas || state == lon_deg) {
                        if(deg_lon.size() >= 3) throw std::invalid_argument("Longitude degrees too long.");
                        deg_lon += c;
                        state = lon_deg;
                    }
                    else if(state == lon_colon || state == lon_minnum) {
                        if(min_lon.size() >= 2) throw std::invalid_argument("Longitude minutes too long.");
                        min_lon += c;
                        state = lon_minnum;
                    }
                    else if(state == lon_dot || state == lon_mindec) {
                        if(min_lon.size() < 7) min_lon += c;
                        state = lon_mindec;
                    }
                    else throw std::invalid_argument("Wrong number.");
                    break;

                case '\0':
                    if(state != lon_minnum && state != lon_mindec && state != done) throw std::invalid_argument("Input too short.");
                    break;

                default: throw std::invalid_argument("Character not allowed.");
                    break;
            }
    }

    Coordinate coordinate;

    double float_minutes_lat = atof(min_lat.c_str());
    double float_seconds_lat = (float_minutes_lat - floor(float_minutes_lat)) * 60;

    coordinate.setLatitudeCompas(compas_lat);
    coordinate.setLatitudeDegrees(atoi(deg_lat.c_str()));
    coordinate.setLatitudeMinutes((unsigned short) floor(float_minutes_lat));
    coordinate.setLatitudeSeconds((unsigned short) floor(float_seconds_lat + 0.5));

    double float_minutes_lon = atof(min_lon.c_str());
    double float_seconds_lon = (float_minutes_lon - floor(float_minutes_lon)) * 60;

    coordinate.setLongitudeCompas(compas_lon);
    coordinate.setLongitudeDegrees(atoi(deg_lon.c_str()));
    coordinate.setLongitudeMinutes((unsigned short) floor(float_minutes_lon));
    coordinate.setLongitudeSeconds((unsigned short) floor(float_seconds_lon + 0.5));

    return coordinate;
}

Coordinate Parser::compas_colon_d(std::string line) {}
Coordinate Parser::compas_degree_dms(std::string line) {}
Coordinate Parser::compas_degree_dm(std::string line) {}
Coordinate Parser::compas_degree_d(std::string line) {}

Coordinate Parser::colon_dms_compas(std::string line) {

    enum states {start, lat_deg, lat_colon1, lat_min, lat_colon2, lat_sec, lat_compas, space, lon_deg, lon_colon1, lon_min, lon_colon2, lon_sec, lon_compas, done};
    states state = start;

    std::string deg_lat = "";
    std::string min_lat = "";
    std::string sec_lat = "";
    char compas_lat = 'N';

    std::string deg_lon = "";
    std::string min_lon = "";
    std::string sec_lon = "";
    char compas_lon = 'E';

    for(unsigned int iterator = 0; iterator <= line.size(); ++iterator) {
        char c = line[iterator];
            switch (c) {
                case ' ':
                    if(state == lat_compas) state = space;
                    else if(state == lon_compas) state = done;
                    else if(state != start && state != space && state != done) throw std::invalid_argument("Wrong space character.");
                    break;

                case 'N' : case 'S' :
                    if(state == lat_sec) {
                        compas_lat = c;
                        state = lat_compas;
                    }
                    else throw std::invalid_argument("Wrong latitude compas.");
                    break;

                case 'E' : case 'W' :
                    if(state == lon_sec) {
                        compas_lon = c;
                        state = lon_compas;
                    }
                    else throw std::invalid_argument("Wrong longitude compas.");
                    break;

                case ':' :
                    if(state == lat_deg) state = lat_colon1;
                    else if(state == lat_min) state = lat_colon2;
                    else if(state == lon_deg) state = lon_colon1;
                    else if(state == lon_min) state = lon_colon2;
                    else throw std::invalid_argument("Wrong ':' character.");
                    break;

                case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
                    if(state == start || state == lat_deg) {
                        if(deg_lat.size() >= 2) throw std::invalid_argument("Latitude degrees too long.");
                        deg_lat += c;
                        state = lat_deg;
                    }
                    else if(state == lat_colon1 || state == lat_min) {
                        if(min_lat.size() >= 2) throw std::invalid_argument("Latitude minutes too long.");
                        min_lat += c;
                        state = lat_min;
                    }
                    else if(state == lat_colon2 || state == lat_sec) {
                        if(sec_lat.size() >= 2) throw std::invalid_argument("Latitude seconds too long.");
                        sec_lat += c;
                        state = lat_sec;
                    }
                    else if(state == space || state == lon_deg) {
                        if(deg_lon.size() >= 3) throw std::invalid_argument("Longitude degrees too long.");
                        deg_lon += c;
                        state = lon_deg;
                    }
                    else if(state == lon_colon1 || state == lon_min) {
                        if(min_lon.size() >= 2) throw std::invalid_argument("Longitude minutes too long.");
                        min_lon += c;
                        state = lon_min;
                    }
                    else if(state == lon_colon2 || state == lon_sec) {
                        if(sec_lon.size() >= 2) throw std::invalid_argument("Longitude seconds too long.");
                        sec_lon += c;
                        state = lon_sec;
                    }
                    else throw std::invalid_argument("Wrong number.");
                    break;

                case '\0':
                    if(state != lon_compas && state != done) throw std::invalid_argument("Input too short.");
                    break;

                default: throw std::invalid_argument("Character not allowed.");
                    break;
            }
    }

    Coordinate coordinate;

    coordinate.setLatitudeCompas(compas_lat);
    if(atoi(deg_lat.c_str()) > 90) throw std::invalid_argument("Latitude degrees too big.");
    coordinate.setLatitudeDegrees(atoi(deg_lat.c_str()));
    if(atoi(min_lat.c_str()) > 59 || (atoi(deg_lat.c_str()) == 90 && atoi(min_lat.c_str()) != 0)) throw std::invalid_argument("Latitude minutes too big.");
    coordinate.setLatitudeMinutes(atoi(min_lat.c_str()));
    if(atoi(sec_lat.c_str()) > 59 || (atoi(deg_lat.c_str()) == 90 && atoi(sec_lat.c_str()) != 0)) throw std::invalid_argument("Latitude seconds too big.");
    coordinate.setLatitudeSeconds(atoi(sec_lat.c_str()));

    coordinate.setLongitudeCompas(compas_lon);
    if(atoi(deg_lon.c_str()) > 180) throw std::invalid_argument("Longitude degrees too big.");
    coordinate.setLongitudeDegrees(atoi(deg_lon.c_str()));
    if(atoi(min_lon.c_str()) > 59 || (atoi(deg_lon.c_str()) == 180 && atoi(min_lon.c_str()) != 0)) throw std::invalid_argument("Longitude minutes too big.");
    coordinate.setLongitudeMinutes(atoi(min_lon.c_str()));
    if(atoi(sec_lon.c_str()) > 59 || (atoi(deg_lon.c_str()) == 180 && atoi(sec_lon.c_str()) != 0)) throw std::invalid_argument("Longitude seconds too big.");
    coordinate.setLongitudeSeconds(atoi(sec_lon.c_str()));

    return coordinate;
}

Coordinate Parser::colon_dm_compas(std::string line) {

    enum states {start, lat_deg, lat_colon, lat_minnum, lat_dot, lat_mindec, lat_compas, space, lon_deg, lon_colon, lon_minnum, lon_dot, lon_mindec, lon_compas, done};
    states state = start;

    std::string deg_lat = "";
    std::string min_lat = "";
    char compas_lat = 'N';

    std::string deg_lon = "";
    std::string min_lon = "";
    char compas_lon = 'E';

    for(unsigned int iterator = 0; iterator <= line.size(); ++iterator) {
        char c = line[iterator];
            switch (c) {
                case ' ':
                    if(state == lat_compas) state = space;
                    else if(state == lon_compas) state = done;
                    else if(state != start && state != space && state != done) throw std::invalid_argument("Wrong space character.");
                    break;

                case 'N' : case 'S' :
                    if(state == lat_minnum || state == lat_mindec) {
                        compas_lat = c;
                        state = lat_compas;
                    }
                    else throw std::invalid_argument("Wrong latitude compas.");
                    break;

                case 'E' : case 'W' :
                    if(state == lon_minnum || state == lon_mindec) {
                        compas_lon = c;
                        state = lon_compas;
                    }
                    else throw std::invalid_argument("Wrong longitude compas.");
                    break;

                case ':' :
                    if(state == lat_deg) state = lat_colon;
                    else if(state == lon_deg) state = lon_colon;
                    else throw std::invalid_argument("Wrong ':' character.");
                    break;

                case '.' :
                    if(state == lat_minnum) {
                        min_lat += c;
                        state = lat_dot;
                    }
                    else if(state == lon_minnum) {
                        min_lon += c;
                        state = lon_dot;
                    }
                    else throw std::invalid_argument("Wrong '.' character.");
                    break;

                case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
                    if(state == start || state == lat_deg) {
                        if(deg_lat.size() >= 2) throw std::invalid_argument("Latitude degrees too long.");
                        deg_lat += c;
                        state = lat_deg;
                    }
                    else if(state == lat_colon || state == lat_minnum) {
                        if(min_lat.size() >= 2) throw std::invalid_argument("Latitude minutes too long.");
                        min_lat += c;
                        state = lat_minnum;
                    }
                    else if(state == lat_dot || state == lat_mindec) {
                        if(min_lat.size() < 7) min_lat += c;
                        state = lat_mindec;
                    }
                    else if(state == space || state == lon_deg) {
                        if(deg_lon.size() >= 3) throw std::invalid_argument("Longitude degrees too long.");
                        deg_lon += c;
                        state = lon_deg;
                    }
                    else if(state == lon_colon || state == lon_minnum) {
                        if(min_lon.size() >= 2) throw std::invalid_argument("Longitude minutes too long.");
                        min_lon += c;
                        state = lon_minnum;
                    }
                    else if(state == lon_dot || state == lon_mindec) {
                        if(min_lon.size() < 7) min_lon += c;
                        state = lon_mindec;
                    }
                    else throw std::invalid_argument("Wrong number.");
                    break;

                case '\0':
                    if(state != lon_compas && state != done) throw std::invalid_argument("Input too short.");
                    break;

                default: throw std::invalid_argument("Character not allowed.");
                    break;
            }
    }

    Coordinate coordinate;

    double float_minutes_lat = atof(min_lat.c_str());
    double float_seconds_lat = (float_minutes_lat - floor(float_minutes_lat)) * 60;

    coordinate.setLatitudeCompas(compas_lat);
    coordinate.setLatitudeDegrees(atoi(deg_lat.c_str()));
    coordinate.setLatitudeMinutes((unsigned short) floor(float_minutes_lat));
    coordinate.setLatitudeSeconds((unsigned short) floor(float_seconds_lat + 0.5));

    double float_minutes_lon = atof(min_lon.c_str());
    double float_seconds_lon = (float_minutes_lon - floor(float_minutes_lon)) * 60;

    coordinate.setLongitudeCompas(compas_lon);
    coordinate.setLongitudeDegrees(atoi(deg_lon.c_str()));
    coordinate.setLongitudeMinutes((unsigned short) floor(float_minutes_lon));
    coordinate.setLongitudeSeconds((unsigned short) floor(float_seconds_lon + 0.5));

    return coordinate;
}

Coordinate Parser::colon_d_compas(std::string line) {}
Coordinate Parser::degree_dms_compas(std::string line) {}
Coordinate Parser::degree_dm_compas(std::string line) {}
Coordinate Parser::degree_d_compas(std::string line) {}
