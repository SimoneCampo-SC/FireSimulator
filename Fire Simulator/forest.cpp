#include "forest.h"
#include <iostream>

using namespace std;

Forest* Forest::_pointer = nullptr; // out of line definition of static pointer

Forest::Forest(bool moisture)
{
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            // Draw the boundaries and do not create the object
            if (i == 0 || j == 0 || i == 20 || j == 20)
            {
                forestArray[i][j] = '0';
            }
            // If the cell is the center of the forest, creates a burning tree, add into the list
            else if ((i == 10) && (j == 10))
            {
                Tree* tree = new Tree(i, j, '#', moisture);
                forestArray[i][j] = tree->getState();
                list->appendTree(tree);
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
                list->appendTree(tree);
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
    // when the forest has initialised, it sets the counters
    totalTrees = totalDry + totalMoisture;
    liveTrees = totalTrees;
    liveDry = totalDry;
    liveMoisture = totalMoisture;
    burningTrees = list->countBurning();
}

Forest* Forest::getForest(bool moisture)
{
    // Execute the constructor only if the static pointer has not been initialised
    if (_pointer == nullptr)
    {
        _pointer = new Forest(moisture);
    }
    return _pointer;
}

int Forest::getTotalTrees(void) { return totalTrees; }

int Forest::getTotalMoisture(void) { return totalMoisture; }

int Forest::getTotalDry(void) { return totalDry; }

int Forest::getDeadTrees(void) { return deadTrees; }

int Forest::getDeadMoisture(void) { return deadMoisture; }

int Forest::getDeadDry(void) { return deadDry; }

int Forest::getLiveTrees(void) { return liveTrees; }

int Forest::getLiveMoisture(void) { return liveMoisture; }

int Forest::getLiveDry(void) { return liveDry; }

int Forest::getBurningTrees(void) { return burningTrees; }

bool Forest::updateForest(Wind* wind)
{
    std::vector<std::pair<int, int>> burningTreesAtStart;

    // Capture the trees that are burning at the beginning of this round.
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            if (forestArray[i][j] == '#')
            {
                burningTreesAtStart.push_back({i, j});
            }
        }
    }

    // Only trees that were already burning at the start of the round
    // are allowed to spread the fire during this timestep.
    for (const auto& position : burningTreesAtStart)
    {
        int row = position.first;
        int column = position.second;

        burnNeighbour(row, column, wind);
    }

    // Burning trees are consumed after propagation.
    for (const auto& position : burningTreesAtStart)
    {
        int row = position.first;
        int column = position.second;

        list->removeTree(row, column);
        forestArray[row][column] = ' ';
    }

    // Update statistics.
    liveTrees = list->countTrees();
    liveMoisture = list->countMoisture();
    liveDry = liveTrees - liveMoisture;

    deadTrees = totalTrees - liveTrees;
    deadMoisture = totalMoisture - liveMoisture;
    deadDry = totalDry - liveDry;

    burningTrees = list->countBurning();

    return burningTrees == 0;
}

void Forest::burnNeighbour(int row, int column, Wind* wind)
{

    // tree on the left
    // If it exists and it is not burning
    if (list->elementExist(row, column - 1) && list->getElement(row, column - 1)->getState() != '#')
    {
        // Pass the pointer only if it is initialised and if the direction is West
        if (wind != nullptr && wind->getDirection() == "West")
        {
            if (list->getElement(row, (column - 1))->ifDeleted(wind))
            {
                list->getElement(row, (column - 1))->setState('#');
                forestArray[row][column - 1] = '#';
            }
        }
        else
        {
            if (list->getElement(row, (column - 1))->ifDeleted(nullptr))
            {
                list->getElement(row, (column - 1))->setState('#');
                forestArray[row][column - 1] = '#';
            }
        }
    }

    // tree on the right
    // If it exists and it is not burning
    if (list->elementExist(row, column + 1) && list->getElement(row, column + 1)->getState() != '#')
    {
        // Pass the pointer only if it is initialised and if the direction is East
        if (wind != nullptr && wind->getDirection() == "East")
        {
            if (list->getElement(row, column + 1)->ifDeleted(wind))
            {
                list->getElement(row, (column + 1))->setState('#');
                forestArray[row][column + 1] = '#';
            }
        }
        else
        {
            if (list->getElement(row, column + 1)->ifDeleted(nullptr))
            {
                list->getElement(row, (column + 1))->setState('#');
                forestArray[row][column + 1] = '#';
            }
        }
    }

    // Upper tree
    // If it exists and it is not burning
    if (list->elementExist(row - 1, column) && list->getElement(row - 1, column)->getState() != '#')
    {
        // Pass the pointer only if it is initialised and if the direction is North
        if (wind != nullptr && wind->getDirection() == "North")
        {
            if (list->getElement(row - 1, column)->ifDeleted(wind))
            {
                list->getElement((row - 1), column)->setState('#');
                forestArray[row - 1][column] = '#';
            }
        }
        else
        {
            if (list->getElement(row - 1, column)->ifDeleted(nullptr))
            {
                list->getElement((row - 1), column)->setState('#');
                forestArray[row - 1][column] = '#';
            }
        }
    }

    // Bottom tree
    // If it exists and it is not burning
    if (list->elementExist(row + 1, column) && list->getElement(row + 1, column)->getState() != '#')
    {
        // Pass the pointer only if it is initialised and if the direction is South
        if (wind != nullptr && wind->getDirection() == "South")
        {
            if (list->getElement(row + 1, column)->ifDeleted(wind))
            {
                list->getElement((row + 1), column)->setState('#');
                forestArray[row + 1][column] = '#';
            }
        }
        else
        {
            if (list->getElement(row + 1, column)->ifDeleted(nullptr))
            {
                list->getElement((row + 1), column)->setState('#');
                forestArray[row + 1][column] = '#';
            }
        }
    }
}

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
