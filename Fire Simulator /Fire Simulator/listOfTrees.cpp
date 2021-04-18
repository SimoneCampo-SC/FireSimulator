#include "listOfTrees.h"

ListOfTrees* ListOfTrees::_pointer = nullptr; // out of line definition of static pointer

/// <summary>
/// Default constructor of the list
/// </summary>
ListOfTrees::ListOfTrees(void)
{
    start = NULL;
    end = NULL;
}

/// <summary>
/// return the static instance and initialise only if it has not been already defined
/// </summary>
ListOfTrees* ListOfTrees::getList()
{
    if(_pointer == nullptr)
    {
        _pointer = new ListOfTrees();
    }
    return _pointer;
}

/// <summary>
/// Return true when the list is empty
/// </summary>
bool ListOfTrees::isEmpty(void)
{
    if (start == NULL && end == NULL)
    {
        return true;
    }
    return false;
}

/// <summary>
/// Return the number of elements in the list
/// </summary>
int ListOfTrees::countTrees(void)
{
    int number = 0;
    Tree* current = start;
    
    while (current != NULL)
    {
        number++;
        current = current->getNext();
    }
    return number;
}

/// <summary>
/// Return the number of trees within the list having the moisture
/// </summary>
int ListOfTrees::countMoisture(void)
{
    int number = 0;
    Tree* current = start;
    
    while (current != NULL)
    {
        if (current->getMoisture())
        {
            number++;
        }
        current = current->getNext();
    }
    return number;
}

/// <summary>
/// Return the number of burning trees
/// </summary>
int ListOfTrees::countBurning(void)
{
    int number = 0;
    Tree* current = start;
    while (current != NULL)
    {
        if (current->isBurning())
        {
            number++;
        }
        current = current->getNext();
    }
    return number;
}

/// <summary>
/// append a tree object in the list
/// </summary>
/// <param name="object">object tree to be added</param>
void ListOfTrees::appendTree(Tree* object)
{
    object->setNext(start);
    start = object;
}

/// <summary>
/// Check whether an element having a certain location exists
/// </summary>
///<param name="row">The row index of the tree position in the 2D Array </param>
///<param name="column">The column index of the tree position in the 2D Array </param>
bool ListOfTrees::elementExist(int row, int column)
{
    Tree* current = start;
    
    while (current != NULL)
    {
        if (current->checkCoordinates(row, column))
        {
            return true;
        }
        else
        {
            current = current->getNext();
        }
    }
    return false;
}

/// <summary>
/// Return an element in the list given their location
/// Return NULL if the element does not exist
/// </summary>
///<param name="row">The row index of the tree position in the 2D Array </param>
///<param name="column">The column index of the tree position in the 2D Array </param>
Tree* ListOfTrees::getElement(int row, int column)
{
    Tree* current = start;
    
    while (current != NULL)
    {
        if (current->checkCoordinates(row, column))
        {
            return current;
        }
        else
        {
            current = current->getNext();
        }
    }
    return NULL;
}

/// <summary>
/// Remove a tree object from the list
/// </summary>
///<param name="row">The row index of the tree position in the 2D Array </param>
///<param name="column">The column index of the tree position in the 2D Array </param>
void ListOfTrees::removeTree(int row, int column)
{
    Tree* current = start;
    Tree* previous = nullptr;
    
    while (current != NULL)
    {
        if (!(current->checkCoordinates(row, column)))
        {
            previous = current;
            current = current->getNext();
        }
        else
        {
            if (previous == nullptr)
            {
                removeFirst();
                break;
            }
            else if (current->getNext() == NULL)
            {
                removeLast();
                break;
            }
            else
            {
                previous->setNext(current->getNext());
                delete current;
                break;
            }
        }
    }
}

/// <summary>
/// Remove the first element from the list
/// </summary>
void ListOfTrees::removeFirst(void)
{
    Tree* current = start;
    start = start->getNext();
    delete current;
}

/// <summary>
/// Remove the last element from the list
/// </summary>
void ListOfTrees::removeLast(void)
{
    Tree* current;
    Tree* previous = nullptr;
    current = start;
    while (current->getNext() != NULL)
    {
        previous = current;
        current = current->getNext();
    }
    end = previous;
    previous->setNext(NULL);
    delete current;
}
