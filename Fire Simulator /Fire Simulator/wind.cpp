#include "wind.h"

Wind* Wind::_pointer = nullptr; // out of line definition of static pointer
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

/// <summary>
/// return the static instance and initialise only if it has not been already defined
/// </summary>
Wind* Wind::getWind()
{
    if(_pointer == nullptr)
    {
        _pointer = new Wind();
    }
    return _pointer;
}

string Wind::getDirection(void) // Getter
{
    return direction;
}

int Wind::getSpeed(void) // Getter
{
    return speed;
}
