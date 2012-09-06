#pragma once

#include "ofMain.h"
#include "data.h"
#include "gui.h"
#include "simulator.h"
#include "flowControl.h"
#include "visualizer.h"


class testApp : public ofBaseApp {
	
    public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        
    Data * data;
    Gui * gui;
    Simulator * simulator;
    flowControl * flowcontrol;
    Visualizer * visualizer;
    
    
    // calibration
    double minLat;
    double minLng;
    double maxLat;
    double maxLng;
    
    
};  
