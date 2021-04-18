#ifndef WINDH
#define WINDH
#include <string>

using namespace std;
class Wind
{
private:
    string direction; // Either North, South, East and West
    int speed; // Velocity in Km/h
    
public:
    Wind(void); // Public constructor
    string getDirection(void); // Getter
    int getSpeed(void); // Getter
};
#endif
