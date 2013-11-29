#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <stdexcept>
/**
 * @brief The NumberException class
 * thrown when no numbers found in coordinate
 */
class NumberException : public std::invalid_argument
{
public:
    NumberException() : std::invalid_argument("Coordinate not found"){}

    virtual const char* what() const throw();

};

/**
 * @brief The PatternException class
 * general pattern exception
 * used in case of combination of different formats etc.
 */
class PatternException : public std::invalid_argument
{
public:
    PatternException() : std::invalid_argument("Coordinate has wrong pattern"){}
    virtual const char* what() const throw();

};

/**
 * @brief The CharException class
 * used in case of mispaced characters in coordinate
 */
class CharException : public std::invalid_argument
{
public:
    CharException() : std::invalid_argument("Wrong position of character"){}
    virtual const char* what() const throw();
private:
    char character;

};

/**
 * @brief The WhitespaceException class
 * misplaced whitespaces
 */
class WhitespaceException : public std::invalid_argument
{
public:
    WhitespaceException() : std::invalid_argument("Wrong position of whitespace"){}
    virtual const char* what() const throw();

};

/**
 * @brief The CoordinateOverlowException class
 * coordinates out of bounds
 */
class CoordinateOverlowException : public std::invalid_argument
{
public:
    CoordinateOverlowException() : std::invalid_argument("Wrong dimensions of coordinate"){}
    virtual const char* what() const throw();

};

/**
 * @brief The CoordinateIdentifierException class
 * mispaced or wrong compas identifier
 */
class CoordinateIdentifierException : public std::invalid_argument
{
public:
    CoordinateIdentifierException() : std::invalid_argument( "Wrong use of coordinate identifier"){}
    virtual const char* what() const throw();

};

#endif // EXCEPTIONS_H
