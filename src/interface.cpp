#include "interface.h"

void Interface::setup(Data * dataRef, Gui * guiRef, Simulator * simRef, flowControl * flowRef){
    data = dataRef;
    gui = guiRef;
    sim = simRef;
    flow = flowRef;
    
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
    //ofSetColor(50);
    //ofRect(0, 0, w*0.25, h*0.5);
    
    // draw path selector area
    //ofSetColor(100);
    //ofRect(w*0.25, 0, w*0.25, h*0.5);
    
    //drawPathList();
    
    // draw map 50% 0, 100%, 60%
    drawMap(w*0.5+pad, 0+pad, (w*0.5)-(2*pad), (h*0.5)-(2*pad));
    
    // draw detail inspection view / path editor 
    drawDetailInspector(0, h*0.5, w*0.5, h*0.45);
    
    
    // draw output view 
    //ofSetColor(60);
    //ofRect(w*0.5, h*0.5, w*0.5, h*0.45);
    drawOutput(w*0.5, h*0.5, w*0.5, h*0.45);
    
    // draw simulator control / timeline
    //ofSetColor(40);
    //ofRect(0, h*0.95, w, h*0.05);
    drawTimeline(0, h*0.95, w, h*0.05);
    
    /*for (int i=0; i<data->paths.size(); i++) {
        drawPath(&data->paths[i]);
    }
    
    if (selectedPoint) {
        drawInterpolation(&selectedPoint->bikes, 20., 800., 700., 400.);
    }*/
    
}


void Interface::drawOutput(float x, float y, float w, float h) {
    ofPushMatrix();
    ofTranslate(x, y);
    
    float cw = w/NUM_CHANNELS;
    
    for(int i=0; i < NUM_CHANNELS; i++) {
        
        //ofPushMatrix();
        //ofTranslate((w/NUM_CHANNELS)*i, y);
        
        float wo = (w/NUM_CHANNELS)*i;
        
        ofSetColor(255, 100, 100);
        ofRect(wo, 0, cw, h);
        
        ofDrawBitmapString(ofToString(flow->channels[i].airPressure), wo+pad, pad*2);
        
        ofDrawBitmapString(ofToString(flow->channels[i].waterPressure), wo+pad, pad*4);
        
        //ofPopMatrix;
    }
    
    ofPopMatrix();
}

void Interface::drawMap(float x, float y, float w,  float h) {
    
    ofNoFill();
    
    for (int i=0; i < data->dataPoints.size(); i++) {        
        
        DataPoint * point = &data->dataPoints[i];
        
        if(point->loc->lat != 0 && point->loc->lng != 0) {
            
            float a = point->bikes.sampleAt(sim->elapsedFloat);
            point->marker = ofPoint(ofMap(point->loc->lat, minLat, maxLat, x, x+w), ofMap(point->loc->lng, minLng, maxLng, y, y+h));
            point->markerRadius = ofMap(a, 0, data->maxStatEntry, 2, 8);
            
            ofSetColor(255);
            if (selectedPoint) {
                if (selectedPoint->i == point->i) {
                    ofSetColor(255,0,0);
                }
            }
            
            ofCircle(point->marker, point->markerRadius);
            
        }
    }
}

void Interface::drawDetailInspector(float x, float y, float w, float h) {
    
    // add modes so this can either display selected point or selected path
    // draw point details
    if (selectedPoint) {
        ofPushMatrix();
        ofTranslate(x, y);
        ofSetColor(255,255,255);
        ofDrawBitmapString(selectedPoint->getLabel(), pad, pad);
        drawInterpolation(&selectedPoint->bikes, 0, 0, w, h);
        ofPopMatrix();
    } else if (selectedPath) {
        
    }
    
}

void Interface::drawInterpolation(MSA::Interpolator1D * ipo, float x, float y, float w, float h) {
    // curve
    ofPushMatrix();
    ofTranslate(x, y);
    
    for(int i=0; i < w; i++) {
        ofCircle(i, ofMap(ipo->sampleAt(i/w), 0, data->maxStatEntry, h, 0), 1);
    }
    // labels
    for(int i=0; i < ipo->size(); i++) {
        ofDrawBitmapString(ofToString(ipo->at(i)), (i*w/ipo->size()), h-pad);
    }
    
    ofPopMatrix();
    
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
    
    if(selectedPoint) {
        if(key == 'n') {
            selectedPoint = data->getNextPoint(selectedPoint);
        }
        if(key == 'b') {
            selectedPoint = data->getPreviousPoint(selectedPoint);
        }
    
        if(key == 'P') {
            Path p;
            data->paths.push_back(p);
        }
    
        if(key == '1') {
            
            data->paths[0].addPoint(selectedPoint);
        }
    }
    
    if(key == 'R') {
            for(int i=0; i < NUM_CHANNELS; i++) {
                flow->channels[i].path = &data->paths[i];
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
    ofPushMatrix();
    ofTranslate(x, y);
    
    ofFill(); 
    ofSetColor(100, 100, 100);
    ofRect(0, 0, w, h);
    
    ofSetColor(255, 255, 255);
    ofRect(0, 0, ofMap(sim->simElapsedTime, 0, sim->simDuration, 0, w), h);
 
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("Simulator time: " + sim->formatTime(sim->simElapsedTime) + " / " + sim->formatTime(sim->simDuration), pad, 12);
    ofDrawBitmapString("Real time: " + sim->formatTime(sim->realElapsedTime) + " / " + sim->formatTime(sim->realDuration), pad, 12+12); 
    ofDrawBitmapString("Speed: " + ofToString(sim->speed), pad, 12*3);
    
    ofPopMatrix();

}
