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
	void debugDraw();
    
    void drawMap();
    void drawInterpolation(Location location);
    
    Data * data;
    Gui * gui;
    Simulator * sim;
    
    // calibration
    double minLat;
    double minLng;
    double maxLat;
    double maxLng;
    
    
};