#pragma once

#include "ofMain.h"
#include "data.h"
#include "gui.h"
#include "defines.h"

class installationControl {
public:
    
	void setup(Data * dataRef, Gui * guiRef);
	void update();
	void debugDraw();
    
    // data
    Data * data;
    Gui * gui;
    
};