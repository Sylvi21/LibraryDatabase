#ifndef DATA_MANIPULATION_H
#define DATA_MANIPULATION_H

#include <iostream>
#include <sstream>
#include <string>

class DataManipulation
{
    public:
        static std::string loadLine();
        static char loadCharacter();
        static int extractNumber(std::string dataLine, int caseNumber);
        static int stringToInt(std::string stringNumber);
};
#endif // DATA_MANIPULATION_H

