#pragma once

#include "ofMain.h"
#include "data.h"
#include "gui.h"
#include "defines.h"

#include "MSAInterpolator.h"

class Simulator {
public:

	void setup(Data * dataRef, Gui * guiRef);
	void update();
	void debugDraw();
    
    void start();
    void pause();
    void resume();
    
    
    
    
    // data
    Data * data;
    Gui * gui;
    
    void drawInterpolation();
    MSA::Interpolator1D	 myInterpolator1D;
    MSA::Interpolator1D	 myInterpolator1D_two;
    
    
    string formatTime(int millis);
    
    void stop();    
    void setSpeed();
    
    float speed;
    
    // simulator time and duration
    int simElapsedTime;
    int simDuration;    
    int lastUpdateTime;
    int simStartOffset;
    
    bool playing;
    

    

};