#include "../headers/army.h"
#include "../headers/messenger.h"
#include "../headers/functions.h"
#include <iostream>
using namespace std;
#include <string>

int main()
{
    Army redArmy;
    redArmy.setColor(1);
    redArmy.setMessengerCount(5);
    redArmy.setWaitTime(12601);
    Army blueArmy;
    blueArmy.setColor(2);
    blueArmy.setMessengerCount(10);
    blueArmy.setWaitTime(4201);
    struct action
    {
        int timestamp;
        int army;
        int type;
        bool possibleTime = true;
        bool valid = false;
    };
    action actionVec[20];

    //primeira ação
    redArmy.sendMessenger();
    Messenger redMessenger;
    redMessenger.setColor(1);
    redMessenger.setTravelTime();
    redMessenger.castleCapture();
    actionVec[0] = {0, 1, 1, true, true}; //segundo zero, exército vermelho, tipo enviar(1), valid = true
    if (redMessenger.getStatus() == true)
    {
        actionVec[1] = {redMessenger.getTravelTime(), 2, 2, true, true}; //tempo = 0+tempo de viagem, exército azul, tipo receber(2)
    }
    else 
    {
        actionVec[1] = {redArmy.getWaitTime(), 1, 1, true, true}; 
    }

    bool endProgram = false;
    while(endProgram != true)
    {
        int i;
        for (i = 19; i > 0; i--) //roda o vetor para encontrar o último termo válido
        {
            if (actionVec[i].valid == true)
            {
                if (actionVec[i].army == 2 && actionVec[i].type == 2) //exercito azul recebe mensageiro e envia o próximo
                {
                    if (blueArmy.getMessengerCount() > 0)
                    {
                        blueArmy.sendMessenger();
                        Messenger blueMessenger;
                        blueMessenger.setColor(2);
                        blueMessenger.setTravelTime();
                        blueMessenger.setPossibleMessage();
                        blueMessenger.castleCapture();
                        actionVec[i+1] = {actionVec[i].timestamp, 2, 1, blueMessenger.getPossibleMessage(), true};
                        if (blueMessenger.getStatus() == true)
                        {
                            actionVec[i+2] = {actionVec[i].timestamp + blueMessenger.getTravelTime(), 1, 2, blueMessenger.getPossibleMessage(), true};
                        }
                        else
                        {
                            actionVec[i+2] = {actionVec[i].timestamp + blueArmy.getWaitTime(), 2, 1, blueMessenger.getPossibleMessage(), true};
                        }
                    }
                    
                }
                if (actionVec[i].army == 1 && actionVec[i].type == 2) //exercito vermelho recebe mensageiro e dispara
                {
                    if (actionVec[i].possibleTime == true)
                    {
                        redArmy.flareShot();
                        cout << "vai caraio" << endl;
                    }
                }
                if (actionVec[i].army == 1 && actionVec[i].type == 1) //exercito vermelho reenvia mensageiro pois pode ter morrido
                {
                    if (redArmy.getMessengerCount() > 0)
                    {
                        redArmy.sendMessenger();
                        Messenger redMessenger;
                        redMessenger.setColor(1);
                        redMessenger.setTravelTime();
                        redMessenger.castleCapture();
                        if (redMessenger.getStatus() == true)
                        {
                            actionVec[i+1] = {actionVec[i].timestamp + redMessenger.getTravelTime(), 2, 2, true, true}; //tempo = 0+tempo de viagem, exército azul, tipo receber(2)
                        }
                        else 
                        {
                            if (redArmy.getMessengerCount() != 0)
                            {
                                actionVec[i+1] = {actionVec[i].timestamp + redArmy.getWaitTime(), 1, 1, true, true}; 
                            }
                        }
                    }
                    
                }
                if (actionVec[i].army == 2 && actionVec[i].type == 1) //exercito azul reenvia o mensageiro porque morreu
                {
                    if (blueArmy.getMessengerCount() > 0)
                    {
                        blueArmy.sendMessenger();
                        Messenger blueMessenger;
                        blueMessenger.setColor(2);
                        blueMessenger.setTravelTime();
                        blueMessenger.setPossibleMessage();
                        blueMessenger.castleCapture();
                        if (blueMessenger.getStatus() == true)
                        {
                            actionVec[i+1] = {actionVec[i].timestamp + blueMessenger.getTravelTime(), 1, 2, blueMessenger.getPossibleMessage(), true};
                        }
                        else
                        {
                            if (blueArmy.getMessengerCount() != 0)
                            {
                                actionVec[i+1] = {actionVec[i].timestamp + blueArmy.getWaitTime(), 2, 1, blueMessenger.getPossibleMessage(), true};
                            }
                        }

                    }
                }
                break;
            } 
        }
        if (redArmy.getSuccess() == true || redArmy.getMessengerCount() == 0 || blueArmy.getMessengerCount() == 0)
        {
            endProgram = true;
        }
    }
    for (int i = 0; i < 20; i++) 
    {
        if (actionVec[i].valid) 
        {
            cout << "timestamp: " << actionVec[i].timestamp << ", exercito: " << actionVec[i].army << ", tipo: " << actionVec[i].type << endl;
        }
    }
}