#ifndef ARMY_H
#define ARMY_H

class Army
{
    private:
        int color;
        int messengerCount;
        int waitTime;
        bool success = false;
    public:
        void setColor(int);
        void setMessengerCount(int);
        void setWaitTime(int);
        void setSuccess(bool);
        int getColor() const;
        int getMessengerCount() const;
        int getWaitTime() const;
        bool getSuccess() const;
        void sendMessenger();
        void flareShot();
};

#endif
