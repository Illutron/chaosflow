
#include "simulator.h"

void Simulator::setup(Data * dataRef, flowControl * flowRef){

    data = dataRef;
    flow = flowRef;

    simDuration = DATA_HOURS * 3600000;
    simElapsedTime = 0;
    
    lastUpdateTime = 0;
    
    speed = 2.;
    //gui->playToggle = false;
}

void Simulator::update(){
    
    // send out osc messages
    // elapsed float 
    // each channels data
    // speed
    
    
    elapsedFloat = simElapsedTime / float(simDuration);
        
    //speed = gui->simSpeed;
    
    if (playing) {
        
        int updateTime = ofGetElapsedTimeMillis();
        simElapsedTime = abs(simElapsedTime + (updateTime - lastUpdateTime) * speed);
        
        lastUpdateTime = updateTime;
        
        if (simElapsedTime >= simDuration) {
            simElapsedTime = simDuration;
            stop();
        }
        
        simulatePaths();
        
    } else {
        pause();
    }
    
    realDuration = abs(simDuration/speed);
    realElapsedTime = abs(simElapsedTime/speed);
    
}

void Simulator::simulatePath(Channel * c) {
    //c->path->sum_max;
    //c->path->sum.at(elapsedFloat);
    
}   

void Simulator::simulatePaths() {
    
    for (int i = 0; i < NUM_CHANNELS; i++) {
        simulatePath(&flow->channels[i]);
    }
    
    
}

void Simulator::pause(){
    if (playing) {
        playing = false;
        //gui->playToggle = false;
    }
}

void Simulator::stop(){
    playing = false;
    //gui->playToggle = false;
    simElapsedTime = 0;
}

void Simulator::play(){
    if (!playing) {
        lastUpdateTime = ofGetElapsedTimeMillis();
        playing = true;
        //gui->playToggle = true;
    }
}

void Simulator::debugDraw(){
    
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