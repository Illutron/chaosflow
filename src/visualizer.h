#pragma once

#include "ofMain.h"
#include "gui.h"
#include "data.h"
#include "simulator.h"
#include "defines.h"

class Visualizer {
public:
	void setup(Data * dataRef, Gui * guiRef, Simulator * simRef);
	void update();
    
    void mousePressed(int x, int y, int button);
    
	void debugDraw();
    
    void draw();
    void drawLocation(Location * loc);
    void drawInterpolation(Location * loc);
    
    Data * data;
    Gui * gui;
    Simulator * sim;
    
    // calibration
    double minLat;
    double minLng;
    double maxLat;
    double maxLng;
    
    Location * selectedLoc;
    
};