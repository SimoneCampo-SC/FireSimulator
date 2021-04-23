#include "tree.h"

bool Tree::setMoisture(void)
{
    int randNumber = rand() % + 2; // Randomly either 0 or 1

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

void Tree::setState(char state) { this->state = state; }

char Tree::getState() { return state; }

void Tree::setNext(Tree* current) { this->next = current; }

Tree* Tree::getNext() { return next; }

bool Tree::getMoisture() { return moisture; }

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

bool Tree::ifDeleted(Wind* wind)
{
    int probability;
    int randNumber = rand() % 100 + 1; // Random number from 1 to 100

    // When the tree has a moist soil the probability is set to 40 / 100
    // When the tree has a dry soil the probability is set to 60 / 100
    if (moisture == true)
    {
        probability = 40;
    }
    else
    {
        probability = 60;
    }

    // If the wind is applied, its velocity is added to the probability of catching the fire [Up to + 35]
    if (wind != nullptr)
    {
        probability += wind->getSpeed();
    }

    // Does not catch the fire only if the random number is greater than the number given by the probability
    if (randNumber <= probability)
    {
        return true;
    }
    else
    {
        return false;
    }
}
