#include "interface.h"

void Interface::setup(Data * dataRef, Simulator * simRef, flowControl * flowRef){
    data = dataRef;
    sim = simRef;
    flow = flowRef;
    
    maxLat = 55.7368;
    minLat = 55.6108;    
    maxLng = 12.6293;
    minLng = 12.4519;
    
    pad = 8;
    
    selectedChannel = &flow->channels[0];
    selectedPath = &data->paths[0];
    selectedPoint = &data->dataPoints[0];
    
    //cout << "listening for osc messages on port 7000"<<endl;
    //receiver.setup(7000);
    
    //sender.setup(SEND_HOST, SEND_PORT);
    
    //mode = 0;
}

void Interface::update(){
    
    /*for(int i = 0; i < NUM_MSG_STRINGS; i++){
		if(timers[i] < ofGetElapsedTimef()){
			msg_strings[i] = "";
		}
	}*/
    /*
	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
        if(m.getAddress() == "/1/fader3"){
            timeStep = ofMap(m.getArgAsFloat(0), 0, 1, -150, 150); 
        }
        
        if(m.getAddress() == "/1/fader1"){
            particleNeighborhood = ofMap(m.getArgAsFloat(0), 0, 1, 0, 25); 
        }
        
        if(m.getAddress() == "/1/fader4"){
            particleRepulsion = ofMap(m.getArgAsFloat(0), 0, 1, 0, 1); 
        }
        
        
        if(m.getAddress() == "/1/fader5"){
            centerAttraction = ofMap(m.getArgAsFloat(0), 0, 1, -1, 1); 
        }
        
        if(m.getAddress() == "1/fader2"){
            bodyAttraction = ofMap(m.getArgAsFloat(0), 0, 1, -1, 1); 
        }
        
        if(m.getAddress() == "/1/xy1"){
            int x = ofMap(m.getArgAsFloat(0), 0, 1, 0, ofGetWidth());
            int y = ofMap(m.getArgAsFloat(1), 0, 1, 0, ofGetHeight());
            
            centerLoc = ofVec2f(x, y);
            
        }*/
        
        
        
        /*
        
        if(m.getAddress() == "/1/toggle14"){
            if(m.getArgAsInt32(0) == 1) {
                drawSkeleton = true;
            } else {
                drawSkeleton = false;
            }
        }
        
        if(m.getAddress() == "/1/toggle13"){
            if(m.getArgAsInt32(0) == 1) {
                dynamicTime = true;
            } else {
                dynamicTime = false;
            }
        }
        */
        
        
	//}
    
    
    // update locations for stuff that is clickable here ?
    
}

void Interface::randomData() {
    
}

void Interface::draw() {
    
    ofFill(); 
    ofBackground(0, 0, 0);
    ofSetColor(255);
    
    float w = ofGetWidth();
    float h = ofGetHeight();
            
    // draw settings area 
    
    
    // draw path selector area
    drawPathInspector(0, 0, w*0.5, h*0.5);
    
    // draw map 50% 0, 100%, 60%
    drawMap(w*0.5+pad, 0+pad, (w*0.5)-(2*pad), (h*0.5)-(2*pad));
    
    // draw detail inspection view / path editor 
    drawPointInspector(0, h*0.5, w*0.5, h*0.45);
    
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
    
    
    ofSetColor(20, 20, 255);
    if(selectedPath){
        ofDrawBitmapString("Selected path: " + ofToString(selectedPath->i), 20, 20);
        ofDrawBitmapString("   Sum max: " + ofToString(selectedPath->sum_max), 20, 40);
    }
    if(selectedPoint){
        ofDrawBitmapString("Selected point: " + ofToString(selectedPoint->i), 20, 80);
    }
    if(selectedChannel){
        ofDrawBitmapString("Selected channel: " + ofToString(selectedChannel->i), 20, 140);
    }
    
    ofSetColor(255,20,20);
    ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate()), 20, 180);
    
    
}


