#include "../headers/army.h"
#include "../headers/messenger.h"
#include "../headers/functions.h"
#include <iostream>
using namespace std;
#include <string>

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
    struct action
    {
        int timestamp;
        int army;
        int type;
        bool possibleTime = true;
        bool valid = false;
    };
    action actionVec[5][5];

    //primeira ação
    redArmy.sendMessenger();
    Messenger redMessenger;
    redMessenger.setColor(1);
    redMessenger.setTravelTime();
    redMessenger.castleCapture();
    actionVec[0][0] = {0, 1, 1, true, true}; //segundo zero, exército vermelho, tipo enviar(1), valid = true
    if (redMessenger.getStatus() == true)
    {
        actionVec[0][1] = {redMessenger.getTravelTime(), 2, 2, true, true}; //tempo = 0+tempo de viagem, exército azul, tipo receber(2)
        actionVec[1][0] = {redArmy.getWaitTime(), 1, 1, true, true}; 
    }
    else 
    {
        actionVec[1][0] = {redArmy.getWaitTime(), 1, 1, true, true}; 
    }

    bool endProgram = false;
    while(endProgram != true)
    {
        int j = 0;
        bool nextLine = true;
        while(nextLine) //roda cada linha da matriz
        {
            for (int i = 4; i > 0; i--) //roda coluna da matriz para encontrar o último termo válido
            {
                if (actionVec[j][i].valid == true)
                {
                    if (actionVec[j][i].army == 2 && actionVec[j][i].type == 2) //exercito azul recebe mensageiro e envia o próximo
                    {
                        if (blueArmy.getMessengerCount() > 0)
                        {
                            blueArmy.sendMessenger();
                            Messenger blueMessenger;
                            blueMessenger.setColor(2);
                            blueMessenger.setTravelTime();
                            blueMessenger.setPossibleMessage();
                            blueMessenger.castleCapture();
                            actionVec[j][i+1] = {actionVec[j][i].timestamp, 2, 1, blueMessenger.getPossibleMessage(), true};
                            if (blueMessenger.getStatus() == true)
                            {
                                actionVec[j][i+2] = {actionVec[j][i].timestamp + blueMessenger.getTravelTime(), 1, 2, blueMessenger.getPossibleMessage(), true};
                            }
                            else
                            {
                                actionVec[j][i+2] = {actionVec[j][i].timestamp + blueArmy.getWaitTime(), 2, 1, blueMessenger.getPossibleMessage(), true};
                            }
                        }
                        else 
                        {
                            nextLine = false;
                            cout << "acabou neguinho do azul" << endl;
                        }
                    }
                    if (actionVec[j][i].army == 1 && actionVec[j][i].type == 2) //exercito vermelho recebe mensageiro e dispara
                    {
                        if (actionVec[j][i].possibleTime == true)
                        {
                            redArmy.flareShot();
                            nextLine = false;
                            cout << "vai caraio" << endl;
                        }
                    }
                    if (actionVec[j][i].army == 1 && actionVec[j][i].type == 1) //exercito vermelho reenvia mensageiro pois pode ter morrido
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
                                actionVec[j+1][0] = {actionVec[j][i].timestamp + redArmy.getWaitTime(), 1, 1, true, true};
                                actionVec[j+1][1] = {actionVec[j+1][0].timestamp + redMessenger.getTravelTime(), 2, 2, true, true}; //tempo = 0+tempo de viagem, exército azul, tipo receber(2)
                            }
                            else 
                            {
                                if (redArmy.getMessengerCount() != 0)
                                {
                                    actionVec[j+1][0] = {actionVec[j][i].timestamp + redArmy.getWaitTime(), 1, 1, true, true}; 
                                }
                            }
                        }
                        else 
                        {
                            nextLine = false;
                            cout << "acabou neguinho do vermelho" << endl;
                        }
                    }
                    if (actionVec[j][i].army == 2 && actionVec[j][i].type == 1) //exercito azul reenvia o mensageiro porque morreu
                    {
                        if (blueArmy.getMessengerCount() > 0)
                        {
                            if (actionVec[j][i].timestamp < actionVec[j+1][0].timestamp)
                            {
                                blueArmy.sendMessenger();
                                Messenger blueMessenger;
                                blueMessenger.setColor(2);
                                blueMessenger.setTravelTime();
                                blueMessenger.setPossibleMessage();
                                blueMessenger.castleCapture();
                                if (blueMessenger.getStatus() == true)
                                {
                                    actionVec[j][i+1] = {actionVec[j][i].timestamp + blueMessenger.getTravelTime(), 1, 2, blueMessenger.getPossibleMessage(), true};
                                }
                                else
                                {
                                    if (blueArmy.getMessengerCount() != 0)
                                    {
                                        actionVec[j][i+1] = {actionVec[j][i].timestamp + blueArmy.getWaitTime(), 2, 1, blueMessenger.getPossibleMessage(), true};
                                    }
                                }
                            }
                            else 
                            {
                                j++;
                            }
                        }
                        else 
                        {
                            nextLine = false;
                            cout << "acabou neguinho do azul" << endl;
                        }
                    }
                    break;
                } 
            }
        }
        
        if (redArmy.getSuccess() == true || redArmy.getMessengerCount() == 0 || blueArmy.getMessengerCount() == 0)
        {
            endProgram = true;
        }
    }
    for (int i = 0; i < 5; i++) 
    {
        for (int j = 0; j < 5; j++)
        {
            if (actionVec[i][j].valid) 
            {
                cout << "timestamp: " << actionVec[i][j].timestamp << ", exercito: " << actionVec[i][j].army << ", tipo: " << actionVec[i][j].type << endl;
            }
        }
    }
}