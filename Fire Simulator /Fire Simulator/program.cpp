#include "program.h"

#include <iostream>
#include <fstream>
/// <summary>
/// prompts the user a question and return either true or false
/// </summary>
/// <param name="question">question to ask the user for</param>
bool Program::chooseMode(string question)
{
    char userChoice;
    bool AllOk = false;
    
    // keep repeating until the user prompts either true or false
    do
    {
        cout << question;
        cin >> userChoice;
        cin.ignore();
        switch (tolower(userChoice))
        {
            case 'y':
                AllOk = true;
                break;
                
            case 'n':
                AllOk = false;
                break;
                
            default:
                userChoice = 'x';
                system("CLS");
                cout << "Not valid option" << endl;
                break;
        }
    }
    while (userChoice == 'x');
    
    return AllOk;
}

/// <summary>
/// Display both the title and the legend to the screen
/// </summary>
/// <param name="wind">pointer to a Wind object</param>
/// <param name="round">round of the simulation</param>
void Program::displayMenu(Wind* wind, int round)
{
    system("CLS");
    cout << "FIRE SIMULATOR\n----------------" << endl << endl;
    cout << "LEGEND" << endl;
    if (wind != nullptr)
    {
        cout << " - Wind direction: " << wind->getDirection() << '\n' << " - Wind speed: " << wind->getSpeed() << "Km/h"
        << '\n' << " - @: Tree with most soil" << endl;
        
    }
    cout << " - &: Tree with dry soil" << '\n' << " - #: Burning Tree" << '\n' << " - ' ': Death Tree" << '\n' << "----------------" << endl << endl;
    cout << "Round: " << round << endl << endl;
}

/// <summary>
/// Creates / Open a file and write the statistics on it
/// </summary>
/// <param name="wind">pointer to a wind object</param>
/// <param name="forest">forest initialised in Main</param>
/// <param name="rounds">number of rounds played</param>
/// <param name="fileName">name of the file which is intended to create / open</param>
/// <returns>true if statistics have been written, false if the connection have not been opened</returns>
bool Program::printStatistics(Wind* wind, Forest* forest, int rounds, string fileName)
{
    ofstream outFile;
    outFile.open(fileName); // open connection
    
    if (outFile.is_open() == false)
    {
        return false;
    }
    else
    {
        outFile << "FIRE SIMULATOR STATISTICS\n----------------\n"
        << "Total Rounds: " << rounds << endl;
        if (wind == nullptr)
        {
            outFile << " - Total Trees: " << forest->getTotalTrees() << '\n'
            << " - Dead Trees: " << forest->getDeadTrees() << '\n'
            << " - Live Trees: " << forest->getLiveTrees() << '\n'
            << " - Burning Trees: " << forest->getBurningTrees() << '\n';
        }
        else
        {
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

/// <summary>
/// read the file
/// </summary>
/// <param name="fileName">name of the file which is inteded to be read</param>
/// <returns>true if statistics have been read, false if the connection have not been opened</returns>
bool Program::readStatistics(string fileName)
{
    ifstream inFile;
    string line;
    
    system("CLS");
    inFile.open(fileName); // Open connection
    
    if (inFile.is_open() == false)
    {
        return false;
    }
    else
    {
        while (getline(inFile, line))
        {
            cout << line << endl;
        }
        cout << endl;
        
        inFile.close(); // Close connection
        return true;
    }
}
