#ifndef PROGRAMH
#define PROGRAMH

#include "wind.h"
#include "forest.h"
#include <string>
using namespace std;

class Program
{
public:

    /// <summary>
    /// Display a question to the user and gets the answer which can be either Yes or No
    /// </summary>
    /// <param name="question"> question to answer to the user</param>
    /// <returns>True if Yes or False if No</returns>
    static bool chooseMode(string question);

    /// <summary>
    /// Display both the title and the legend to the screen
    /// </summary>
    /// <param name="wind">pointer to a Wind object</param>
    /// <param name="round">round of the simulation</param>
    static void displayMenu(Wind* wind, int round);

    /// <summary>
    /// Creates / Open a file and write the statistics on it
    /// </summary>
    /// <param name="wind">pointer to a wind object</param>
    /// <param name="forest">forest initialised in Main</param>
    /// <param name="rounds">number of rounds played</param>
    /// <param name="fileName">name of the file where is intended to create / open</param>
    /// <returns>true if statistics have been written, false if the connection have not been opened</returns>
    static bool printStatistics(Wind* wind, Forest* forest, int rounds, string fileName);

    /// <summary>
    /// read the file
    /// </summary>
    /// <param name="fileName">name of the file which is inteded to be read</param>
    /// <returns>true if statistics have been read, false if the connection have not been opened</returns>
    static bool readStatistics(string fileName);
};
#endif

