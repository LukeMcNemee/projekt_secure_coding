#include "exceptions.h"


const char* NumberException::what() const throw()
{
    return "Coordinate not found";
}

const char* PatternException::what() const throw()
{
    return "Coordinate has wrong pattern";
}

const char* CharException::what() const throw()
{
    return "Wrong position of character";
}

const char* WhitespaceException::what() const throw()
{
    return "Wrong position of whitespace";
}

const char* CoordinateOverlowException::what() const throw()
{
    return "Wrong dimensions of coordinate";
}

const char* CoordinateIdentifierException::what() const throw()
{
    return "Wrong use of coordinate identifier";
}
