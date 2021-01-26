#ifndef DATA_MANIPULATION_H
#define DATA_MANIPULATION_H
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>

using namespace std;

class DataManipulation
{
    public:
        static string loadLine();
        static char loadCharacter();
        static int loadInteger();
        static int extractNumber(string dataLine, int caseNumber);
        static int stringToInt(string stringNumber);
        bool isLeapYear(int year);
        static string getCurrentDate();
        static string getDueDate();
};
#endif // DATA_MANIPULATION_H

