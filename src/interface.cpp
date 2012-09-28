#include "interface.h"

void Interface::setup(Data * dataRef, Gui * guiRef, Simulator * simRef){
    data = dataRef;
    gui = guiRef;
    sim = simRef;
    
    maxLat = 55.7368;
    minLat = 55.6108;    
    maxLng = 12.6293;
    minLng = 12.4519;
    
    pad = 8;

}

void Interface::update(){
    
    // update locations for stuff that is clickable here ?
    
}

void Interface::draw() {
    
    ofFill(); 
    ofBackground(0, 0, 0);
    
    float w = ofGetWidth();
    float h = ofGetHeight();
            
    // draw settings area 
    ofSetColor(50);
    ofRect(0, 0, w*0.25, h*0.5);
    
    // draw path selector area
    ofSetColor(100);
    ofRect(w*0.25, 0, w*0.25, h*0.5);
    
    //drawPathList();
    
    // draw map 50% 0, 100%, 60%
    drawMap(w*0.5+pad, 0+pad, (w*0.5)-(2*pad), (h*0.5)-(2*pad));
    
    // draw detail inspection view / path editor 
    ofSetColor(120);
    ofRect(0, h*0.5, w*0.5, h*0.45);
    
    drawDetailInspector(0, h*0.5, w*0.5, h*0.45);
    
    
    // draw output view 
    ofSetColor(60);
    ofRect(w*0.5, h*0.5, w*0.5, h*0.45);
    
    // draw simulator control / timeline
    ofSetColor(40);
    ofRect(0, h*0.95, w, h*0.05);
    
    
    /*for (int i=0; i<data->paths.size(); i++) {
        drawPath(&data->paths[i]);
    }
    
    if (selectedPoint) {
        drawInterpolation(&selectedPoint->bikes, 20., 800., 700., 400.);
    }*/
    
}

void Interface::drawMap(float x, float y, float w,  float h) {
    
    ofSetColor(255);
    ofNoFill();
    
    for (int i=0; i<data->dataPoints.size(); i++) {        
        
        DataPoint * point = &data->dataPoints[i];
        
        if(point->loc->lat != 0 && point->loc->lng != 0) {
            
        
            float a = point->bikes.sampleAt(sim->elapsedFloat);
            
            point->marker = ofPoint(ofMap(point->loc->lat, minLat, maxLat, x, x+w), ofMap(point->loc->lng, minLng, maxLng, y, y+h));
                        
            point->markerRadius = ofMap(a, 0, data->maxStatEntry, 2, 8);
            
            ofCircle(point->marker, point->markerRadius);
            
        }
        
    }
}

void Interface::drawDetailInspector(float x, float y, float w, float h) {
    
    // add modes so this can either display selected point or selected path
    
    // draw point details
    if (selectedPoint) {
        
        
        drawInterpolation(&selectedPoint->bikes, x, y, w, h);
    }
    
}

void Interface::drawInterpolation(MSA::Interpolator1D * ipo, float x, float y, float w, float h) {
    
    for(int i=0; i < w; i++) {
        ofCircle(x+i, ofMap(ipo->sampleAt(i/w), 0, data->maxStatEntry, y+h, y), 1);
    }
    
}

void Interface::mousePressed(int x, int y, int button){
    for (int i=0; i<data->dataPoints.size(); i++) {
        DataPoint * point = &data->dataPoints[i];
        
        if (ofDist(x,y,point->marker.x, point->marker.y) < point->markerRadius) {
            selectedPoint = point;
        }
    }
}


void Interface::keyPressed(int key){
    if(key == 'P') {
        Path p;
        data->paths.push_back(p);
    }
    
    if(selectedPoint) {
        if(key == '1') {
            
            data->paths[0].addPoint(selectedPoint);
        }
    }
}


void Interface::drawPath(Path * path) {
    
    string s;
    
    for(int i=0; i<path->points.size(); i++) {
       s += path->points[i]->loc->name + " < -- > ";
    }
    
    ofDrawBitmapString(s, ofGetWidth()-800, 200);
    
    if(path->points.size() > 0) {
        
        for(int i=0; i < path->points.size(); i++) {
            ofDrawBitmapString(ofToString(path->sum.at(i)), (ofGetWidth()-300)+(i*(300/10)), ofGetHeight()-20);
        }
        
        for(int p=0; p < 300; p++) {
        
            float finto = p / float(300);
        
            //cout<<ofToString(finto)<<endl;
            float val = path->sum.sampleAt(finto);
        
            ofCircle(ofGetWidth()-300+p, ofMap(val, 0, data->maxStatEntry, ofGetHeight()-20, 20), 1);
        }
    }
}

void Interface::drawTimeline(float x, float y, float w, float h) {
    
 ofFill(); 
 ofSetColor(100, 100, 100);
 
 ofRect(x, y, w, h);
 ofSetColor(255, 255, 255);
 ofRect(x, y, ofMap(sim->simElapsedTime, 0, sim->simDuration, 0, w), h);
 
 ofDrawBitmapString("Simulator time: " + sim->formatTime(sim->simElapsedTime) + " / " + sim->formatTime(sim->simDuration), 10, 40);
 
 ofDrawBitmapString("Speed: " + ofToString(sim->speed), 10, 80);
 
 ofDrawBitmapString("Real time: " + sim->formatTime(sim->realElapsedTime) + " / " + sim->formatTime(sim->realDuration), 10, 60);
   
 
 
}

/*void Interface::drawInterpolation(DataPoint * point) {
    
    int width = 700;
    int i;
    
    
   
    
    ofSetColor(100, 259, 60, 255);
    ofDrawBitmapString(point->direction_name, 20, ofGetHeight()-160);
    
    ofSetColor(255, 255, 255, 255);
    
    for(i=0; i < DATA_HOURS; i++) {
        ofDrawBitmapString(ofToString(point->bikes.at(i)), 10+(i*(width/10)), ofGetHeight()-20);
        
    }
    
    ofDrawBitmapString(point->loc->name, 20, ofGetHeight()-200);
        
    ofSetColor(100, 250, 60, 200);
    
    for(i=0; i < width; i++) {
        
        float finto = i / float(width);
        
        //cout<<ofToString(finto)<<endl;
        float val = point->bikes.sampleAt(finto);
        
        ofCircle(10+i, ofMap(val, 0, data->maxStatEntry, ofGetHeight()-20, 20), 1);
    }
    
}*/