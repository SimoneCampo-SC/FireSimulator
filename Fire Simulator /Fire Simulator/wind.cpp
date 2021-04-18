#include "wind.h"

Wind::Wind()
{
    int randNumber = rand() % +4; // Random integer from 0 to 3
    this->speed = rand() % 26 + 10; // Random integer from 10 to 35
    
    // Constructor assigns the direction of Wind according to the number randomly generated
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

string Wind::getDirection(void) // Getter
{
    return direction;
}

int Wind::getSpeed(void) // Getter
{
    return speed;
}
