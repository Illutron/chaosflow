
#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    data = new Data();
    gui = new Gui();
    ui = new Interface();
    simulator = new Simulator();
    flowcontrol = new flowControl();
    
    data->setup();
    gui->setup();
    simulator->setup(data, gui);
    ui->setup(data, gui, simulator, flowcontrol);
    flowcontrol->setup();
    
    data->getData();
    
    ofSetVerticalSync(true);    
    ofSetSphereResolution(128);
    ofBackground(50,50,50);
    ofEnableSmoothing();
	ofSetColor(255,255,255);
    ofEnableAlphaBlending();
    
    gui->loadSettings();
    simulator->play();
}


//--------------------------------------------------------------
void testApp::update(){
    data->update();
    gui->update();
    simulator->update();
    ui->update();
    flowcontrol->update();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ui->draw();
    
    
    data->debugDraw();
    simulator->debugDraw();
    flowcontrol->debugDraw();
    //gui->draw();
}

void testApp::exit() {
    gui->exit();
}

void testApp::keyPressed(int key){
    gui->keyPressed(key);
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