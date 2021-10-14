#include "../headers/functions.h"
#include <iostream>
#include <time.h>
using namespace std;

bool possibleTime(void)
{
    int t = rand() % 100 + 1;
    if (t == 1)
    {
        return false;
    }
    else 
    {
        return true;
    }
}

int travelTimeFunction(void)
{
    int t = rand() % 601 + 3600;
    return t;
}

bool castleCaptureFunction(void)
{
    int t = rand() % 100 + 1;
    if (t <= 45) 
    {
        return true;
    }
    else 
    {
        return false;
    }
}