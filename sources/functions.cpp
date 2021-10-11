#include "../headers/functions.h"
#include <iostream>
using namespace std;

bool possibleTime(void)
{
    srand(time(NULL));
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
    srand(time(NULL));
    int t = rand() % 601 + 3600;
    return t;
}

bool castleCaptureFunction(void)
{
    srand(time(NULL));
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