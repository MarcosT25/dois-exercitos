#include "../headers/messenger.h"
#include "../headers/functions.h"
#include <iostream>
using namespace std;

void Messenger::setColor(char *c)
{
    color = c;
}
void Messenger::setStatus(bool s)
{
    alive = s;
}
void Messenger::setTravelTime()
{
    travelTime = travelTimeFunction();
}
void Messenger::setPossibleMessage()
{
    possibleMessage = possibleTime();
}
char *Messenger::getColor() 
{
    return color;
}
bool Messenger::getStatus() const
{
    return alive;
}
int Messenger::getTravelTime() const
{
    return travelTime;
}
bool Messenger::getPossibleMessage() const
{
    return possibleMessage;
}
void Messenger::castleCapture()
{
    if (castleCaptureFunction())
    {
        alive = false;
    }
}