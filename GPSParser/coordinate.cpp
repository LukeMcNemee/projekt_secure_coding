#include "coordinate.h"
#include <sstream>

Coordinate::Coordinate()
{
    latitudeCompas = 'N';
    latitudeDegrees = 0;
    latitudeMinutes = 0;
    latitudeSeconds = 0;

    longitudeCompas = 'E';
    longitudeDegrees = 0;
    longitudeMinutes = 0;
    longitudeSeconds = 0;
}

void Coordinate::setLatitudeCompas(char value) {
    latitudeCompas = value;
    checkOverFlow();
}
void Coordinate::setLatitudeDegrees(unsigned short value) {
    latitudeDegrees = value;
    checkOverFlow();
}
void Coordinate::setLatitudeMinutes(unsigned short value) {
    latitudeMinutes = value;
    checkOverFlow();
}
void Coordinate::setLatitudeSeconds(unsigned short value) {
    latitudeSeconds = value;
    checkOverFlow();
}

void Coordinate::setLongitudeCompas(char value) {
    longitudeCompas = value;
    checkOverFlow();
}
void Coordinate::setLongitudeDegrees(unsigned short value) {
    longitudeDegrees = value;
    checkOverFlow();
}
void Coordinate::setLongitudeMinutes(unsigned short value) {
    longitudeMinutes = value;
    checkOverFlow();
}
void Coordinate::setLongitudeSeconds(unsigned short value) {
    longitudeSeconds = value;
    checkOverFlow();
}

std::string Coordinate::toSVG() {

    unsigned short x = (longitudeCompas == 'E') ? 2 * (180 + longitudeDegrees) : 2 * (180 - longitudeDegrees);
    if(longitudeMinutes >= 30) x = (longitudeCompas == 'E') ? x + 1 : x - 1;
    unsigned short y = (latitudeCompas == 'S') ? 2 * (90 + latitudeDegrees) : 2 * (90 - latitudeDegrees);
    if(latitudeMinutes >= 30) y = (latitudeCompas == 'S') ? y + 1 : y - 1;

    std::stringstream ss;
    ss << "<circle cx=\"" << x;
    ss << "\" cy=\"" << y;
    ss << "\" r=\"2\" stroke=\"black\" stroke-width=\"1\" fill=\"black\" />" << std::endl;

    ss << "<text x=\"" << x;
    ss << "\" y=\"" << y;
    ss << "\" fill=\"black\">";
    ss << latitudeDegrees << ":" << latitudeMinutes << ":" << latitudeSeconds << latitudeCompas;
    ss << longitudeDegrees << ":" << longitudeMinutes << ":" << longitudeSeconds << longitudeCompas;
    ss << "</text>" << std::endl;

    return ss.str();
}

std::string Coordinate::toString(){
    std::stringstream ss;
    ss << latitudeDegrees << ":" << latitudeMinutes << ":" << latitudeSeconds << latitudeCompas;
    ss << longitudeDegrees << ":" << longitudeMinutes << ":" << longitudeSeconds << longitudeCompas;
    return ss.str();
}

void Coordinate::checkOverFlow(){
    if(latitudeCompas != 'N' && latitudeCompas != 'S'){
        throw PatternException();
    }
    if(longitudeCompas != 'E' && longitudeCompas != 'W'){
        throw PatternException();
    }
    double sumLat = latitudeDegrees;
    sumLat += latitudeMinutes / 60.0;
    sumLat += latitudeSeconds / 360.0;
    if(sumLat > 90){
        throw CoordinateOverlowException();
    }
    double sumLon = longitudeDegrees;
    sumLon += longitudeMinutes / 60.0;
    sumLon += longitudeSeconds / 360.0;
    if (sumLon > 180){
        throw CoordinateOverlowException();
    }
}
