#ifndef FORESTH
#define FORESTH

#include "listOfTrees.h"

class Forest
{
private:
    char forestArray[21][21]; // 2D Array holds the states of the trees

    // Counters attributes used for the statistics function and they keep track of the number of trees in the list
    int totalTrees = 0, totalMoisture = 0, totalDry = 0;
    int deadTrees = 0, deadMoisture = 0, deadDry = 0;
    int liveTrees = 0, liveMoisture = 0, liveDry = 0;
    int burningTrees = 0;

    // Pointer to the linked list data structure 
    ListOfTrees* list = ListOfTrees::getList();

    // Pointer to the static object of the Forest class
    static Forest* _pointer;

    /// <summary>
    /// Private constructor initialise Forest object with boundary and the burning tree at the center
    /// Set the counters attributes of the Forest
    /// </summary>
    /// <param name="moisture"> true if the user wants to apply the moist soil </param>
    Forest(bool moisture);

public:
    /// <summary>
    /// Singleton Design Pattern: return the static instance and initialise it only if it's not been already done
    /// </summary>
    /// <param name="moisture"> true if the user wants to apply the moist soil </param>
    /// <returns> pointer to the Forest object </returns>
    static Forest* getForest(bool moisture);

    // Getter
    int getTotalTrees(void);

    // Getter
    int getTotalMoisture(void);

    // Getter
    int getTotalDry(void);

    // Getter
    int getDeadTrees(void);

    // Getter
    int getDeadMoisture(void);

    // Getter
    int getDeadDry(void);

    // Getter
    int getLiveTrees(void);

    // Getter
    int getLiveMoisture(void);

    // Getter
    int getLiveDry(void);

    // Getter
    int getBurningTrees(void);

    /// <summary>
    /// Update the state of the trees in the forest
    /// </summary>
    /// <param name="wind">pointer to the wind object</param>
    /// <returns> true when there are no more burning trees and therefore the fire finished </returns>
    bool updateForest(Wind* wind);

    /// <summary>
    /// Burn neighborhoods of a tree which location in the forest is passed as parameters
    /// </summary>
    ///<param name="row"> The row index of the tree position in the 2D Array </param>
    ///<param name="column"> The column index of the tree position in the 2D Array </param>
    /// <param name="wind"> Pointer to the wind object </param>
    void burnNeighbour(int row, int column, Wind* wind);

    /// <summary>
    /// Draw the 2D forest on the console
    /// </summary>
    void drawForest(void);
};
#endif
