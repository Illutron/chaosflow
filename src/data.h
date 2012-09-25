#pragma once

#include "ofMain.h"
#include "jansson.h"
#include "ofxJansson.h"
#include "MSAInterpolator.h"
#include "defines.h"


struct Location {
    string oid;
    string name;
    
    string dir_one_name;
    string dir_two_name;
    
    double lat;
    double lng;
};

struct DataPoint {
    
    string direction_name;
    
    MSA::Interpolator1D bikes;
    
    Location * loc;
    
    // local pixel coordinates in visualization
    ofPoint marker;
    float markerRadius;
};

struct Path {
    vector<DataPoint*> points;
    
    MSA::Interpolator1D sum;
    int sum_max;
    
    void addPoint(DataPoint * point);
    void removeLocation(int index);
    
    void update();
    int size() { return points.size(); };
};

class Data {
public:
    
    void setup();
    void update();
    void debugDraw();
    
    void getData();
    //void reloadData();
    
    vector<Location> locations;
    vector<DataPoint> dataPoints;
    vector<Path> paths;
    
    double maxLat;
    double minLat;
    double maxLng;
    double minLng;
    
    int maxStatEntry;
    int maxCombinedStatEntry;
    
private:
    
    void getLocations();
    void getStatEntries(Location* location);
    
    ofxJansson ofxjan;
    
    string endpoint;
    
};  
