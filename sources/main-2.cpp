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
        int army;
        int type;
        bool possibleTime = true;
        bool valid = false;
        bool read = false;
        bool alive = true;
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

void printTimestamp(action *actionVec)
{
    for (int i = 0; i < 30; i++)
    {
        if (actionVec[i].valid && actionVec[i].read) 
        {
            time_t now = time(0) + actionVec[i].timestamp;
            char* dt = ctime(&now);
            string army;
            string type;
            string alive;
            if (actionVec[i].army == 1)
            {
                army = "Vermelho";
            }
            else 
            {
                army = "Azul";
            }
            if (actionVec[i].type == 1)
            {
                type = "enviou";
            }
            else
            {
                type = "recebeu";
            }
            if (actionVec[i].alive)
            {
                alive = "vivo";
            }
            else 
            {
                alive = "morto";
            }
            
            cout << "Em " << dt << " o exército " << army << " " << type << " um mensageiro " << alive << endl;
        }
    }
}

int main()
{
    srand(time(NULL));
    Army redArmy;
    redArmy.setColor(1);
    redArmy.setMessengerCount(5);
    redArmy.setWaitTime(12601);
    Army blueArmy;
    blueArmy.setColor(2);
    blueArmy.setMessengerCount(10);
    blueArmy.setWaitTime(4201);
    
    action actionVec[30];
    int actualTimestamp;
    int newTimestamp;
    action newAction;

    //primeira ação
    redArmy.sendMessenger();
    Messenger redMessenger;
    redMessenger.setColor(1);
    redMessenger.setTravelTime();
    redMessenger.castleCapture();
    actionVec[0] = {0, 1, 1, true, true, true, redMessenger.getStatus()}; //segundo zero, exército vermelho, tipo enviar(1), valid = true
    cout << "nova contagem vermelho: " << redArmy.getMessengerCount() << endl;
    cout << "o mensageiro que saiu agora sobreviveu?" << redMessenger.getStatus() << endl;
    actionVec[1] = {redArmy.getWaitTime(), 1, 1, true, true, false, true};

    if (redMessenger.getStatus())
    {
        newAction = {redMessenger.getTravelTime(), 2, 2, true, true, false, true};
        structInsert(newAction, actionVec);
    }

    bool endProgram = false;
    while (!endProgram)
    {
        for (int i = 29; i >= 0; i--)
        {
            if (actionVec[i].valid && actionVec[i].read)
            {
                if (actionVec[i+1].army == 2 && actionVec[i+1].type == 2 && actionVec[i+1].read ==  false && actionVec[i+1].alive) //azul recebe
                {
                    actionVec[i+1].read = true; //marca o ultimo como lido
                    actualTimestamp = actionVec[i+1].timestamp;
                    if (blueArmy.getMessengerCount() > 0)
                    {
                        blueArmy.sendMessenger();
                        cout << "nova contagem azul: " << blueArmy.getMessengerCount() << endl;
                        Messenger blueMessenger; //azul envia
                        blueMessenger.setColor(2);
                        blueMessenger.setTravelTime();
                        blueMessenger.setPossibleMessage();
                        blueMessenger.castleCapture();
                        cout << "o mensageiro que saiu agora sobreviveu?" << blueMessenger.getStatus() << endl;
                        newTimestamp = actualTimestamp + 1;
                        newAction = {newTimestamp, 2, 1, blueMessenger.getPossibleMessage(), true, true, blueMessenger.getStatus()}; 
                        structInsert(newAction, actionVec);
                        if (blueMessenger.getStatus()) 
                        {
                            newTimestamp = actualTimestamp + blueMessenger.getTravelTime();
                            newAction = {newTimestamp, 1, 2, blueMessenger.getPossibleMessage(), true, false, true}; 
                            structInsert(newAction, actionVec);
                        }
                        else 
                        {
                            newTimestamp = actualTimestamp + blueArmy.getWaitTime();
                            newAction = {newTimestamp, 2, 1, true, true, false, true};
                            structInsert(newAction, actionVec);
                        }
                    }
                    else 
                    {
                        endProgram = true;
                    }
                }
                if (actionVec[i+1].army == 1 && actionVec[i+1].type == 2 && actionVec[i+1].read ==  false && actionVec[i+1].alive) //vermelho recebe e acaba
                {
                    actionVec[i+1].read = true;
                    if (actionVec[i+1].possibleTime)
                    {
                        redArmy.flareShot();
                        cout << "vai caraio" << endl;
                    }
                }
                if (actionVec[i+1].army == 1 && actionVec[i+1].type == 1 && actionVec[i+1].read ==  false) //vermelho reenvia pq deu o tempo
                {
                    actionVec[i+1].read = true;
                    actualTimestamp = actionVec[i+1].timestamp;
                    if (redArmy.getMessengerCount() > 0)
                    {
                        redArmy.sendMessenger();
                        cout << "nova contagem vermelho: " << redArmy.getMessengerCount() << endl;
                        Messenger redMessenger;
                        redMessenger.setColor(1);
                        redMessenger.setTravelTime();
                        redMessenger.castleCapture();
                        cout << "o mensageiro que saiu agora sobreviveu?" << redMessenger.getStatus() << endl;
                        newTimestamp = actualTimestamp + redArmy.getWaitTime();
                        newAction = {newTimestamp, 1, 1, true, true, false, true};
                        structInsert(newAction, actionVec);
                        if (redMessenger.getStatus())
                        {
                            newTimestamp = actualTimestamp + redMessenger.getTravelTime();
                            newAction = {newTimestamp, 2, 2, true, true, false, true};
                            structInsert(newAction, actionVec);
                        }
                    }
                    else 
                    {
                        endProgram = true;
                    }
                }
                if(actionVec[i+1].army == 2 && actionVec[i+1].type == 1 && actionVec[i+1].read ==  false) //azul reenvia pq deu o tempo
                {
                    actionVec[i+1].read = true; //marca o ultimo como lido
                    actualTimestamp = actionVec[i+1].timestamp;
                    if (blueArmy.getMessengerCount() > 0)
                    {
                        blueArmy.sendMessenger();
                        cout << "nova contagem azul: " << blueArmy.getMessengerCount() << endl;
                        Messenger blueMessenger; //azul envia
                        blueMessenger.setColor(2);
                        blueMessenger.setTravelTime();
                        blueMessenger.setPossibleMessage();
                        blueMessenger.castleCapture();
                        cout << "o mensageiro que saiu agora sobreviveu?" << blueMessenger.getStatus() << endl;                                    
                        if (blueMessenger.getStatus()) 
                        {
                            newTimestamp = actualTimestamp + blueMessenger.getTravelTime();
                            newAction = {newTimestamp, 1, 2, blueMessenger.getPossibleMessage(), true, false, true}; 
                            structInsert(newAction, actionVec);
                        }
                        else 
                        {
                            newTimestamp = actualTimestamp + blueArmy.getWaitTime();
                            newAction = {newTimestamp, 2, 1, true, true, false, true};
                            structInsert(newAction, actionVec);
                        }
                    }
                    else 
                    {
                        endProgram = true;
                    }
                }
            }
        }
        if (redArmy.getSuccess())
        {
            endProgram = true;
        }
    }

    printTimestamp(actionVec);
 
}