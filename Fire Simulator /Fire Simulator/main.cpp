#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>

using namespace std;

class Wind
{
private:
    string direction; // Either North, South, East and West
    int speed; // Velocity in Km/h
public:
    /// <summary>
    /// Public Constructor
    /// </summary>
    Wind()
    {
        int randNumber = rand() % +4;

        this->speed = rand() % 26 + 10;

        // Constructor randomly decides the direction of Wind
        switch (randNumber)
        {
        case 0:
            direction = "North";
            break;
        case 1:
            direction = "South";
            break;
        case 2:
            direction = "East";
            break;
        case 3:
            direction = "West";
            break;
        default:
            break;
        }
    }

    // Getter
    string getDirection()
    {
        return direction;
    }

    // Getter
    int getSpeed()
    {
        return speed;
    }
};

class Tree
{
private:
    char state;
    bool moisture; // True for moist / False for dry
    Tree* next = nullptr; // Next object in the listOfTrees
    int row, column; // location (x, y) in the 2D forestArray

    /// <summary>
    /// private method, 50% of probability to allow the moisture (true)
    /// </summary>
    bool setMoisture()
    {
        int randNumber = rand() % +2;
        if (randNumber == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

public:

    ///<summary>
    /// Default constructor creates a tree object
    ///<summary>
    ///<param name="row"> The row index of the tree position in the 2D Array </param>
    ///<param name="column"> The column index of the tree position in the 2D Array </param>
    ///<param name="moist"> True if the user wants to apply the moisture </param>
    Tree(int row, int column, bool moist)
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
    Tree(int row, int column, char state, bool moist)
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
    void setState(char state)
    {
        this->state = state;
    }

    // Getter
    char getState()
    {
        return state;
    }

    // Setter
    void setNext(Tree* current)
    {
        this->next = current;
    }

    // Getter
    Tree* getNext()
    {
        return next;
    }

    ///<summary>
    /// Checks whether the object having those indexes exists in the list
    ///<summary>
    ///<param name="row">The row index of the tree position in the 2D Array </param>
    ///<param name="column">The column index of the tree position in the 2D Array </param>
    bool checkCoordinates(int row, int column)
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

    bool isBurning()
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
    bool ifDeleted(Wind* wind)
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
};

class ListOfTrees
{
private:
    Tree* start;
    Tree* end;

public:

    /// <summary>
    /// Constructor for the list
    /// </summary>
    ListOfTrees()
    {
        start = NULL;
        end = NULL;
    }

    /// <summary>
    /// Return true when the list is empty
    /// </summary>
    bool isEmpty()
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
    int countElements()
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
    /// Return the number of burning trees
    /// </summary>
    int countBurning()
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
    void appendTree(Tree* object)
    {
        object->setNext(start);
        start = object;
    }

    /// <summary>
    /// Check whether an element having a certain location exists
    /// </summary>
    ///<param name="row">The row index of the tree position in the 2D Array </param>
    ///<param name="column">The column index of the tree position in the 2D Array </param>
    bool elementExist(int row, int column)
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
    Tree* getElement(int row, int column)
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
    void removeTree(int row, int column)
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
                    break;
                }
            }
        }
    }

    /// <summary>
    /// Remove the first element from the list
    /// </summary>
    void removeFirst()
    {
        Tree* current = start;
        start = start->getNext();
        delete current;
    }

    /// <summary>
    /// Remove the last element from the list
    /// </summary>
    void removeLast()
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
};

class Forest
{
private:
    char forestArray[21][21];
    ListOfTrees list;

public:

    // Getter
    ListOfTrees getList()
    {
        return list;
    }

    /// <summary>
    /// Initialise entire forest with boundary and burning tree at the center
    /// </summary>
    /// <param name="moisture"> true if the user wants to apply the moist soil </param>
    void initialiseForest(bool moisture)
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
                // If the cell is the center of the forest, creates a burning tree and add into the list
                else if ((i == 10) && (j == 10))
                {
                    Tree* tree = new Tree(i, j, '#', moisture);
                    forestArray[i][j] = tree->getState();
                    list.appendTree(tree);
                }
                else
                // Creates a default tree and add into the list
                {
                    Tree* tree = new Tree(i, j, moisture);
                    forestArray[i][j] = tree->getState();
                    list.appendTree(tree);
                }
            }
        }
    }
    
    /// <summary>
    /// Update the state of the trees in the forest
    /// </summary>
    /// <param name="wind"></param>
    /// <returns> false when at least one tree has been removed </returns>
    bool updateForest(Wind* wind)
    {
        bool finish = true;

        // Move through the forest
        for (int i = 0; i < 21; i++)
        {
            for (int j = 0; j < 21; j++)
            {
                if (forestArray[i][j] == '#')
                {
                    burnNeighorhood(i, j, wind);
                    list.removeTree(i, j);
                    forestArray[i][j] = ' ';
                    if (finish == true)
                    {
                        finish = false;
                    }
                }
            }
        }
        return finish;
    }

    /// <summary>
    /// Burn neighborhoods of a tree whose location is passed by parameters
    /// </summary>
    ///<param name="row"> The row index of the tree position in the 2D Array </param>
    ///<param name="column"> The column index of the tree position in the 2D Array </param>
    /// <param name="wind"> Pointer to a wind object </param>
    void burnNeighorhood(int row, int column, Wind* wind)
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
    void drawForest()
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
};

