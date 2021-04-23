#include "program.h"
#include <iostream>
#include <fstream>

bool Program::chooseMode(string question)
{
    char userChoice; 
    bool AllOk = false;

    // keep repeating until the user prompts either Y or F
    do
    {
        cout << question;
        cin >> userChoice;
        cin.ignore();

        // tolower makes the userChoice no case sensitive
        switch (tolower(userChoice))
        {
        case 'y':
            AllOk = true;
            break;

        case 'n':
            AllOk = false;
            break;

        default:
            // Assing a default value
            userChoice = 'x';

            // Clear the console showing the error
            system("CLS");
            cout << "Not valid option" << endl;
            break;
        }
    }     while (userChoice == 'x');

    return AllOk;
}

void Program::displayMenu(Wind* wind, int round)
{
    system("CLS");
    cout << "FIRE SIMULATOR\n----------------" << endl << endl;
    cout << "LEGEND" << endl;

    // When the user chose the enhancements
    if (wind != nullptr)
    {
        cout << " - Wind direction: " << wind->getDirection() << '\n' 
             << " - Wind speed: " << wind->getSpeed() << "Km/h" << '\n' 
             << " - @: Tree with most soil" << endl;
    }
    // Standard legend information
    cout << " - &: Tree with dry soil" << '\n' 
         << " - #: Burning Tree" << '\n' 
         << " - ' ': Death Tree" << '\n' 
         << "----------------" << endl << endl;

    cout << "Round: " << round << endl << endl;
}

bool Program::printStatistics(Wind* wind, Forest* forest, int rounds, string fileName)
{
    ofstream outFile;
    outFile.open(fileName); // Open connection

    // The connection could not be opened for some reasons, it return false
    if (outFile.is_open() == false)
    {
        return false;
    }
    else
    {
        outFile << "FIRE SIMULATOR STATISTICS\n----------------\n"
            << "Total Rounds: " << rounds << endl;

        // Additional information are displayed if the user chose the enhancements
        if (wind == nullptr)
        {
            outFile << " - Total Trees: " << forest->getTotalTrees() << '\n'
                << " - Dead Trees: " << forest->getDeadTrees() << '\n'
                << " - Live Trees: " << forest->getLiveTrees() << '\n'
                << " - Burning Trees: " << forest->getBurningTrees() << '\n';
        }
        else
        {
            // Standard statistics information
            outFile << "\n1. WIND\n"
                << "\t - Direction: " << wind->getDirection() << '\n'
                << "\t - Speed: " << wind->getSpeed() << " Km/h\n"
                << "\n2. BURNING TREES\n"
                << "\t - Total: " << forest->getBurningTrees() << '\n'
                << "\n3. TREES WITH DRY SOIL\n"
                << "\t - Total: " << forest->getTotalDry() << '\n'
                << "\t - Dead: " << forest->getDeadDry() << '\n'
                << "\t - Live: " << forest->getLiveDry() << '\n'
                << "\n4. TREES WITH MOIST SOIL\n"
                << "\t - Total: " << forest->getTotalMoisture() << '\n'
                << "\t - Dead: " << forest->getDeadMoisture() << '\n'
                << "\t - Live: " << forest->getLiveMoisture() << endl;

            outFile.close(); // close connection
        }
        return true;
    }
}

bool Program::readStatistics(string fileName)
{
    ifstream inFile;
    string line;

    system("CLS");
    inFile.open(fileName); // Open connection

    // The connection could not be opened for some reasons, it return false
    if (inFile.is_open() == false)
    {
        return false;
    }
    else
    {
        // Iterates throught the entire file
        while (getline(inFile, line))
        {
            // Read line by line
            cout << line << endl;
        }
        cout << endl;

        inFile.close(); // Close connection
        return true;
    }
}
