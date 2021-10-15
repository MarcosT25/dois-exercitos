#ifndef MESSENGER_H
#define MESSENGER_H

class Messenger
{
    private:
        char *color;
        bool alive = true;
        int travelTime;
        bool possibleMessage;
    public:
        void setColor(char*);
        void setStatus(bool);
        void setTravelTime();
        void setPossibleMessage();
        char *getColor();
        bool getStatus() const;
        int getTravelTime() const;
        bool getPossibleMessage() const;
        void castleCapture();
};

#endif