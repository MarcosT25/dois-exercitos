#include "../headers/army.h"
#include <iostream>
using namespace std;

void Army::setColor(int c)
{
    color = c;
}
void Army::setMessengerCount(int m)
{
    messengerCount = m;
}
void Army::setWaitTime(int t)
{
    waitTime = t;
}
void Army::setSuccess(bool s)
{
    success = s;
}
int Army::getColor() const
{
    return color;
}
int Army::getMessengerCount() const
{
    return messengerCount;
}
int Army::getWaitTime() const
{
    return waitTime;
}
bool Army::getSuccess() const
{
    return success;
}
void Army::sendMessenger()
{
    messengerCount = messengerCount - 1;
}
void Army::flareShot()
{
    success = true;
}
