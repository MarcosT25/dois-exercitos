#ifndef MESSENGER_H
#define MESSENGER_H

class Messenger
{
    private:
        int color;
        bool status = true;
        int travelTime;
        bool possibleMessage;
    public:
        void setColor(int);
        void setStatus(bool);
        void setTravelTime();
        void setPossibleMessage();
        int getColor() const;
        bool getStatus() const;
        int getTravelTime() const;
        bool getPossibleMessage() const;
        void castleCapture();
};

#endif