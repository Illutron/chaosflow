
#include "simulator.h"

void Simulator::setup(Data * dataRef, Gui * guiRef){
    
    data = dataRef;
    gui = guiRef;
    
    //simStartOffset = 7 * 3600000;
    
    simDuration = 10 * 3600000;
    simElapsedTime = 0;
    
    lastUpdateTime = 0;
    
    speed = 1200.;
    playing = false;
    
    gui->ui->addSlider("Speed",-400,400,&speed,304,16);
    
    //gui->ui->addS
    
}

void Simulator::update(){
    
    if (playing) {
        int updateTime = ofGetElapsedTimeMillis();
    
        simElapsedTime += (updateTime - lastUpdateTime) * speed;
    
        lastUpdateTime = updateTime;
        
        if (simElapsedTime > simDuration) {
            simElapsedTime = simDuration;
            stop();
        }
    }
}

void Simulator::stop(){
    playing = false;
}

void Simulator::start(){
    lastUpdateTime = ofGetElapsedTimeMillis();
    playing = true;
}

void Simulator::debugDraw(){
    ofFill();
    
    ofSetColor(100, 100, 100);
    ofRect(10, 10, ofGetWindowWidth()-20, 10);
    ofSetColor(255, 255, 255);
    ofRect(10, 10, ofMap(simElapsedTime,0,simDuration,0,ofGetWindowWidth()-20), 10);
    
    ofDrawBitmapString("Simulator time: " + formatTime(simElapsedTime) + " / " + formatTime(simDuration), 10, 40);
    
    ofDrawBitmapString("Speed: " + ofToString(speed), 10, 80);
    
    
    int realDuration = simDuration/speed;
    int realElapsedTime = simElapsedTime/speed;
    
    
    ofDrawBitmapString("Real time: " + formatTime(realElapsedTime) + " / " + formatTime(realDuration), 10, 60);
    
    drawInterpolation();
    
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


void Simulator::drawInterpolation() {
    //data->locations[10].entries
    
    // my own jaggy linear interpolation example for debug
    // maybe try and use msainterpolate for the end result
    
    int width = 700;
    int locnum = 43;
    int i;
    
    
    ofSetColor(255, 255, 255, 255);
    
    ofSetColor(100, 259, 60, 255);
    ofDrawBitmapString(data->locations[locnum].dir_one_label, 20, ofGetWindowHeight()-160);
    
    ofSetColor(250, 100, 60, 255);
    ofDrawBitmapString(data->locations[locnum].dir_two_label, 20, ofGetWindowHeight()-180);
    
    ofSetColor(255, 255, 255, 255);

    
    for(i=0; i < data->locations[locnum].dir_one.size(); i++) {
        ofDrawBitmapString(ofToString(data->locations[locnum].dir_one.at(i)), 10+(i*(width/10)), ofGetWindowHeight()-20);
        
    }
    
    for(i=0; i < data->locations[locnum].dir_two.size(); i++) {
                
        ofDrawBitmapString(ofToString(data->locations[locnum].dir_two.at(i)), 10+(i*(width/10)), ofGetWindowHeight()-50);
        
        
    }
    
    ofDrawBitmapString(data->locations[locnum].road, 20, ofGetWindowHeight()-200);
    
    //ofPath()
    
    ofSetColor(100, 250, 60, 200);

    for(i=0; i < width; i++) {
        
        float finto = i / float(width);
        
        //cout<<ofToString(finto)<<endl;
        float val = data->locations[locnum].dir_one.sampleAt(finto);
        
        ofCircle(10+i, ofMap(val, 0, 3500, ofGetWindowHeight()-20, 20), 1);
    }
    
    ofSetColor(250, 100, 60, 200);

    for(i=0; i < width; i++) {
        
        float finto = i / float(width);
        
        //cout<<ofToString(finto)<<endl;
        float val = data->locations[locnum].dir_two.sampleAt(finto);
        
        ofCircle(10+i, ofMap(val, 0, 3500, ofGetWindowHeight()-20, 20), 1);
    }
    
    
    
    /*ofSetColor(160, 160, 160, 200);
    for(i=1; i < width+1; i++) {
        
        int hour = i / (width/10);
        
        int amount_one = data->locations[locnum].dir_one[hour].amount;        
        int amount_two = data->locations[locnum].dir_one[hour+1].amount;        
        
        //int hour
        
        float finto = i % (width/10) / (width/10.0);
        
        //cout<<ofToString(i) + " pixels in. " + ofToString(finto) + " in section "<<endl;
        
        //cout<<"Getting hour " + ofToString(hour) + " and "+ ofToString(hour+1)<<endl;
        
        //ofSleepMillis(10);
        
        float height = (finto * amount_two) + ((1.0-finto) * amount_one);
        
        //cout<<"Amounts are " + ofToString(amount_one) + " and " + ofToString(amount_two)<<endl;
        //cout<<"Result is " + ofToString(height)<<endl;
        
        ofCircle(10+i, ofGetWindowHeight()-height, 1);
        
    }*/
    
    //myInterpolator1D.clear();
    //myInterpolator1D_two.clear();
    
    //ofSleepMillis(3600);
}
