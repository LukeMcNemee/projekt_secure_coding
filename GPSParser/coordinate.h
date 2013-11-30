#ifndef COORDINATE_H
#define COORDINATE_H

#include <string>
#include "exceptions.h"


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

    /**
     * @brief checkOverFlow
     * check content of coordinate for overflow
     * in case of overflow throws exception
     */
    void checkOverFlow();
};

#endif // COORDINATE_H