class Program
{
public:
    /// <summary>
    /// Prompts the user to choose the simulator mode
    /// </summary>
    /// <returns>the user choice</returns>
    static bool chooseMode(string question)
    {
        char userChoice;

        cout << question;
        cin >> userChoice;
        cin.ignore();
        cout << endl;

        if (tolower(userChoice) == 'y')
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /// <summary>
    /// Display both the title and the legend
    /// </summary>
    /// <param name="wind">pointer to a Wind object</param>
    /// <param name="round">round of the simulation</param>
    static void displayMenu(Wind* wind, int round)
    {
        system("CLS");
        cout << "FIRE SIMULATOR" << '\n' << "----------------" << endl << endl;
        cout << "LEGEND" << endl;
        if (wind != nullptr)
        {
            cout << " - Wind direction: " << wind->getDirection() << '\n' << " - Wind speed: " << wind->getSpeed() << "Km/h"
                << '\n' << " - @: Tree with most soil" << endl;

        }
        cout << " - &: Tree with dry soil" << '\n' << " - #: Burning Tree" << '\n' << " - ' ': Death Tree" << '\n' << "----------------" << endl << endl;
        cout << "Round: " << round << endl << endl;
    }
    
    static bool writeOnFile(Wind* wind, int round, int alive, int death, int burning)
    {
        ofstream outFile;
        outFile.open("statistics.txt");
        
        if (outFile.is_open() == false)
        {
            return false;
        }
        else
        {
            outFile << "STATISTICS" << '\n'
                    << " - Total Rounds: " << to_string(round) << '\n';

            if(wind != nullptr)
            {
                outFile << " - Wind direction: " << wind->getDirection() << '\n'
                        << " - Wind speed: " << to_string(wind->getSpeed()) << "Km/h" << '\n';
            }
            outFile << " - Trees alive: " << to_string(alive) << '\n'
                    << " - Trees death: " << to_string(death) << '\n'
                    << " - Trees burning: " << to_string(burning);
            
            outFile.close();
            return true;
        }
    }
};

int main()
{
    bool userChoice;
    char value;
    bool end = false, finish = false;
    int round = 1;

    srand(static_cast<unsigned int>(time(nullptr)));

    Wind* wind = nullptr;
    Forest forest;
    
    cout << "Welcome to Fire Simulator" << '\n' << "----------------" << endl << endl;
    userChoice = Program::chooseMode("Add wind and moisture effect to the simulation? [Y/N]: ");

    // Initialise the Wind pointer only if the user wants to apply the wind to the simulation
    if (userChoice)
    {
        wind = new Wind();
    }

    forest.initialiseForest(userChoice);

    // As long as the user click 'x' or there are no more burning trees
    while (end == false && finish == false)
    {
        Program::displayMenu(wind, round);
        forest.drawForest();

        cout << endl;
        cout << "Press enter to continue or 'x' to exit..." << endl;
        value = cin.get();

        if (value == '\n')
        {
            finish = forest.updateForest(wind);
            round++;
        }
        else if (tolower(value) != 'x')
        {
            cin.ignore();
        }
        else
        {
            end = true;
        }
    }
    if (finish == true)
    {
        cout << "Program ended:" << endl << endl;
        round--;
    }
    else
    {
        cout << "Program ended: key 'x' entered" << endl << endl;;
    }
    system("CLS");

    // Display statistics of the simulation
    cout << "STATISTICS:" << '\n' << "----------------" << '\n';
    cout << " - Total Rounds: " << round << '\n' << '\n';
    if (wind != nullptr)
    {
        cout << " - Wind direction: " << wind->getDirection() << '\n'
             << " - Wind speed: " << wind->getSpeed() << "Km/h" << '\n';
    }
    cout << " - Tree alive: " << forest.getList().countElements() << '\n'
         << " - Tree death: " << 361 - forest.getList().countElements() << '\n'
         << " - Tree burning: " << forest.getList().countBurning() << endl;

    cout << endl;
    userChoice = Program::chooseMode("Do you want to print the statistics on a file? [Y/N]: ");
    cout << endl;
    
    if(userChoice)
    {
        bool successful = Program::writeOnFile(wind, round, forest.getList().countElements(),
                                               361 - forest.getList().countElements(),
                                               forest.getList().countBurning());
        if(successful)
        {
            cout << "statistics.txt successfully created." << endl;
        }
        else
        {
            cout << "File could not be created." << endl;
        }
    }
    cout << endl;
    cout << "Press any key to end the program..." << endl;
    cin.get();

    return 0;
}
