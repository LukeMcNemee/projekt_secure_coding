#ifndef COORDINATE_H
#define COORDINATE_H

#include <string>

enum compas {N, S, E, W};

class Coordinate
{
public:
    Coordinate();

    void setLatitudeCompas(char value);
    void setLatitudeDegrees(unsigned short value);
    void setLatitudeMinutes(unsigned short value);
    void setLatitudeSeconds(unsigned short value);

    void setLongitudeCompas(char value);
    void setLongitudeDegrees(unsigned short value);
    void setLongitudeMinutes(unsigned short value);
    void setLongitudeSeconds(unsigned short value);

    std::string toSVG();

private:
    char latitudeCompas;
    unsigned short latitudeDegrees;
    unsigned short latitudeMinutes;
    unsigned short latitudeSeconds;

    char longitudeCompas;
    unsigned short longitudeDegrees;
    unsigned short longitudeMinutes;
    unsigned short longitudeSeconds;
};

#endif // COORDINATE_H
