#include "forest.h"
#include <iostream>

using namespace std;

Forest* Forest::_pointer = nullptr; // out of line definition of static pointer

/// <summary>
/// Private constructor initialise forest with boundary and burning tree at the center
/// Set the counters attributes of the forest
/// </summary>
/// <param name="moisture"> true if the user wants to apply the moist soil </param>
Forest::Forest(bool moisture)
{
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            // If it is the boundary, do not create the object and add set the cell value a 0
            if (i == 0 || j == 0 || i == 20 || j == 20)
            {
                forestArray[i][j] = '0';
            }
            // If the cell is the center of the forest, creates a burning tree, add into the list
            else if ((i == 10) && (j == 10))
            {
                Tree* tree = new Tree(i, j, '#', moisture);
                forestArray[i][j] = tree->getState();
                list.appendTree(tree);
                if (tree->getMoisture())
                {
                    totalMoisture++;
                }
                else
                {
                    totalDry++;
                }
            }
            else
            {
                Tree* tree = new Tree(i, j, moisture);
                forestArray[i][j] = tree->getState();
                list.appendTree(tree);
                if (tree->getMoisture())
                {
                    totalMoisture++;
                }
                else
                {
                    totalDry++;
                }
            }
        }
    }
    // set counters
    totalTrees = totalDry + totalMoisture;
    liveTrees = totalTrees;
    liveDry = totalDry;
    liveMoisture = totalMoisture;
    burningTrees = list.countBurning();
}

/// <summary>
/// return the static instance and initialise only if it has not been already defined
/// </summary>
/// <param name="moisture"> true if the user wants to apply the moist soil </param>
Forest* Forest::getForest(bool moisture)
{
    if(_pointer == nullptr)
    {
        _pointer = new Forest(moisture);
    }
    return _pointer;
}

// Getter
int Forest::getTotalTrees(void)
{
    return totalTrees;
}

// Getter
int Forest::getTotalMoisture(void)
{
    return totalMoisture;
}

// Getter
int Forest::getTotalDry(void)
{
    return totalDry;
}

// Getter
int Forest::getDeadTrees(void)
{
    return deadTrees;
}

// Getter
int Forest::getDeadMoisture(void)
{
    return deadMoisture;
}

// Getter
int Forest::getDeadDry(void)
{
    return deadDry;
}

// Getter
int Forest::getLiveTrees(void)
{
    return liveTrees;
}

// Getter
int Forest::getLiveMoisture(void)
{
    return liveMoisture;
}

// Getter
int Forest::getLiveDry(void)
{
    return liveDry;
}

// Getter
int Forest::getBurningTrees(void)
{
    return burningTrees;
}

/// <summary>
/// Update the state of the trees in the forest
/// </summary>
/// <param name="wind"></param>
/// <returns> false when at least one tree has been removed </returns>
bool Forest::updateForest(Wind* wind)
{
    bool finish = true;
    
    // Move through the forest
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            if (forestArray[i][j] == '#')
            {
                burnNeighbour(i, j, wind);
                list.removeTree(i, j);
                forestArray[i][j] = ' ';
                if (finish == true)
                {
                    finish = false;
                }
            }
        }
    }
    
    // Update counters each time the forest is updated
    liveTrees = list.countTrees();
    liveMoisture = list.countMoisture();
    liveDry = liveTrees - liveMoisture;
    
    deadTrees = totalTrees - liveTrees;
    deadMoisture = totalMoisture - liveMoisture;
    deadDry = totalDry - liveDry;
    
    burningTrees = list.countBurning();
    
    return finish;
}

/// <summary>
/// Burn neighborhoods of a tree whose location is passed by parameters
/// </summary>
///<param name="row"> The row index of the tree position in the 2D Array </param>
///<param name="column"> The column index of the tree position in the 2D Array </param>
/// <param name="wind"> Pointer to a wind object </param>
void Forest::burnNeighbour(int row, int column, Wind* wind)
{
    // tree on the left
    // If it exists and if it is not burning
    if (list.elementExist(row, column - 1) && list.getElement(row, column - 1)->getState() != '#')
    {
        // Pass the pointer only if it is initialised and if the direction is West
        if (wind != nullptr && wind->getDirection() == "West")
        {
            if (list.getElement(row, (column - 1))->ifDeleted(wind))
            {
                list.getElement(row, (column - 1))->setState('#');
                forestArray[row][column - 1] = '#';
            }
        }
        else
        {
            if (list.getElement(row, (column - 1))->ifDeleted(nullptr))
            {
                list.getElement(row, (column - 1))->setState('#');
                forestArray[row][column - 1] = '#';
            }
        }
    }
    
    // tree on the right
    if (list.elementExist(row, column + 1) && list.getElement(row, column + 1)->getState() != '#')
    {
        // Pass the pointer only if it is initialised and if the direction is East
        if (wind != nullptr && wind->getDirection() == "East")
        {
            if (list.getElement(row, column + 1)->ifDeleted(wind))
            {
                list.getElement(row, (column + 1))->setState('#');
                forestArray[row][column + 1] = '#';
            }
        }
        else
        {
            if (list.getElement(row, column + 1)->ifDeleted(nullptr))
            {
                list.getElement(row, (column + 1))->setState('#');
                forestArray[row][column + 1] = '#';
            }
        }
    }
    // upper tree
    if (list.elementExist(row - 1, column) && list.getElement(row - 1, column)->getState() != '#')
    {
        // Pass the pointer only if it is initialised and if the direction is North
        if (wind != nullptr && wind->getDirection() == "North")
        {
            if (list.getElement(row - 1, column)->ifDeleted(wind))
            {
                list.getElement((row - 1), column)->setState('#');
                forestArray[row - 1][column] = '#';
            }
        }
        else
        {
            if (list.getElement(row - 1, column)->ifDeleted(nullptr))
            {
                list.getElement((row - 1), column)->setState('#');
                forestArray[row - 1][column] = '#';
            }
        }
    }
    
    // bottom tree
    if (list.elementExist(row + 1, column) && list.getElement(row + 1, column)->getState() != '#')
    {
        // Pass the pointer only if it is initialised and if the direction is South
        if (wind != nullptr && wind->getDirection() == "South")
        {
            if (list.getElement(row + 1, column)->ifDeleted(wind))
            {
                list.getElement((row + 1), column)->setState('#');
                forestArray[row + 1][column] = '#';
            }
        }
        else
        {
            if (list.getElement(row + 1, column)->ifDeleted(nullptr))
            {
                list.getElement((row + 1), column)->setState('#');
                forestArray[row + 1][column] = '#';
            }
        }
    }
}

/// <summary>
/// Display the 2D forest on the console
/// </summary>
void Forest::drawForest(void)
{
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            cout << forestArray[i][j];
        }
        cout << endl;
    }
}
