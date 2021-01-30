#ifndef DATA_MANIPULATION_H
#define DATA_MANIPULATION_H
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>

using namespace std;

class DataManipulation
{
    private:
        static int getDaysInMonth(int year, int month);
        static bool isLeapYear(int year);
    public:
        static string loadLine();
        static char loadCharacter();
        static int loadInteger();
        static int extractNumber(string dataLine, int caseNumber);
        static int stringToInt(string stringNumber);
        static string getCurrentDate();
        static string getDueDate();
        static int getCurrentYear();
};
#endif // DATA_MANIPULATION_H

