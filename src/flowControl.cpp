#include "flowControl.h"

void flowControl::setup(){
    // establish connection to arduino
    
    // for 1 in 3 arduinos
    // set up serial connection
    
    arduino[0].enumerateDevices();
    
    arduino[0].setup("/dev/tty.usbmodemfd1221", 9600);
    arduino[1].setup("/dev/tty.usbmodemfd1211", 9600);
    arduino[2].setup("/dev/tty.usbmodemfd1241", 9600);
    //arduino[2].setup(2, 9600);
    
    //arduino[0].setVerbose(true);
    
    for (int i = 0; i < NUM_CHANNELS; i++) {
        channels[i].i = i;
        channels[i].airCal = 0.8;
        channels[i].waterOpen = true;
        updateChannel(&channels[i]);
    }
    
    channels[0].airCal = 0.2; 
    
}

void flowControl::sendValue(char label, int value, ofSerial * ard) {
    bool valueWritten, labelWritten;
    
    valueWritten = ard->writeByte(value);
    
    if (valueWritten) {
        labelWritten = ard->writeByte(label);
    }
    
    //unsigned char myByte = 225;
    //ard->writeByte(4);
    //ard->writeByte('c');

    //unsigned char buf[10] = {'1', ';', '100', ';', '200', ';', '0', ';', '1', '\n'};
    //ard->writeBytes(&buf[0], 10);
        
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
    
    if(ofGetFrameNum() % 4) { // add something to update less often
        for (int i = 0; i < NUM_CHANNELS; i++) {
            updateChannel(&channels[i]);
        }
    }
}

void flowControl::debugDraw(){
    
}

void flowControl::injectAir(Channel * c, float duration) {
    openWaterValve(c);
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
    
    int ci;
    int ard = 0;
    
    if (c->i > 2) {
        ci = c->i - 3;
        ard = 1;
    } else if (c->i ) {
        ci = c->i - 6;
        ard = 2;
    }
    
    sendValue('c', ci, &arduino[ard]);    
    
    sendValue('p', ofMap(c->airPressure, 0, 1, 0, 160) * c->airCal, &arduino[ard]);
    //sendValue('s', ofMap(c->waterPressure, 0, 1, 0, 255), &arduino[ard]);
    sendValue('a', c->airOpen, &arduino[ard]);
    sendValue('w', true, &arduino[ard]); // hard coded ex
    
}
