#include "../headers/messenger.h"
#include "../headers/functions.h"
#include <iostream>
using namespace std;

void Messenger::setColor(int c)
{
    color = c;
}
void Messenger::setStatus(bool s)
{
    status = s;
}
void Messenger::setTravelTime()
{
    travelTime = travelTimeFunction();
}
void Messenger::setPossibleMessage()
{
    possibleMessage = possibleTime();
}
int Messenger::getColor() const
{
    return color;
}
bool Messenger::getStatus() const
{
    return status;
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
        status = false;
    }
}