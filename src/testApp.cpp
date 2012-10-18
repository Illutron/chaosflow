
#include "testApp.h"

// to do update interpolator to version at https://github.com/memo/ofxMSAInterpolator

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetLogLevel(OF_LOG_SILENT);
    data = new Data();
    flowcontrol = new flowControl();
    ui = new Interface();
    simulator = new Simulator();
    
    data->setup();
    flowcontrol->setup();
    simulator->setup(data, flowcontrol);
    ui->setup(data, simulator, flowcontrol);
    
    ofSetVerticalSync(true);    
    ofSetSphereResolution(128);
    ofBackground(50,50,50);
    ofEnableSmoothing();
	ofSetColor(255,255,255);
    ofEnableAlphaBlending();
    
    simulator->play();
}


//--------------------------------------------------------------
void testApp::update(){
    data->update();
    simulator->update();
    ui->update();
    flowcontrol->update();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    
    
    data->debugDraw();
    simulator->debugDraw();
    flowcontrol->debugDraw();
    
    ui->draw();
}

void testApp::exit() {
    //ui->exit();
}

void testApp::keyPressed(int key){
    ui->keyPressed(key);    
}

void testApp::keyReleased(int key){
    
}

void testApp::mouseMoved(int x, int y){

}

void testApp::mouseDragged(int x, int y, int button){

}

void testApp::mousePressed(int x, int y, int button){
    ui->mousePressed(x, y, button);
}

void testApp::mouseReleased(int x, int y, int button){

}

void testApp::windowResized(int w, int h){

}

void testApp::gotMessage(ofMessage msg){

}

void testApp::dragEvent(ofDragInfo dragInfo){ 

}