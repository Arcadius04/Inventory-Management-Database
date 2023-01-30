/*
 * Electrical Components Inventory Manager
 *
 * Authored by:
 * Muhanna AlNoaimi / 202000153
 */

#include "Console.hpp"


void Console::consolePrint(std::string info)
{
    // Default color of the text is 7 (white)
    int currentColor=7;
    for(int i = 0; i < info.size(); i++)
    {
        // Check if the current pointed character is a dollar sign (the color code symbol)
        if(info[i]=='$')
        {
            // The number variable holds the whole number which will be concatenated to it
            std::string number="";
            // k represents the number the succeeds the color coded symbol
            int k = i+1;
            // Go through all the symbols after the first digit to check if the number is still continuous and loop until its not a digit
            while(isdigit(info[k]))
            {
                // Concatenate the character to the string number
                number+=info[k];
                // Go to the next character
                k++;
            }
            // Skip the color code as well as the digits succeeding it
            i=k-1;
            // Assign a converted string number to integer into the current color integer
            currentColor = stoi(number);
            // Continue the for loop when the color code is skipped to proceed a print the characters
            continue;
        }
        // If the program is being compiled by a windows PC the console handler gets defined
        // as well as the text attribute property for the handler to allow the change in colors
#ifdef _WIN32
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(consoleHandle, currentColor);
#endif
        // Print each character in the string except the ones skipped or color coded
        std::cout << info[i];
    }
    return;
}

void Console::displayErrorMessage(std::string errorMessage)
{
    std::string errorPrefix = "$8[$12Error$8]$4 ";
    Console::consolePrint(errorPrefix + errorMessage);
    return;
}

void Console::displayWarnMessage(std::string warnMessage)
{
    std::string warnPrefix = "$8[$14Warn$8]$7 ";
    Console::consolePrint(warnPrefix + warnMessage);
    return;
}
void Console::displayInfoMessage(std::string infoMessage)
{
    std::string infoPrefix = "$8[$7Info$8]$7 ";
    Console::consolePrint(infoPrefix + infoMessage);
    return;
}
