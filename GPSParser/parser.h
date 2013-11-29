#ifndef PARSER_H
#define PARSER_H

#include "coordinate.h"
#include "exceptions.h"

class Parser
{
public:
    Parser();

    /**
     * @brief parseInput
     * receives line with gps coordinates, recognized format
     * and processes input to method for that format
     * @param line
     * @return coordinates parsed to coordinate class
     */
    Coordinate parseInput(std::string line);

private:
    /**
     * @brief Count
     * counts number of occurences of substring in string
     * @param str substring to find
     * @param obj string in which is searched
     * @return number of occurences
     */
    int Count( const std::string & str, const std::string & obj );

    /**
     * @brief minus_colon_dms
     * processes coordinates from the given string input in format (-)ddd:mm:ss (-)ddd:mm:ss
     * @param line string input with coordinates
     * @return coordinates parsed to coordinate class
     */
    Coordinate minus_colon_dms(std::string line);

    /**
     * @brief minus_colon_dm
     * processes coordinates from the given string input in format (-)ddd:mm.mmmmm (-)ddd:mm.mmmmm
     * @param line string input with coordinates
     * @return coordinates parsed to coordinate class
     */
    Coordinate minus_colon_dm(std::string line);

    /**
     * @brief minus_colon_d
     * processes coordinates from the given string input in format (-)ddd.dddddd (-)ddd.dddddd
     * @param line string input with coordinates
     * @return coordinates parsed to coordinate class
     */
    Coordinate minus_colon_d(std::string line);

    /**
     * @brief minus_degree_dms
     * processes coordinates from the given string input in format (-)ddd°mm'ss" (-)ddd°mm'ss"
     * @param line string input with coordinates
     * @return coordinates parsed to coordinate class
     */
    Coordinate minus_degree_dms(std::string line);

    /**
     * @brief minus_degree_dm
     * processes coordinates from the given string input in format (-)ddd°mm.mmmmm' (-)ddd°mm.mmmmm'
     * @param line string input with coordinates
     * @return coordinates parsed to coordinate class
     */
    Coordinate minus_degree_dm(std::string line);

    /**
     * @brief minus_degree_d
     * processes coordinates from the given string input in format (-)ddd.dddddd° (-)ddd.dddddd°
     * @param line string input with coordinates
     * @return coordinates parsed to coordinate class
     */
    Coordinate minus_degree_d(std::string line);

    /**
     * @brief compas_colon_dms
     * processes coordinates from the given string input in format [NS]ddd:mm:ss [WE]ddd:mm:ss
     * @param line string input with coordinates
     * @return coordinates parsed to coordinate class
     */
    Coordinate compas_colon_dms(std::string line);

    /**
     * @brief compas_colon_dm
     * processes coordinates from the given string input in format [NS]ddd:mm.mmmmm [WE]ddd:mm.mmmmm
     * @param line string input with coordinates
     * @return coordinates parsed to coordinate class
     */
    Coordinate compas_colon_dm(std::string line);

    /**
     * @brief compas_colon_d
     * processes coordinates from the given string input in format [NS]ddd.dddddd [WE]ddd.dddddd
     * @param line string input with coordinates
     * @return coordinates parsed to coordinate class
     */
    Coordinate compas_colon_d(std::string line);

    /**
     * @brief compas_degree_dms
     * processes coordinates from the given string input in format [NS]ddd°mm'ss" [WE]ddd°mm'ss"
     * @param line string input with coordinates
     * @return coordinates parsed to coordinate class
     */
    Coordinate compas_degree_dms(std::string line);

    /**
     * @brief compas_degree_dm
     * processes coordinates from the given string input in format [NS]ddd°mm.mmmmm' [WE]ddd°mm.mmmmm'
     * @param line string input with coordinates
     * @return coordinates parsed to coordinate class
     */
    Coordinate compas_degree_dm(std::string line);

    /**
     * @brief compas_degree_d
     * processes coordinates from the given string input in format [NS]ddd.dddddd° [WE]ddd.dddddd°
     * @param line string input with coordinates
     * @return coordinates parsed to coordinate class
     */
    Coordinate compas_degree_d(std::string line);

    /**
     * @brief colon_dms_compas
     * processes coordinates from the given string input in format ddd:mm:ss[NS] ddd:mm:ss[WE]
     * @param line string input with coordinates
     * @return coordinates parsed to coordinate class
     */
    Coordinate colon_dms_compas(std::string line);

    /**
     * @brief colon_dm_compas
     * processes coordinates from the given string input in format ddd:mm.mmmmm[NS] ddd:mm.mmmmm[WE]
     * @param line string input with coordinates
     * @return coordinates parsed to coordinate class
     */
    Coordinate colon_dm_compas(std::string line);

    /**
     * @brief colon_d_compas
     * processes coordinates from the given string input in format ddd.dddddd[NS] ddd.dddddd[WE]
     * @param line string input with coordinates
     * @return coordinates parsed to coordinate class
     */
    Coordinate colon_d_compas(std::string line);

    /**
     * @brief degree_dms_compas
     * processes coordinates from the given string input in format ddd°mm'ss"[NS] ddd°mm'ss"[WE]
     * @param line string input with coordinates
     * @return coordinates parsed to coordinate class
     */
    Coordinate degree_dms_compas(std::string line);

    /**
     * @brief degree_dm_compas
     * processes coordinates from the given string input in format ddd°mm.mmmmm'[NS] ddd°mm.mmmmm'[WE]
     * @param line string input with coordinates
     * @return coordinates parsed to coordinate class
     */
    Coordinate degree_dm_compas(std::string line);

    /**
     * @brief degree_d_compas
     * processes coordinates from the given string input in format ddd.dddddd°[NS] ddd.dddddd°[WE]
     * @param line string input with coordinates
     * @return coordinates parsed to coordinate class
     */
    Coordinate degree_d_compas(std::string line);

};

#endif // PARSER_H