void Interface::drawOutput(float x, float y, float w, float h) {
    ofPushMatrix();
    ofTranslate(x, y);
    
    float cw = w/NUM_CHANNELS;
    
    for(int i=0; i < NUM_CHANNELS; i++) {
        
        Channel * c = &flow->channels[i];
        
        float wo = (w/NUM_CHANNELS)*i;
        
        ofSetColor(255, 100, 100);
        if(c == selectedChannel) {
            ofSetColor(255, 255, 255);
        }
        
        ofRect(wo, 0, cw, h);
        
        ofDrawBitmapString("Cha: " + ofToString(c->i), wo+pad, pad*2);
        ofDrawBitmapString(ofToString(c->airPressure), wo+pad, pad*4);
        ofDrawBitmapString(ofToString(c->waterPressure), wo+pad, pad*6);
        ofDrawBitmapString(ofToString(c->waterOpen), wo+pad, pad*8);
        ofDrawBitmapString(ofToString(c->airOpen), wo+pad, pad*10);
        
        if(c->path) {
            drawInterpolation(&c->path->sum, sim->maxPathSum, false,  wo, 100, cw, 100);
        }
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

void Interface::drawPointInspector(float x, float y, float w, float h) {
    
    // add modes so this can either display selected point or selected path
    // draw point details
    if (selectedPoint) {
        ofPushMatrix();
        ofTranslate(x, y);
        ofSetColor(255,255,255);
        ofDrawBitmapString(selectedPoint->getLabel(), pad, pad);
        drawInterpolation(&selectedPoint->bikes, 0, 0, w, h);
        ofPopMatrix();
    }
}


void Interface::drawInterpolation(MSA::Interpolator1D * ipo, float x, float y, float w, float h) {
    drawInterpolation(ipo, data->maxStatEntry, true, x, y, w, h);
}

void Interface::drawInterpolation(MSA::Interpolator1D * ipo, float max, float x, float y, float w, float h) {
    drawInterpolation(ipo, max, true, x, y, w, h);
}

void Interface::drawInterpolation(MSA::Interpolator1D * ipo, float max, bool labels, float x, float y, float w, float h) {
    // curve
    ofPushMatrix();
    ofTranslate(x, y);
    
    if(ipo && max != 0) {
        for(int i=0; i < w; i++) {
            ofCircle(i, ofMap(ipo->sampleAt(i/w), 0, max, h, 0), 1);
        }
        // labels
        if(labels) {
            for(int i=0; i < ipo->size(); i++) {
                ofDrawBitmapString(ofToString(ipo->at(i)), (i*w/ipo->size()), h-pad);
            }
        }
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
    }
    
    if(selectedPath) {
        if(key == 'h') {
            selectedPath = data->getNextPath(selectedPath);
        }
        if(key == 'g') {
            selectedPath = data->getPreviousPath(selectedPath);
        }
        
        if(key == 'a') {
            if(selectedPoint) {
                selectedPath->addPoint(selectedPoint);
            }
        }
    }
    
    if(selectedChannel) {
        if(key == 'y') {
            selectedChannel = flow->getNextChannel(selectedChannel);
        }
        if(key == 't') {
            selectedChannel = flow->getPreviousChannel(selectedChannel);
        }
        
        
        if(key == 'o') {
            selectedChannel->waterOpen = false;
            flow->updateChannel(selectedChannel);
        } else if(key == 'O') {
            selectedChannel->waterOpen = true;
            flow->updateChannel(selectedChannel);
        } else if(key == 'p') {
            selectedChannel->airOpen = false;
            flow->updateChannel(selectedChannel);
        } else if(key == 'P') {
            selectedChannel->airOpen = true;
            flow->updateChannel(selectedChannel);
        } else if(key == 'i') {
            selectedChannel->airPressure += 0.01;
            flow->updateChannel(selectedChannel);
        } else if(key == 'I') {
            selectedChannel->airPressure -= 0.01;
            flow->updateChannel(selectedChannel);
        } else if(key == 'u') {
            selectedChannel->waterPressure += 0.01;
            flow->updateChannel(selectedChannel);
        } else if(key == 'U') {
            selectedChannel->waterPressure -= 0.01;
            flow->updateChannel(selectedChannel);
        }
        
        
        if(key == 'q') {
            if(selectedPath) {
                selectedChannel->path = selectedPath;
            }
        }
        
    }
    
    if(key == 'R') {
            for(int i=0; i < NUM_CHANNELS; i++) {
                flow->channels[i].path = &data->paths[i];
            }
    }
    
}

void Interface::drawPathInspector(float x, float y, float w, float h) {
    ofPushMatrix();
    ofTranslate(x, y);
    ofSetColor(255);
    
    if(selectedPath) {
        
        drawInterpolation(&selectedPath->sum, selectedPath->sum_max, 0, 0, w, h);
        
        // list of points
        for(int i=0; i<selectedPath->points.size(); i++) {
            // path->points[i]->loc->name;
        }
    }
    
    ofPopMatrix();
    
}

void Interface::drawPathList(float x, float y, float w, float h) {
    ofPushMatrix();
    ofTranslate(x, y);
    
    ofSetColor(255);
        
    for(int i = 0; i < NUM_CHANNELS; i++) {
        ofDrawBitmapString("Path of " + ofToString(data->paths[i].size()) + " points", pad, 20 + (i*20));
    }
    
    ofPopMatrix();
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
