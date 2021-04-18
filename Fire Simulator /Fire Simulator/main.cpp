#include "wind.h"
#include "forest.h"
#include "program.h"
#include <iostream>
#include <ctime>


using namespace std;

int main()
{
    bool userChoice;
    char value;
    bool end = false, finish = false;
    int round = 1;

    srand(static_cast<unsigned int>(time(nullptr)));

    Wind* wind = nullptr;

    cout << "Welcome to Fire Simulator" << '\n' << "----------------" << endl << endl;
    userChoice = Program::chooseMode("Do you want to add wind and moisture effects to the simulation? [Y/N]: ");

    // Initialise the Wind pointer only if the user wants to apply the wind to the simulation
    if (userChoice)
    {
        wind = Wind::getWind();
    }

    Forest forest(userChoice);

    // As long as the user click 'x' or there are no more burning trees
    while (end == false && finish == false)
    {
        Program::displayMenu(wind, round);
        forest.drawForest();

        cout << endl;
        cout << "Press enter to continue or 'x' to exit..." << endl;
        value = cin.get();

        if (value == '\n')
        {
            finish = forest.updateForest(wind);
            round++;
        }
        else if (tolower(value) != 'x')
        {
            cin.ignore();
        }
        else
        {
          end = true;
        }
    }
    if (finish == true)
    {
        cout << "Program ended: no more burning trees" << endl << endl;
        round--;
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
