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
}
void Coordinate::setLatitudeDegrees(unsigned short value) {
    latitudeDegrees = value;
}
void Coordinate::setLatitudeMinutes(unsigned short value) {
    latitudeMinutes = value;
}
void Coordinate::setLatitudeSeconds(unsigned short value) {
    latitudeSeconds = value;
}

void Coordinate::setLongitudeCompas(char value) {
    longitudeCompas = value;
}
void Coordinate::setLongitudeDegrees(unsigned short value) {
    longitudeDegrees = value;
}
void Coordinate::setLongitudeMinutes(unsigned short value) {
    longitudeMinutes = value;
}
void Coordinate::setLongitudeSeconds(unsigned short value) {
    longitudeSeconds = value;
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
