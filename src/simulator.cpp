
#include "simulator.h"

void Simulator::setup(Data * dataRef, flowControl * flowRef){

    data = dataRef;
    flow = flowRef;

    simDuration = DATA_HOURS * 3600000;
    simElapsedTime = 0;
    
    lastUpdateTime = 0;
    
    speed = 20.;
    //gui->playToggle = false;
    
    
    stoPeriod = 100;
    
    baseBikeDuration = 100;
    
    for (int i = 0; i < NUM_CHANNELS; i++) {
        flow->channels[i].path = &data->paths[i];   
        
        flow->channels[i].path->hasBike = false;
        flow->channels[i].path->timeToNextBike = 600;
        flow->channels[i].path->singleBikeDuration = 100;
        flow->channels[i].path->lastBike = 0;
        
    }
    
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
    
    if(c->path) {
        
        c->path->trafficf = ofMap(c->path->sum.sampleAt(elapsedFloat), 0, maxPathSum, 0, 1);
        
        c->waterPressure = c->path->trafficf;
        c->airPressure = ofMap(c->path->trafficf, 0, 1, 0.2, 0.4);
        
        
        //hasBike;
        
        if (ofGetFrameNum() % 8 == 0) {
            c->path->timeToNextBike = ofMap(c->path->trafficf, 0, 1, 6000, 100) + ofMap(ofNoise(elapsedFloat), -1, 1, 2000, 0); 
            c->path->singleBikeDuration = ofMap(c->path->trafficf, 0, 1, 1000, 20) + ofMap(ofNoise(elapsedFloat), -1, 1, 200, 0);
        }
        
        if(c->path->hasBike) {
            if(ofGetElapsedTimeMillis() - c->path->lastBike > c->path->singleBikeDuration) {
                c->path->hasBike = false;
            }
        } else {
            if(ofGetElapsedTimeMillis() - c->path->lastBike > c->path->timeToNextBike) {
                c->path->hasBike = true;
                c->path->lastBike = ofGetElapsedTimeMillis();
            }
        }
        
        if(c->path->hasBike) {
            c->airOpen = true;
            c->waterOpen = false;
        } else {
            c->airOpen = false;
            c->waterOpen = true;
        }
        
        
        
        /* very simple rough working version
            if ( ofRandomf() < ofMap(c->path->sum.sampleAt(elapsedFloat), 0, maxPathSum, 0, 1) ) {
                if (c->waterOpen) {
                    c->waterOpen = false;
                    c->airOpen = true;
                } else {
                    c->waterOpen = true;
                    c->airOpen = false;
                }
            }
        */
        // add a kind of noise to the chance
    }
}   

void Simulator::simulatePaths() {    
    // add an if editing mode to improve performance
    maxPathSum = 0;
    for (int i = 0; i < NUM_CHANNELS; i++) {
        if(flow->channels[i].path) {
            if (flow->channels[i].path->sum_max > maxPathSum) {
                maxPathSum = flow->channels[i].path->sum_max;
            }
        }
    }
    
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