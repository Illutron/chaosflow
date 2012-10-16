#pragma once

#include "ofMain.h"
#include "data.h"
#include "defines.h"

struct Channel {
public:
    int i;
    
    int arduinoNum;
    // consider having pins losted here if arduinos are not wired similarily
    
    float airPressure;
    float waterPressure;
    
    long airOpenSince;
    long waterOpenSince;  
    
    bool airOpen;
    bool waterOpen;
    
    bool lock; // when lock true the channel does not accept new valve commands
    // maybe do a vector of waiting commands
    
    Path * path;
};

class flowControl {
public:
	void setup();
	void update();
	void debugDraw();
    
    Channel channels [NUM_CHANNELS];
    
    Channel * getNextChannel(Channel * c);
    Channel * getPreviousChannel(Channel * c);
    
    void injectAir(Channel * c, float duration);
    //void injectAir(Channel * c, float duration, float pressure);
    
    void openAirValve(Channel * c);
    void closeAirValve(Channel * c);
    void setAirPressure(Channel * c, float pressure);
    
    void openWaterValve(Channel * c);
    void closeWaterValve(Channel * c);
    void setWaterPressure(Channel * c, float pressure);
    
    void updateChannel(Channel * c);
    
    void sendValue(char label, int value, ofSerial * ard);
    
    ofSerial arduino [3];
};