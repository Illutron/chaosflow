#include "visualizer.h"

void Visualizer::setup(Data * dataRef, Gui * guiRef, Simulator * simRef){
    data = dataRef;
    gui = guiRef;
    sim = simRef;
    
    maxLat = 55.7368;
    minLat = 55.6108;    
    maxLng = 12.6293;
    minLng = 12.4519;

}

void Visualizer::update(){
    
}

void Visualizer::debugDraw(){
    
}


void Visualizer::mousePressed(int x, int y, int button){
    
    for (int i=0; i<data->locations.size(); i++) {
        Location * loc = &data->locations[i];
        
        if (ofDist(x,y,loc->marker.x, loc->marker.y) < loc->markerRadius) {
            selectedLoc = loc;
        }
        
    }
    
}


void Visualizer::keyPressed(int key){
    if(key == 'P') {
        Path p;
        data->paths.push_back(p);
    }
    
    if(selectedLoc) {
        if(key == '1') {
            data->paths[0].addLocation(selectedLoc);
        }
    }
}

void Visualizer::drawMapPoint() {
    
}

void Visualizer::drawLocation(Location * loc) {
    
    if(loc->lat != 0 && loc->lng != 0) {
                
        float aOne = loc->dir_one.sampleAt(sim->elapsedFloat);
        float aTwo = loc->dir_two.sampleAt(sim->elapsedFloat);
        
        loc->marker = ofPoint(ofMap(loc->lng, minLng, maxLng, 200, 680), ofMap(loc->lat, minLat, maxLat, 680, 200));
        
        
        loc->markerRadius = ofMap(aOne+aTwo, 0, data->maxCombinedStatEntry, 2, 36);
        
        ofSetColor(ofMap(aOne, 0, data->maxStatEntry, 80, 255), 100, ofMap(aTwo, 0, data->maxStatEntry, 0, 255));
        ofCircle(loc->marker, loc->markerRadius);
        
    } 
}


void Visualizer::drawTimeline() {
    
}

void Visualizer::draw() {
    
    ofNoFill();    
    
    for (int i=0; i<data->locations.size(); i++) {        
        drawLocation(&data->locations[i]);
    }
    
    for (int i=0; i<data->paths.size(); i++) {
        drawPath(&data->paths[i]);
    }
    
    if (selectedLoc) {
        drawInterpolation(selectedLoc);
    }
    
}

void Visualizer::drawPath(Path * path) {
    
    string s;
    
    for(int i=0; i<path->locations.size(); i++) {
        s += path->locations[i]->road + " < -- > ";
    }
    
    ofDrawBitmapString(s, ofGetWidth()-800, 200);
    
    if(path->dir_one.size() > 0) {
        
        for(int i=0; i < path->dir_one.size(); i++) {
            ofDrawBitmapString(ofToString(path->dir_one.at(i)), (ofGetWidth()-300)+(i*(300/10)), ofGetHeight()-20);
        }
        
        for(int p=0; p < 300; p++) {
        
            float finto = p / float(300);
        
            //cout<<ofToString(finto)<<endl;
            float val = path->dir_one.sampleAt(finto);
        
            ofCircle(ofGetWidth()-300+p, ofMap(val, 0, data->maxStatEntry, ofGetHeight()-20, 20), 1);
        }
    }
}


void Visualizer::drawInterpolation(MSA::Interpolator1D * ipo, float width, float height, float max) {
    
}

void Visualizer::drawInterpolation(Location * loc) {
    
    int width = 700;
    int i;
    
    ofSetColor(100, 259, 60, 255);
    ofDrawBitmapString(loc->dir_one_label, 20, ofGetWindowHeight()-160);
    
    ofSetColor(250, 100, 60, 255);
    ofDrawBitmapString(loc->dir_two_label, 20, ofGetWindowHeight()-180);
    
    ofSetColor(255, 255, 255, 255);
    
    for(i=0; i < loc->dir_one.size(); i++) {
        ofDrawBitmapString(ofToString(loc->dir_one.at(i)), 10+(i*(width/10)), ofGetHeight()-20);
        
    }
    
    for(i=0; i < loc->dir_two.size(); i++) {
        
        ofDrawBitmapString(ofToString(loc->dir_two.at(i)), 10+(i*(width/10)), ofGetHeight()-50);
    }
    
    ofDrawBitmapString(loc->road, 20, ofGetHeight()-200);
        
    ofSetColor(100, 250, 60, 200);
    
    for(i=0; i < width; i++) {
        
        float finto = i / float(width);
        
        //cout<<ofToString(finto)<<endl;
        float val = loc->dir_one.sampleAt(finto);
        
        ofCircle(10+i, ofMap(val, 0, data->maxStatEntry, ofGetHeight()-20, 20), 1);
    }
    
    ofSetColor(250, 100, 60, 200);
    
    for(i=0; i < width; i++) {
        
        float finto = i / float(width);
        
        //cout<<ofToString(finto)<<endl;
        float val = loc->dir_two.sampleAt(finto);
        
        ofCircle(10+i, ofMap(val, 0, data->maxStatEntry, ofGetWindowHeight()-20, 20), 1);
    }
    
}