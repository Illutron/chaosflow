#pragma once

#include "ofMain.h"
#include "jansson.h"
#include "ofxJansson.h"
#include "MSAInterpolator.h"
#include "defines.h"


struct Location {
    int index;
    
    string oid;
    string name;
    
    string dir_names [2];
    
    double lat;
    double lng;
};

struct DataPoint {
    int i; // index
    
    int direction;
    
    string getDirName() {
        return loc->dir_names[direction];
    }
    
    string getLabel() {
        return loc->name + " - " + loc->dir_names[direction];
    }
    
    MSA::Interpolator1D bikes;
    int sum;
    
    Location * loc;
    
    // local pixel coordinates in visualization
    ofPoint marker;
    float markerRadius;
};

struct Path {
    int index;
    
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
    
    DataPoint* getNextPoint(DataPoint * point);
    DataPoint* getPreviousPoint(DataPoint * point);
    
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
