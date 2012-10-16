#include "flowControl.h"

void flowControl::setup(){
    // establish connection to arduino
    
    // for 1 in 3 arduinos
    // set up serial connection
    
    arduino[0].enumerateDevices();
    arduino[0].setup("/dev/cu.usbserial-A9007KHo", 9600);
    arduino[0].setVerbose(true);
    
    for (int i = 0; i < NUM_CHANNELS; i++) {
        channels[i].i = i;
    }
}

Channel* flowControl::getNextChannel(Channel * c) {
    if(c->i >= NUM_CHANNELS-1) {
        return &channels[0];
    } else {
        return &channels[c->i+1];
    }
}
Channel* flowControl::getPreviousChannel(Channel * c) {
    if(c->i <= 0) {
        return &channels[NUM_CHANNELS-1];
    } else {
        return &channels[c->i-1];
    }
}


void flowControl::update(){
    
    // period that increases probability of bikes
    
    if(ofGetFrameNum() % 4 == 0) {
        for (int i = 0; i < NUM_CHANNELS; i++) {
            updateChannel(&channels[i]);
        }
    }
}

void flowControl::debugDraw(){
    
}

void flowControl::injectAir(Channel * c, float duration) {
    openWaterValve(c);
    c->lock = true;
    // trigger close watervalve after duration time and set lock false;
}

void flowControl::openWaterValve(Channel * c) {
    c->waterOpen = true;
}

void flowControl::closeWaterValve(Channel * c) {
    c->waterOpen = false;
}

void flowControl::openAirValve(Channel * c) {
    c->airOpen = true;
}

void flowControl::closeAirValve(Channel * c) {
    c->airOpen = false;
}


void flowControl::updateChannel(Channel * c) {
    // data format is channel number int; air pressure float 0-1, water pressure float 0-1, air open bool, water open bool,
    
    //const char
    unsigned char buf[10] = {c->i, ';', c->airPressure, ';', c->waterPressure, ';', c->airOpen, ';', c->waterOpen, '\n'};
    arduino[c->arduinoNum].writeBytes(&buf[0], 10);

}
