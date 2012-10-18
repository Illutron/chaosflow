#pragma once

// This module has functions for visualizing the data. Does it also handle interface events like making paths or should I add this to data? Maybe add it all to gui class?

#include "ofMain.h"
#include "defines.h"
#include "data.h"
#include "simulator.h"
#include "flowControl.h"

#define NUM_MSG_STRINGS 20


class Interface {
public:
	void setup(Data * dataRef, Simulator * simRef, flowControl * flowRef);
	void update();
    
    void mousePressed(int x, int y, int button);
    void keyPressed(int key);
    
    void randomData();
    
    Data * data;
    Simulator * sim;
    flowControl * flow;
    
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
    
    void drawPointInspector(float x1, float y1, float w, float h);
    
    void drawOutput(float x1, float y1, float w, float h);
    
    void drawPathList(float x1, float y1, float w, float h);
    
    void drawPathInspector(float x1, float y1, float w, float h);
    
    void drawPathLabel(Path * path);
    
    void drawMapPoint();
    
    void drawMapPath();
    
    void drawInterpolation(MSA::Interpolator1D * ipo, float x1, float y1, float w, float h);
    void drawInterpolation(MSA::Interpolator1D * ipo, float max, float x1, float y1, float w, float h);
    void drawInterpolation(MSA::Interpolator1D * ipo, float max, bool labels, float x1, float y1, float w, float h);
    
    Path * selectedPath;
    DataPoint * selectedPoint;
    Channel * selectedChannel;
    
    /*
    ofxOscReceiver receiver;
    ofxOscSender sender;
    
    int current_msg_string;
    string msg_strings[NUM_MSG_STRINGS];
    float timers[NUM_MSG_STRINGS];*/
    
    
};