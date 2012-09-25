#pragma once

#include "ofMain.h"

#include "jansson.h"
#include "ofxJansson.h"
#include "MSAInterpolator.h"

#include "defines.h"


struct Location {
    
    string oid;
    
    // global coordinates
    double  lat;
    double  lng;
    
    // local pixel coordinates in visualization
    ofPoint marker;
    float markerRadius;
    
    // label
    string road;
    
    string dir_one_label;
    string dir_two_label;
    
    MSA::Interpolator1D dir_one;
    MSA::Interpolator1D dir_two;
    
};

struct Path {
    vector<Location*> locations;  
    MSA::Interpolator1D dir_one;
    MSA::Interpolator1D dir_two;
    
    void addLocation(Location * loc);
    void removeLocation(int index);
    
    void update();
    
    int size() { return locations.size(); };
};

class Data {
public:
    
    void setup();
    void update();
    void debugDraw();
    
    void getData();
    
    vector<Location> locations;
    vector<Path> paths;
    
    //double maxLat;
    //double minLat;
    //double maxLng;
    //double minLng;
    
    int maxStatEntry;
    int maxCombinedStatEntry;
    
private:
    
    void getLocations();
    void getStatEntries(Location* location);
    
    ofxJansson ofxjan;
    
    string endpoint;
    
};  
