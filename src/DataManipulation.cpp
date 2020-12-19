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
