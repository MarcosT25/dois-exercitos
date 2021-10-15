#include "../headers/army.h"
#include "../headers/messenger.h"
#include "../headers/functions.h"
#include <iostream>
using namespace std;
#include <string>
#include <ctime>

struct action
    {
        int timestamp;
        char *army;
        char *type;
        bool possibleTime = true;
        bool alive = true;
        bool valid = false;
    };

void structInsert(action actionStruct, action *actionVec) 
{
    for (int i = 29; i >= 0; i--)
    {
        if (actionVec[i].valid)
        {
            if (actionStruct.timestamp < actionVec[i].timestamp)
            {
                actionVec[i+1] = actionVec[i];
            }
            else
            {
                actionVec[i+1] = actionStruct;
                break;
            }
        }
        
    }
}

int main()
{
    srand(time(NULL));
    Army redArmy;
    char vermelho[9] = "Vermelho";
    redArmy.setColor(vermelho);
    redArmy.setMessengerCount(5);
    redArmy.setWaitTime(12601);
    Army blueArmy;
    char azul[5] = "Azul";
    blueArmy.setColor(azul);
    blueArmy.setMessengerCount(10);
    blueArmy.setWaitTime(4201);
    
    action actionVec[30];
    int actualTimestamp;
    int newTimestamp;
    action newAction;
    action *currentAction;

    char enviou[7] = "enviou";
    char recebeu[8] = "recebeu";
    actionVec[0] = {0, vermelho, enviou, true, true, true}; //segundo zero, exército vermelho, enviou, valid = true

    bool endProgram = false;
    int i = 0;
    while (!endProgram)
    {
        currentAction = &actionVec[i];
        if ((*currentAction).valid)
        {
            if ((*currentAction).type == enviou)
            {
                Messenger messenger;
                if ((*currentAction).army == vermelho)
                {
                    if(redArmy.getMessengerCount() > 0)
                    {
                        redArmy.sendMessenger();
                        messenger.setColor(vermelho); 
                        messenger.setTravelTime();
                        messenger.castleCapture();
                        (*currentAction).alive = messenger.getStatus();
                        time_t now = time(0) + (*currentAction).timestamp;
                        char* dt = ctime(&now);
                        string alive;
                        if ((*currentAction).alive)
                        {
                            alive = "vivo";
                        }
                        else 
                        {
                            alive = "morto";
                        }
                        cout << "O exército " << (*currentAction).army << " " << (*currentAction).type << " em " << dt << " um mensageiro " << alive << endl;
                        if (messenger.getStatus())
                        {                            
                            newTimestamp = (*currentAction).timestamp + messenger.getTravelTime();
                            newAction = {newTimestamp, azul, recebeu, true, true, true};
                            structInsert(newAction, actionVec);
                        }
                        newTimestamp = (*currentAction).timestamp + redArmy.getWaitTime();
                        newAction = {newTimestamp, vermelho, enviou, true, true, true};
                        structInsert(newAction, actionVec);
                    }
                    else 
                    {
                        endProgram = true;
                        cout << "O exército perdeu pois os mensageiros do exército Vermelho acabaram" << endl;
                    }
                }
                if ((*currentAction).army == azul)
                {
                    if (blueArmy.getMessengerCount() > 0)
                    {
                        blueArmy.sendMessenger();
                        messenger.setColor(azul);
                        messenger.setTravelTime();
                        messenger.setPossibleMessage();
                        messenger.castleCapture();
                        (*currentAction).alive = messenger.getStatus();
                        (*currentAction).possibleTime = messenger.getPossibleMessage();
                        time_t now = time(0) + (*currentAction).timestamp;
                        char* dt = ctime(&now);
                        string alive;
                        if ((*currentAction).alive)
                        {
                            alive = "vivo";
                        }
                        else 
                        {
                            alive = "morto";
                        }
                        cout << "O exército " << (*currentAction).army << " " << (*currentAction).type << " em " << dt << " um mensageiro " << alive << endl;
                        if (messenger.getStatus())
                        {
                            newTimestamp = (*currentAction).timestamp + messenger.getTravelTime();
                            newAction = {newTimestamp, vermelho, recebeu, messenger.getPossibleMessage(), true, true};
                            structInsert(newAction, actionVec);
                        }
                        else
                        {
                            newTimestamp = (*currentAction).timestamp + blueArmy.getWaitTime();
                            newAction = {newTimestamp, azul, enviou, true, true, true};
                            structInsert(newAction, actionVec);
                        }
                    }
                    else
                    {
                        endProgram = true;
                        cout << "O exército perdeu pois os mensageiros do exército Azul acabaram" << endl;
                    }
                }
            }
            if ((*currentAction).type == recebeu && (*currentAction).alive)
            {
                if ((*currentAction).army == vermelho)
                {
                    time_t now = time(0) + (*currentAction).timestamp;
                    char* dt = ctime(&now);
                    string alive;
                    if ((*currentAction).alive)
                    {
                        alive = "vivo";
                    }
                    else 
                    {
                        alive = "morto";
                    }
                    cout << "O exército " << (*currentAction).army << " " << (*currentAction).type << " em " << dt << " um mensageiro " << alive << endl;
                    if ((*currentAction).possibleTime)
                    {
                        redArmy.flareShot();
                        endProgram = true;
                        cout << "O exército ganhou" << endl;
                    }
                    else 
                    {
                        newTimestamp = (*currentAction).timestamp + 1;
                        newAction = {newTimestamp, vermelho, enviou, true, true, true};
                        structInsert(newAction, actionVec);
                        cout << "O exército vermelho vai reenviar um mensageiro pois o azul não podia no horário combinado" << endl;
                        for (int j = 29; j >= 0; j--)
                        {
                            if (actionVec[j].army == vermelho && actionVec[j].type == enviou)
                            {
                                actionVec[j].valid = false;
                                break;
                            }
                        }
                    }
                }
                if ((*currentAction).army == azul)
                {   
                    time_t now = time(0) + (*currentAction).timestamp;
                    char* dt = ctime(&now);
                    string alive;
                    if ((*currentAction).alive)
                    {
                        alive = "vivo";
                    }
                    else 
                    {
                        alive = "morto";
                    }
                    cout << "O exército " << (*currentAction).army << " " << (*currentAction).type << " em " << dt << " um mensageiro " << alive << endl;
                    newTimestamp = (*currentAction).timestamp + 1;
                    newAction = {newTimestamp, azul, enviou, true, true, true};
                    structInsert(newAction, actionVec);
                }
            }
        }
        i++;
    }

    return 0;
}