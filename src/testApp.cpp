#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    data = new Data();
    gui = new Gui();
    visualizer = new Visualizer();
    simulator = new Simulator();
    flowcontrol = new flowControl();
    
    data->setup();
    gui->setup();
    simulator->setup(data, gui);
    visualizer->setup(data, gui, simulator);
    flowcontrol->setup();
    
    data->getData();
    
    ofSetVerticalSync(true);    
    ofSetSphereResolution(128);
    ofBackground(0,0,0);
	ofSetColor(255,255,255);
    ofEnableAlphaBlending();
    
    
    
    gui->loadSettings();
    simulator->start();
    
}


//--------------------------------------------------------------
void testApp::update(){
    data->update();
    gui->update();
    simulator->update();
    visualizer->update();
    flowcontrol->update();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    data->debugDraw();
    visualizer->debugDraw();
    simulator->debugDraw();
    flowcontrol->debugDraw();
    
    gui->draw();
}

void testApp::exit() {
    gui->exit();
}

void testApp::keyPressed(int key){
    gui->keyPressed(key);
}

void testApp::keyReleased(int key){
    
}

void testApp::mouseMoved(int x, int y){

}

void testApp::mouseDragged(int x, int y, int button){

}

void testApp::mousePressed(int x, int y, int button){

}

void testApp::mouseReleased(int x, int y, int button){

}

void testApp::windowResized(int w, int h){

}

void testApp::gotMessage(ofMessage msg){

}

void testApp::dragEvent(ofDragInfo dragInfo){ 

}