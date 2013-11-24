#ifndef COORDINATE_H
#define COORDINATE_H

#include <string>

enum compas {N, S, E, W};

class Coordinate
{
public:
    Coordinate();

    void setLatitudeCompas(compas value);
    void setLatitudeDegrees(unsigned short value);
    void setLatitudeMinutes(unsigned short value);
    void setLatitudeSeconds(unsigned short value);

    void setLongitudeCompas(compas value);
    void setLongitudeDegrees(unsigned short value);
    void setLongitudeMinutes(unsigned short value);
    void setLongitudeSeconds(unsigned short value);

    std::string toString();

private:
    compas latitudeCompas;
    unsigned short latitudeDegrees;
    unsigned short latitudeMinutes;
    unsigned short latitudeSeconds;

    compas longitudeCompas;
    unsigned short longitudeDegrees;
    unsigned short longitudeMinutes;
    unsigned short longitudeSeconds;
};

#endif // COORDINATE_H
