#pragma once

// This module has functions for visualizing the data. Does it also handle interface events like making paths or should I add this to data? Maybe add it all to gui class?

#include "ofMain.h"
#include "gui.h"
#include "data.h"
#include "simulator.h"
#include "defines.h"

class Interface {
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
    
    
    float pad;
       
    void draw();
    
    void drawMap(float x1, float y1, float w, float h);
    void drawMapPoint(DataPoint * point);
    void drawTimeline(float x1, float y1, float w, float h);
    
    void drawDetailInspector(float x1, float y1, float w, float h);
    
    
    void drawPath(Path * path);
    
    void drawMapPoint();
    
    void drawMapPath();
    
    
    void drawInterpolation(MSA::Interpolator1D * ipo, float x1, float y1, float w, float h);
    
    
    Path * selectedPath;
    DataPoint * selectedPoint;
    
    
};