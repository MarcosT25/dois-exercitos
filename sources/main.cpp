#include "../headers/army.h"
#include "../headers/messenger.h"
#include "../headers/functions.h"
#include <iostream>
using namespace std;
#include <string>
#include <ctime>
#include <algorithm>

struct action
    {
        int timestamp;
        char *army;
        char *type;
        bool possibleTime = true;
        bool alive = true;
        bool valid = false; //campo valid serve para filtrar structs com lixo de memória no vetor
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
    Army redArmy; //instancia o exército vermelho
    char vermelho[9] = "Vermelho";
    redArmy.setColor(vermelho);
    redArmy.setMessengerCount(5);
    redArmy.setWaitTime(12601);
    Army blueArmy; //instancia o exército azul
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
    string start = "0";
    string end = "0";
    while (!endProgram)
    {
        currentAction = &actionVec[i];
        if ((*currentAction).valid) //confere se não é lixo de memória
        {
            if ((*currentAction).type == enviou)
            {
                Messenger messenger;
                if ((*currentAction).army == vermelho) //exercito vermelho enviando um mensageiro
                {
                    if(redArmy.getMessengerCount() > 0)
                    {
                        redArmy.sendMessenger();
                        messenger.setColor(vermelho); 
                        messenger.setTravelTime();
                        messenger.castleCapture();
                        (*currentAction).alive = messenger.getStatus();
                        time_t now = time(0) + (*currentAction).timestamp;
                        char* dt = ctime(&now); //por padrão a função ctime adiciona um \n
                        string newTime = dt; //retiraremos o \n passando dt para uma string e utilizando a função abaixo
                        newTime.erase(remove(newTime.begin(), newTime.end(), '\n'), newTime.end());
                        if (start == "0")
                        {
                            start = newTime;
                        }
                        string alive;
                        if ((*currentAction).alive)
                        {
                            alive = "Durante o trajeto, o mensageiro sobreviveu.";
                        }
                        else 
                        {
                            alive = "Durante o trajeto, o mensageiro morreu.";
                        }
                        cout << "O exército " << (*currentAction).army << " " << (*currentAction).type << " em " << newTime  << " um mensageiro. " << alive << endl;
                        if (messenger.getStatus()) //caso o mensageiro sobreviva, o exército azul irá recebe-lo
                        {                            
                            newTimestamp = (*currentAction).timestamp + messenger.getTravelTime();
                            newAction = {newTimestamp, azul, recebeu, true, true, true};
                            structInsert(newAction, actionVec);
                        }
                        newTimestamp = (*currentAction).timestamp + redArmy.getWaitTime(); //insere no vetor o tempo que o vermelho aguarda uma resposta para reenviar um mensageiro
                        newAction = {newTimestamp, vermelho, enviou, true, true, true};
                        structInsert(newAction, actionVec);
                    }
                    else 
                    {
                        endProgram = true;
                        cout << "O exército perdeu pois os mensageiros do exército Vermelho acabaram." << endl;
                        time_t now = time(0) + (*currentAction).timestamp;
                        char* dt = ctime(&now);
                        string newTime = dt;
                        newTime.erase(remove(newTime.begin(), newTime.end(), '\n'), newTime.end());
                        end = newTime;
                    }
                }
                if ((*currentAction).army == azul) //exercito azul enviando um mensageiro
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
                        string newTime = dt;
                        newTime.erase(remove(newTime.begin(), newTime.end(), '\n'), newTime.end());
                        string alive;
                        if ((*currentAction).alive)
                        {
                            alive = "Durante o trajeto, o mensageiro sobreviveu.";
                        }
                        else 
                        {
                            alive = "Durante o trajeto, o mensageiro morreu.";
                        }
                        cout << "O exército " << (*currentAction).army << " " << (*currentAction).type << " em " << newTime  << " um mensageiro. " << alive << endl;
                        if (messenger.getStatus()) //caso o mensageiro sobreviva, o exército vermelho irá recebe-lo
                        {
                            newTimestamp = (*currentAction).timestamp + messenger.getTravelTime();
                            newAction = {newTimestamp, vermelho, recebeu, messenger.getPossibleMessage(), true, true};
                            structInsert(newAction, actionVec);
                        }
                        else //caso o mensageiro morra, o exército azul irá reenvia-lo
                        {
                            newTimestamp = (*currentAction).timestamp + blueArmy.getWaitTime();
                            newAction = {newTimestamp, azul, enviou, true, true, true};
                            structInsert(newAction, actionVec);
                        }
                    }
                    else
                    {
                        endProgram = true;
                        cout << "O exército perdeu pois os mensageiros do exército Azul acabaram." << endl;
                        time_t now = time(0) + (*currentAction).timestamp;
                        char* dt = ctime(&now);
                        string newTime = dt;
                        newTime.erase(remove(newTime.begin(), newTime.end(), '\n'), newTime.end());
                        end = newTime;
                        for (int j = 29; j >= 0; j--) //exclui o horário que o vermelho enviaria o último mensageiro
                        {
                            if (actionVec[j].army == vermelho && actionVec[j].type == enviou)
                            {
                                actionVec[j].valid = false;
                                break;
                            }
                        }
                    }
                }
            }
            if ((*currentAction).type == recebeu && (*currentAction).alive) //o exercito recebendo um mensageiro vivo
            {
                if ((*currentAction).army == vermelho)
                {
                    time_t now = time(0) + (*currentAction).timestamp;
                    char* dt = ctime(&now);
                    string newTime = dt;
                    newTime.erase(remove(newTime.begin(), newTime.end(), '\n'), newTime.end());
                    string alive;
                    if ((*currentAction).alive)
                    {
                        alive = "vivo.";
                    }
                    else 
                    {
                        alive = "morto.";
                    }
                    cout << "O exército " << (*currentAction).army << " " << (*currentAction).type << " em " << newTime << " um mensageiro " << alive << endl;
                    if ((*currentAction).possibleTime)
                    {
                        redArmy.flareShot();
                        endProgram = true;
                        cout << "O exército Azul confirmou o horário e o exército Vermelho disparou o sinalizador. O exército ganhou." << endl;
                        end = newTime;
                        for (int j = 29; j >= 0; j--) //exclui o horário que o vermelho enviaria o último mensageiro
                        {
                            if (actionVec[j].army == vermelho && actionVec[j].type == enviou)
                            {
                                actionVec[j].valid = false;
                                break;
                            }
                        }
                    }
                    else 
                    {
                        newTimestamp = (*currentAction).timestamp + 1;
                        newAction = {newTimestamp, vermelho, enviou, true, true, true};
                        structInsert(newAction, actionVec);
                        cout << "O exército Vermelho disparou o sinalizador confirmando que recebeu o mensageiro." << endl;
                        cout << "O exército Vermelho vai reenviar um mensageiro pois o Azul não podia no horário combinado." << endl;
                        for (int j = 29; j >= 0; j--) //exclui o horário que o vermelho enviaria o último mensageiro
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
                    string newTime = dt;
                    newTime.erase(remove(newTime.begin(), newTime.end(), '\n'), newTime.end());
                    string alive;
                    if ((*currentAction).alive)
                    {
                        alive = "vivo.";
                    }
                    else 
                    {
                        alive = "morto.";
                    }
                    cout << "O exército " << (*currentAction).army << " " << (*currentAction).type << " em " << newTime << " um mensageiro " << alive << endl;
                    newTimestamp = (*currentAction).timestamp + 1;
                    newAction = {newTimestamp, azul, enviou, true, true, true};
                    structInsert(newAction, actionVec);
                }
            }
        }
        i++;
    }
    
    cout << "O início da troca de mensagens foi em " << start << ". O fim da troca de mensagens foi em " << end << "." << endl;
    for (int i = 29; i >= 0; i--) 
    {
        if (actionVec[i].valid)
        {
            int hour = (actionVec[i].timestamp - actionVec[0].timestamp) / 3600;
            int minutes = ((actionVec[i].timestamp - actionVec[0].timestamp) % 3600) / 60;
            int seconds = (actionVec[i].timestamp - actionVec[0].timestamp) - (3600 * hour) - (60 * minutes);
            cout << "O tempo total entre a troca de mensagens foi de " << hour << " horas, " << minutes << " minutos e " << seconds << " segundos." << endl;
            break;
        }
    }
    cout << "O exército Vermelho utilizou " << 5 - redArmy.getMessengerCount() << " mensageiros." << endl;
    cout << "O exército Azul utilizou " << 10 - blueArmy.getMessengerCount() << " mensageiros." << endl;

    return 0;
}