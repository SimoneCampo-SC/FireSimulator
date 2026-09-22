#include "wind.h"
#include "forest.h"
#include "program.h"
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    bool userChoice; // holds the choices made from the user
    char userValue;
    bool userEnd = false, noMoreBurningTrees = false;
    int round = 1;

    Wind* wind = nullptr;

    // statement required to generate random numbers
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "Welcome to Fire Simulator" << '\n' 
         << "----------------" << endl << endl;

    userChoice = Program::chooseMode("Do you want to add wind and moisture effects to the simulation? [Y/N]: ");

    // Initialise the Wind pointer only if the user wants to apply the wind to the simulation
    if (userChoice)
    {
        wind = Wind::getWind();
    }

    Forest* forest = Forest::getForest(userChoice);

    // As long as the user click 'x' or there are no more burning trees
    while (userEnd == false && noMoreBurningTrees == false)
    {
        Program::displayMenu(wind, round);
        forest->drawForest();

        cout << endl;
        cout << "Press enter to continue or 'x' to exit..." << endl;
        userValue = cin.get();

        if (userValue == '\n')
        {
            noMoreBurningTrees = forest->updateForest(wind);
            round++;
        }
        else if (tolower(userValue) != 'x')
        {
            cin.ignore(); // Ignore any character inserted other than 'x'
        }
        else
        {
            userEnd = true;
        }
    }
    if (noMoreBurningTrees == true)
    {
        cout << "Program ended: no more burning trees" << endl << endl;
        round--; // Normalise the counter
    }
    else
    {
        cout << "Program ended: key 'x' entered" << endl << endl;;
    }
    if (Program::printStatistics(wind, forest, round, "statistics.txt"))
    {
        cout << "Statistics have been saved on a file called statistics.txt" << endl;
        userChoice = Program::chooseMode("Do you want to read the file? [Y/N]: ");
        cout << endl;

        if (userChoice)
        {
            // The file could not be opened
            if (!Program::readStatistics("statistics.txt"))
            {
                cout << "Error while opening statistics.txt file." << endl;
            }
        }
    }
    else
    {
        cout << "Error while creating statistics.txt file." << endl;
    }
    cout << endl;
    cout << "Press any key to end the program..." << endl;
    cin.get();

    return 0;
}
