#ifndef TREEH
#define TREEH
#include "wind.h"
class Tree
{
private:
    char state; // moist soil, dry soil, death, burning
    bool moisture; // True for moist / False for dry
    Tree* next = nullptr; // Next object in the listOfTrees 
    int row, column; // location (x, y) in the 2D forestArray

    /// <summary>
    /// private method, 50% of probability to allow the moisture (true)
    /// </summary>
    bool setMoisture(void); 

public:

    ///<summary>
    /// Default constructor creates a tree object with default state
    ///<summary>
    ///<param name="row"> The row index of the tree position in the 2D Array </param>
    ///<param name="column"> The column index of the tree position in the 2D Array </param>
    ///<param name="moist"> True if the user wants to apply the moisture </param>
    Tree(int row, int column, bool moist);

    ///<summary>
    /// Overloaded constructor creates a new tree object with no default state
    ///<summary>
    ///<param name="row">The row index of the tree position in the 2D Array </param>
    ///<param name="column"> The column index of the tree position in the 2D Array </param>
    ///<param name="state"> current state of the object </param>
    ///<param name="moist"> True if the user wants to apply the moisture </param>
    Tree(int row, int column, char state, bool moist);

    void setState(char state); // Setter

    char getState(void); // Getter

    void setNext(Tree* current); // Setter

    Tree* getNext(void); // Getter

    bool getMoisture(void); // Getter

    ///<summary>
    /// Checks whether the object having those indexes exists in the list
    ///<summary>
    ///<param name="row">The row index of the tree position in the 2D Array </param>
    ///<param name="column">The column index of the tree position in the 2D Array </param>
    bool checkCoordinates(int row, int column);

    /// <summary>
    /// Return true if the tree is burning
    /// </summary>
    bool isBurning(void);

    ///<summary>
    /// Determine whether the tree object has to be deleted
    /// Depending on the case, the probability of catching the fire ranges from 40% to 95%
    ///<summary>
    bool ifDeleted(Wind* wind);
};
#endif

