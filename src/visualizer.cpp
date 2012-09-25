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
    
    for (int i=0; i<data->dataPoints.size(); i++) {
        DataPoint * point = &data->dataPoints[i];
        
        if (ofDist(x,y,point->marker.x, point->marker.y) < point->markerRadius) {
            selectedPoint = point;
        }
        
    }
    
}


void Visualizer::keyPressed(int key){
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


void Visualizer::drawDataPoint(DataPoint * point) {
    
    if(point->loc->lat != 0 && point->loc->lng != 0) {
                
        float a = point->bikes.sampleAt(sim->elapsedFloat);
        
        point->marker = ofPoint(ofMap(point->loc->lng, minLng, maxLng, 200, 680), ofMap(point->loc->lat, minLat, maxLat, 680, 200));
        
        point->markerRadius = ofMap(a, 0, data->maxStatEntry, 2, 36);
        
        ofCircle(point->marker, point->markerRadius);
        
    } 
}


void Visualizer::drawTimeline() {
    
}

void Visualizer::draw() {
    
    ofNoFill();    
    
    for (int i=0; i<data->dataPoints.size(); i++) {        
        drawDataPoint(&data->dataPoints[i]);
    }
    
    for (int i=0; i<data->paths.size(); i++) {
        drawPath(&data->paths[i]);
    }
    
    if (selectedPoint) {
        drawInterpolation(selectedPoint);
    }
    
}

void Visualizer::drawPath(Path * path) {
    
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


void Visualizer::drawInterpolation(MSA::Interpolator1D * ipo, float width, float height, float max) {
    
}

void Visualizer::drawInterpolation(DataPoint * point) {
    
    int width = 700;
    int i;
    
    ofSetColor(100, 259, 60, 255);
    ofDrawBitmapString(point->direction_name, 20, ofGetWindowHeight()-160);
    
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
    
}