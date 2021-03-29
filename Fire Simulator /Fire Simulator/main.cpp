#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Wind
{
private:
    string type;
public:
    Wind()
    {
        int randNumber = rand() % + 4;
        
        switch(randNumber)
        {
            case 0:
                type = "North";
                break;
            case 1:
                type = "South";
                break;
            case 2:
                type = "East";
                break;
            case 3:
                type = "West";
                break;
            default:
                break;
        }
    }
    string getType()
    {
        return type;
    }
};

class Tree
{
private:
    char state;
    bool wind;
    Tree* next = NULL; // next object in the list
    int row, column; // indexes in the 2D Array
    
public:
    ///<summary>
    /// Default constructor creates a new tree object
    ///<summary>
    ///<param name="row">The row index of the tree position in the 2D Array </param>
    ///<param name="column">The column index of the tree position in the 2D Array </param>
    Tree(int row, int column)
    {
        state = '&';
        this->row = row;
        this->column = column;
        wind = false;
    }
    
    ///<summary>
    /// Overloaded constructor creates a new tree object with no default state
    ///<summary>
    ///<param name="row">The row index of the tree position in the 2D Array </param>
    ///<param name="column">The column index of the tree position in the 2D Array </param>
    ///<param name="state">current state of the object</param>
    Tree(int row, int column, char state)
    {
        this->state = state;
        this->row = row;
        this->column = column;
        wind = false;
    }
    
    void setWind(bool value)
    {
        wind = value;
    }
    
    bool getWind()
    {
        return wind;
    }
    
    void setState(char state)
    {
        this->state = state;
    }
    
    char getState()
    {
        return state;
    }
    
