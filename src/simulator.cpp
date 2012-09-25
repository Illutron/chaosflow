
#include "simulator.h"

void Simulator::setup(Data * dataRef, Gui * guiRef){

    data = dataRef;
    gui = guiRef;

    simDuration = DATA_HOURS * 3600000;
    simElapsedTime = 0;
    
    lastUpdateTime = 0;
    
    speed = 1200.;
    
    gui->playToggle = false;
}

void Simulator::update(){
    
    elapsedFloat = simElapsedTime / float(simDuration);
    
    if(gui->playToggle) {
        play();
    } else {
        pause();
    }
        
    speed = gui->simSpeed;
    
    if (playing) {
        
        int updateTime = ofGetElapsedTimeMillis();
        simElapsedTime = abs(simElapsedTime + (updateTime - lastUpdateTime) * speed);
        
        lastUpdateTime = updateTime;
        
        if (simElapsedTime >= simDuration) {
            simElapsedTime = simDuration;
            stop();
        }
    }
    
    realDuration = abs(simDuration/speed);
    realElapsedTime = abs(simElapsedTime/speed);
    
}

void Simulator::pause(){
    if (playing) {
        playing = false;
        gui->playToggle = false;
    }
}

void Simulator::stop(){
    playing = false;
    gui->playToggle = false;
    simElapsedTime = 0;
}

void Simulator::play(){
    if (!playing) {
        lastUpdateTime = ofGetElapsedTimeMillis();
        playing = true;
        gui->playToggle = true;
    }
}

void Simulator::debugDraw(){
    ofFill();
    
    ofSetColor(100, 100, 100);
    ofRect(10, 10, ofGetWindowWidth()-20, 10);
    ofSetColor(255, 255, 255);
    ofRect(10, 10, ofMap(simElapsedTime,0,simDuration,0,ofGetWindowWidth()-20), 10);
    
    ofDrawBitmapString("Simulator time: " + formatTime(simElapsedTime) + " / " + formatTime(simDuration), 10, 40);
    
    ofDrawBitmapString("Speed: " + ofToString(speed), 10, 80);
    
    ofDrawBitmapString("Real time: " + formatTime(realElapsedTime) + " / " + formatTime(realDuration), 10, 60);

    
}

string Simulator::formatTime(int millis) {
    string out;
    
    int h = millis / (1000*60*60);
    int m = (millis % (1000*60*60)) / (1000*60);
    int s = ((millis % (1000*60*60)) % (1000*60)) / 1000;
    
    if (h < 10) { out += "0"; }
    out += ofToString(h) + ":";
    
    if (m < 10) { out += "0"; }
    out += ofToString(m) + ":";
    
    if (s < 10) { out += "0"; }
    out += ofToString(s);
    
    return out;
}