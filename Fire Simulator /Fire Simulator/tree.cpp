#include "tree.h"
/// <summary>
/// private method, 50% of probability to allow the moisture (true)
/// </summary>
bool Tree::setMoisture(void)
{
    int randNumber = rand() % +2; // Randomly either 0 or 1
    
    // 50% probability of returning true
    if (randNumber == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

///<summary>
/// Default constructor creates a tree object
///<summary>
///<param name="row"> The row index of the tree position in the 2D Array </param>
///<param name="column"> The column index of the tree position in the 2D Array </param>
///<param name="moist"> True if the user wants to apply the moisture </param>
Tree::Tree(int row, int column, bool moist)
{
    this->row = row;
    this->column = column;

    // Runs true when user wants to apply moisture AND when the method allows that
    if (moist == true && setMoisture())
    {
        this->moisture = true;
        this->state = '@'; // @ tree with moist soil
    }
    else
    {
        this->moisture = false;
        this->state = '&'; // & tree with dry soil
    }
}

///<summary>
/// Overloaded constructor creates a new tree object with no default state
///<summary>
///<param name="row">The row index of the tree position in the 2D Array </param>
///<param name="column"> The column index of the tree position in the 2D Array </param>
///<param name="state"> current state of the object </param>
///<param name="moist"> True if the user wants to apply the moisture </param>
Tree::Tree(int row, int column, char state, bool moist)
{
    this->state = state;
    this->row = row;
    this->column = column;

    // Runs true when user wants to apply moisture AND when the method allows that
    // State is not changed because it is set by the user
    if (moist == true && setMoisture())
    {
        this->moisture = true;
    }
    else
    {
        this->moisture = false;
    }
}

// Setter
void Tree::setState(char state)
{
    this->state = state;
}

// Getter
char Tree::getState()
{
    return state;
}

// Setter
void Tree::setNext(Tree* current)
{
    this->next = current;
}

// Getter
Tree* Tree::getNext()
{
    return next;
}

// Getter
bool Tree::getMoisture()
{
    return moisture;
}

///<summary>
/// Checks whether the object having those indexes exists in the list
///<summary>
///<param name="row">The row index of the tree position in the 2D Array </param>
///<param name="column">The column index of the tree position in the 2D Array </param>
bool Tree::checkCoordinates(int row, int column)
{
    if ((this->row == row) && (this->column == column))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/// <summary>
/// Return true if the tree is burning
/// </summary>
bool Tree::isBurning()
{
    if (state == '#')
    {
        return true;
    }
    else
    {
        return false;
    }
}

///<summary>
/// Determines whether the tree object has to be deleted
/// Depending on the case, the probability of catching the fire is
///<summary>
bool Tree::ifDeleted(Wind* wind)
{
    int probability;
    int randNumber = rand() % 100 + 1; // random number from 1 to 100

    // When the tree has a moist soil the probability is 40 / 100
    // When the tree has a dry soil the probability is 60 / 100
    if (moisture == true)
    {
        probability = 40;
    }
    else
    {
        probability = 60;
    }

    // If the wind is applied, its velocity is added to the probability of catching the fire
    if (wind != nullptr)
    {
        probability += wind->getSpeed();
    }

    // Does not catch the fire only if the random number is greater than the probability acquired so far
    if (randNumber <= probability)
    {
        return true;
    }
    else
    {
        return false;
    }
}
