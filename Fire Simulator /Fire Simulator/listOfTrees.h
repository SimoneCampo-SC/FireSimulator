#ifndef LISTOFTREESH
#define LISTOFTREESH
#include "tree.h"

class ListOfTrees
{
private:
    Tree* start; // first element in the Linked List
    Tree* end;  // last element in the Linked List

public:
    /// <summary>
    /// Default constructor of the list
    /// </summary>
    ListOfTrees(void);

    /// <summary>
    /// Return true when the list is empty
    /// </summary>
    bool isEmpty(void);

    /// <summary>
    /// Return the number of elements in the list
    /// </summary>
    int countTrees(void);

    /// <summary>
    /// Return the number of trees within the list having the moisture
    /// </summary>
    int countMoisture(void);

    /// <summary>
    /// Return the number of burning trees
    /// </summary>
    int countBurning(void);

    /// <summary>
    /// append a tree object in the list
    /// </summary>
    /// <param name="object">object tree to be added</param>
    void appendTree(Tree* object);

    /// <summary>
    /// Check whether an element having a certain location exists
    /// </summary>
    ///<param name="row">The row index of the tree position in the 2D Array </param>
    ///<param name="column">The column index of the tree position in the 2D Array </param>
    bool elementExist(int row, int column);

    /// <summary>
    /// Return an element in the list given their location
    /// Return NULL if the element does not exist
    /// </summary>
    ///<param name="row">The row index of the tree position in the 2D Array </param>
    ///<param name="column">The column index of the tree position in the 2D Array </param>
    Tree* getElement(int row, int column);

    /// <summary>
    /// Remove a tree object from the list
    /// </summary>
    ///<param name="row">The row index of the tree position in the 2D Array </param>
    ///<param name="column">The column index of the tree position in the 2D Array </param>
    void removeTree(int row, int column);

    /// <summary>
    /// Remove the first element from the list
    /// </summary>
    void removeFirst(void);

    /// <summary>
    /// Remove the last element from the list
    /// </summary>
    void removeLast(void);
};
#endif
