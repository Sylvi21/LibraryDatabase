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
