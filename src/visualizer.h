#pragma once

// This module has functions for visualizing the data. Does it also handle interface events like making paths or should I add this to data? Maybe add it all to gui class?

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
    void keyPressed(int key);
    
    Data * data;
    Gui * gui;
    Simulator * sim;
    
    // calibration
    double minLat;
    double minLng;
    double maxLat;
    double maxLng;
    
	void debugDraw();
    
    void draw();
    
    void drawLocation(Location * loc);
    void drawPath(Path * path);
    
    void drawMap();
    
    void drawMapPoint();
    
    void drawMapPath();
    
    void drawInterpolation(MSA::Interpolator1D * ipo, float width, float height, float max);
    
    void drawInterpolation(Location * loc);
    
    void drawTimeline();
    
    
    Path * selectedPath;
    Location * selectedLoc;
    
    
};