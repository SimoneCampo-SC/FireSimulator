#ifndef WINDH
#define WINDH
#include <string>

using namespace std;
class Wind
{
private:
    static Wind* _pointer; // private static pointer
    string direction; // Either North, South, East and West
    int speed; // Velocity in Km/h
    Wind(void); // Private constructor
    
public:
    /// <summary>
    /// return the static instance and initialise only if it has not been already defined
    /// </summary>
    static Wind* getWind();
    string getDirection(void); // Getter
    int getSpeed(void); // Getter
};
#endif
