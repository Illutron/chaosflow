#pragma once

#include "ofMain.h"

#include "jansson.h"
#include "ofxJansson.h"
#include "MSAInterpolator.h"

/*
struct Entry {
    //string oid;
    //string location_oid;
    //string type;
    
    // we could do with only hour and amount if needed
    //int hour;
    int amount;
    
    int direction;
};*/


struct Location {
    
    string oid;
    
    // global coordinates
    double  lat;
    double  lng;
    
    // label
    string road;
    
    string dir_one_label;
    string dir_two_label;
    
    MSA::Interpolator1D dir_one;
    MSA::Interpolator1D dir_two;
    
    //vector<Entry> dir_one;
    //vector<Entry> dir_two;    
};



class Data {
public:
    
    void setup();
    void update();
    void debugDraw();
    
    void getData();
    
    vector<Location> locations;
    
private:
    
    void getLocations();
    void getStatEntries(Location* location);
    
    ofxJansson ofxjan;
    string DATA_HOST;    
    
};  
