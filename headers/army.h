#ifndef ARMY_H
#define ARMY_H

class Army
{
    private:
        char *color;
        int messengerCount;
        int waitTime;
        bool success = false;
    public:
        void setColor(char*);
        void setMessengerCount(int);
        void setWaitTime(int);
        void setSuccess(bool);
        char *getColor();
        int getMessengerCount() const;
        int getWaitTime() const;
        bool getSuccess() const;
        void sendMessenger();
        void flareShot();
};

#endif
