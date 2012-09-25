#pragma once

#include "ofMain.h"
#include "defines.h"

struct Channel {
public:
    int address; // serial address
    
    float airPressure;
    float waterPressure;
    
    bool airOpen;
    bool waterOpen;
    
    bool lock; // when lock true the channel does not accept new valve commands
    // maybe do a vector of waiting commands
};

class flowControl {
public:
	void setup();
	void update();
	void debugDraw();
    
    Channel channels [NUM_CHANNELS];
    
    void injectAir(Channel * c, float duration);
    //void injectAir(Channel * c, float duration, float pressure);
    
    void openAirValve(Channel * c);
    void closeAirValve(Channel * c);
    void setAirPressure(Channel * c, float pressure);
    
    void openWaterValve(Channel * c);
    void closeWaterValve(Channel * c);
    void setWaterPressure(Channel * c, float pressure);
    
    
};