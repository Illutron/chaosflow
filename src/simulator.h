#pragma once

#include "ofMain.h"
#include "data.h"
#include "flowControl.h"
#include "defines.h"

#include "MSAInterpolator.h"

class Simulator {
public:

	void setup(Data * dataRef, flowControl * flowRef);
	void update();
	void debugDraw();
    
    void play();
    void pause();
    void stop();
    
    void simulatePaths();
    void simulatePath(Channel * c);
    
    // data
    Data * data;
    flowControl * flow;
    
    void drawInterpolation();
    MSA::Interpolator1D	 myInterpolator1D;
    MSA::Interpolator1D	 myInterpolator1D_two;
    
    string formatTime(int millis);    
    
    float speed;
    float elapsedFloat;
    int simElapsedTime;
    int simDuration;    
    int lastUpdateTime;
    int simStartOffset;
    int realDuration;
    int realElapsedTime;
    
    bool playing;
    
};