#include "DataManipulation.h"

std::string DataManipulation::loadLine()
{
    std::string loadedLine = "";
    getline(std::cin, loadedLine);
    return loadedLine;
}

char DataManipulation::loadCharacter()
{
    std::string input= "";
    char singleCharacter  = {0};

    while (true)
    {
        getline(std::cin, input);

        if (input.length() == 1)
        {
            singleCharacter = input[0];
            break;
        }
        std::cout << "To nie jest pojedynczy znak. Wpisz ponownie." << std::endl;
    }
    return singleCharacter;
}

int DataManipulation::loadInteger()
{
    string input = "";
    int number = 0;

    while (true)
    {
        getline(cin, input);

        stringstream myStream(input);
        if (myStream >> number)
            break;
        cout << "To nie jest liczba. Wpisz ponownie. " << endl;
    }
    return number;
}

int DataManipulation::stringToInt(std::string stringNumber)
{
    int intNumber;
    std::istringstream ss(stringNumber);
    ss >> intNumber;
    return intNumber;
}

int DataManipulation::extractNumber(std::string dataLine, int caseNumber)
{
    std::string stringNumber="";
    int intNumber=0;

    int i=1; int j=0;
    while(i <= caseNumber)
    {
        if (dataLine[j] == '|')
        {
            i++; j++;
        }
        else if (dataLine[j] != '|' && caseNumber == i )
        {
                stringNumber+=dataLine[j];
                j++;
        }
        else
                j++;
    }
    intNumber = stringToInt(stringNumber);
    return intNumber;
}

bool DataManipulation::isLeapYear(int year)
{
    if ((year%4==0 && year%100!=0) || year%400==0)
        return true;
    else
        return false;
}

int DataManipulation::getDaysInMonth(int year, int month)
{
    if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    else if (month == 2 && isLeapYear(year))
        return 29;
    else if (month == 2 && !isLeapYear(year))
        return 28;
    else
        return 31;
}

string DataManipulation::getCurrentDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    return to_string(1900 + ltm->tm_year)+"/"+to_string(1 + ltm->tm_mon)+"/"+to_string(ltm->tm_mday);
}

string DataManipulation::getDueDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int year = 1900 + ltm->tm_year;
    int month = 1 + ltm->tm_mon;
    if(month + 3 > 12){
        month = month + 3 - 12;
        year += 1;
    } else {
        month += 3;
    }
    int day =ltm->tm_mday;

    int daysThreeMonthsFromNow = getDaysInMonth(year, month);
    while (month > 12 || daysThreeMonthsFromNow < day){
        if (month > 12){
            year += 1;
        }
        if (daysThreeMonthsFromNow < day){
            day -= daysThreeMonthsFromNow;
            month += 1;
        }
        daysThreeMonthsFromNow = getDaysInMonth(year, month);
    }

    return to_string(year)+"/"+to_string(month)+"/"+to_string(day);
}

int DataManipulation::getCurrentYear()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return 1900 + ltm->tm_year;
}
