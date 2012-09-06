#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "defines.h"

class Gui {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
    
    ofxUICanvas * ui; 
    void exit(); 
    void guiEvent(ofxUIEventArgs &e);
    
    void loadSettings();
    
    
    bool playToggle;
    float simSpeed;
    
    
};