    void setNext(Tree* current)
    {
        this->next = current;
    }
    
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
        if ((this->row == row)&&(this->column == column))
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
        if(state == '#')
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
    ///<summary>
    bool ifDeleted()
    {
        int randNumber;

        if(wind == true)
        {
            // 66% of probability to catch the fire
            randNumber = rand() % + 3;
            if(randNumber != 2)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            // 50% of probability to catch the fire
            randNumber= rand() % + 2;
            if(randNumber == 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
};

class ListOfTrees
{
private:
    Tree* start;
    Tree* end;

public:
    ListOfTrees()
    {
        start = NULL;
        end = NULL;
    }

    bool isEmpty()
    {
        if (start == NULL && end == NULL)
        {
            return true;
        }
        return false;
    }
    
    int countElements()
    {
        int number = 0;
        Tree* current = start;
        
        while(current != NULL)
        {
            number++;
            current = current->getNext();
        }
        return number;
    }
    
    int countBurning()
    {
        int number = 0;
        Tree* current = start;
        while (current != NULL)
        {
            if(current->isBurning())
            {
                number++;
            }
            current = current->getNext();
        }
        return number;
    }
    
    void addTree(Tree* object)
    {
        object->setNext(start);
        start = object;
    }
    
    bool elementExist(int row, int column)
    {
        Tree* current = start;
        
        while(current != NULL)
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
    
    Tree* getElement(int row, int column)
    {
        Tree* current = start;
        
        while(current != NULL)
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
    
    void removeTree(int row, int column)
    {
        Tree* current = start;
        Tree* previous = nullptr;
    
        while(current != NULL)
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
    
    void removeFirst()
    {
        Tree* current = start;
        start = start->getNext();
        delete current;
    }
    
    void removeLast()
    {
        Tree* current;
        Tree* previous = nullptr;
        current = start;
        while(current->getNext() != NULL)
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
    
    ListOfTrees getList()
    {
        return list;
    }

    void initialiseForest()
    {
        for (int i = 0; i < 21; i++)
        {
            for (int j = 0; j < 21; j++)
            {
                if(i == 0 || j == 0 || i == 20 || j == 20 )
                {
                    forestArray[i][j] = '0';
                }
                else if ((i == 10) && (j == 10))
                {
                    Tree* tree = new Tree(i, j, '#');
                    forestArray[i][j] = tree->getState();
                    list.addTree(tree);
                }
                else
                {
                    Tree* tree = new Tree(i, j);
                    forestArray[i][j] = tree->getState();
                    list.addTree(tree);
                }
            }
        }
    }
    
    bool updateForest()
    {
        bool finish = false;

        for (int i = 0; i < 21; i++)
        {
            for (int j = 0; j < 21; j++)
            {
                if (forestArray[i][j] != '0')
                {
                    if(forestArray[i][j] == '#')
                    {
                        burnNeighorhood(i, j);
                        list.removeTree(i, j);
                        forestArray[i][j] = ' ';
                        if (finish == false)
                        {
                            finish = true;
                        }
                    }
                }
            }
        }
        return finish;
    }
    
    string applyWind()
    {
        Wind wind;
        if(wind.getType() == "North")
        {
            for(int i = 1; i <= 10; i++)
            {
                for(int j = 1; j < 20; j++)
                {
                    list.getElement(i, j)->setWind(true);
                }
            }
        }
        else if(wind.getType() == "South")
        {
            for(int i = 11; i < 20; i++)
            {
                for(int j = 1; j < 20; j++)
                {
                    list.getElement(i, j)->setWind(true);
                }
            }
        }
        else if(wind.getType() == "East")
        {
            for(int i = 1; i < 20; i++)
            {
                for(int j = 11; j < 20; j++)
                {
                    list.getElement(i, j)->setWind(true);
                }
            }
        }
        else if(wind.getType() == "West")
        {
            for(int i = 1; i < 20; i++)
            {
                for(int j = 1; j <= 10; j++)
                {
                    list.getElement(i, j)->setWind(true);
                }
            }
        }
        return wind.getType();
    }

    void burnNeighorhood(int row, int column)
    {
        if(list.elementExist(row, column - 1) && list.getElement(row, (column - 1))->ifDeleted())
        {
            list.getElement(row, (column - 1))->setState('#');
            forestArray[row][column - 1] = '#';
        }

        if(list.elementExist(row, column + 1) && list.getElement(row, column + 1)->ifDeleted())
        {
            list.getElement(row, (column + 1))->setState('#');
            forestArray[row][column + 1] = '#';
        }
        
        if(list.elementExist(row - 1, column) && list.getElement(row - 1, column)->ifDeleted())
        {
            list.getElement((row - 1), column)->setState('#');
            forestArray[row - 1][column] = '#';
        }

        if(list.elementExist(row + 1, column) && list.getElement(row + 1, column)->ifDeleted())
        {
            list.getElement((row + 1), column)->setState('#');
            forestArray[row + 1][column] = '#';
        }
    }
    
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

int main()
{
    string wind;
    char userChoice, value;
    bool end = false, finish = true;
    int round = 1;
    
    srand(static_cast<unsigned int>(time(nullptr)));
    Forest forest;
    forest.initialiseForest();
    
    cout << "Welcome to Tree Simulator" << '\n' << "----------------" << endl << endl;
    cout << "Add wind and moisture effect to the simulation? [Y/N]: ";
    cin >> userChoice;
    if (tolower(userChoice) == 'y')
    {
        wind = forest.applyWind();
    }
    cin.ignore();
    while(end == false && finish == true)
    {
        cout << "TREE SIMULATOR" << '\n' << "----------------" << endl << endl;
        cout << "LEGEND" << endl;
        cout << " - &: Tree alive" << '\n' << " - #: Burning Tree" << '\n'
             << " - ' ': Death Tree"<< '\n' << endl << endl;
        cout << "IMPLEMENTATIONS: " << '\n' << " - Wind direction: " << wind
             << '\n' << "----------------" << endl << endl;

        cout << "Round: " << round << endl << endl;
        forest.drawForest();

        cout << endl;
        cout << "Press enter to continue or 'x' to exit..." << endl;
        value = cin.get();
        
        if(value == '\n')
        {
            finish = forest.updateForest();
            round++;
        }
        else if (value != 'x')
        {
            cin.ignore();
        }
        else
        {
            end = true;
        }
    }
    if (finish == false)
    {
        cout << "Program ended:" << endl << endl;
        round--;
    }
    else
    {
        cout << "Program ended: key 'x' entered" << endl << endl;;
    }
    cout << "STATISTICS:" << endl;
    cout << " - Total Rounds: " << round << endl << endl;
    cout << " - Tree alive: " << forest.getList().countElements() << endl;
    cout << " - Tree death: " << 361 - forest.getList().countElements() << endl;
    if(forest.getList().countBurning() > 0)
    {
        cout << " - Tree burning: " << forest.getList().countBurning() << endl;
    }
    cout << endl;
    cout << "Press any key to end the program..." << endl;
    cin.get();
    
    return 0;
}
