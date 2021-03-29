#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Tree
{
private:
    char state;
    Tree* next = NULL;
    int row, column;
    
public:
    Tree(int row, int column)
    {
        state = '&';
        this->row = row;
        this->column = column;
    }
    
    Tree(int row, int column, char state)
    {
        this->state = state;
        this->row = row;
        this->column = column;
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
    
    bool ifDeleted()
    {
        int randNumber = rand() % + 2;
        if(randNumber == 0)
        {
            return false;
        }
        else
        {
            return true;
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
    char value;
    bool end = false, finish = true;
    int round = 1;
    
    srand(static_cast<unsigned int>(time(nullptr)));

    Forest forest;
    forest.initialiseForest();

    while(end == false && finish == true)
    {
        cout << "Round: " << round <<endl<<endl;
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
        cout << "Program ended: no more trees to burn" << endl << endl;
    }
    else
    {
        cout << "Program ended: key 'x' entered" << endl << endl;
    }
    return 0;
}
