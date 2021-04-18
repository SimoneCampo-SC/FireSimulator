#ifndef FORESTH
#define FORESTH

#include "listOfTrees.h"

class Forest
{
private:
    char forestArray[21][21]; // 2D Array having the states of the trees

    // Counters attributes used for the statistics function and they keep track of the number of trees in the list
    int totalTrees = 0, totalMoisture = 0, totalDry = 0;
    int deadTrees = 0, deadMoisture = 0, deadDry = 0;
    int liveTrees = 0, liveMoisture = 0, liveDry = 0;
    int burningTrees = 0;

    ListOfTrees* list = ListOfTrees::getList();
    static Forest* _pointer;

    /// <summary>
    /// Private constructor initialise forest with boundary and burning tree at the center
    /// Set the counters attributes of the forest
    /// </summary>
    /// <param name="moisture"> true if the user wants to apply the moist soil </param>
    Forest(bool moisture);
    
public:
    /// <summary>
    /// return the static instance and initialise only if it has not been already defined
    /// </summary>
    /// <param name="moisture"> true if the user wants to apply the moist soil </param>
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
    /// <param name="wind"></param>
    /// <returns> false when at least one tree has been removed </returns>
    bool updateForest(Wind* wind);
    
    /// <summary>
    /// Burn neighborhoods of a tree whose location is passed by parameters
    /// </summary>
    ///<param name="row"> The row index of the tree position in the 2D Array </param>
    ///<param name="column"> The column index of the tree position in the 2D Array </param>
    /// <param name="wind"> Pointer to a wind object </param>
    void burnNeighbour(int row, int column, Wind* wind);

    /// <summary>
    /// Display the 2D forest on the console
    /// </summary>
    void drawForest(void);
};
#endif
