#include "listOfTrees.h"

ListOfTrees* ListOfTrees::_pointer = nullptr; // out of line definition of static pointer

ListOfTrees::ListOfTrees(void)
{
    start = NULL;
    end = NULL;
}

ListOfTrees* ListOfTrees::getList()
{
    if (_pointer == nullptr)
    {
        _pointer = new ListOfTrees();
    }
    return _pointer;
}

bool ListOfTrees::isEmpty(void)
{
    if (start == NULL && end == NULL)
    {
        return true;
    }
    return false;
}

int ListOfTrees::countTrees(void)
{
    int number = 0;
    Tree* current = start;

    // Iterate through the linked list
    while (current != NULL)
    {
        number++;
        current = current->getNext();
    }
    return number;
}

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

void ListOfTrees::appendTree(Tree* object)
{
    object->setNext(start);
    start = object;
}

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

void ListOfTrees::removeTree(int row, int column)
{
    Tree* current = start;
    Tree* previous = nullptr;

    while (current != NULL)
    {
        // If the element is not in the required location, it moves further
        if (!(current->checkCoordinates(row, column)))
        {
            previous = current;
            current = current->getNext();
        }
        else
        {
            // Runs when it is the first element in the linked list
            if (previous == nullptr)
            {
                removeFirst();
                break;
            }
            // Runs if it is the last element in the linked list
            else if (current->getNext() == NULL)
            {
                removeLast();
                break;
            }
            else // it is in the middle of the list
            {
                previous->setNext(current->getNext());
                delete current;
                break;
            }
        }
    }
}

void ListOfTrees::removeFirst(void)
{
    Tree* current = start;
    start = start->getNext();
    delete current;
}

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
