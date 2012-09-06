#include "visualizer.h"

void Visualizer::setup(Data * dataRef, Gui * guiRef, Simulator * simRef){
    data = dataRef;
    gui = guiRef;
    sim = simRef;
    
    maxLat = 55.7368;
    minLat = 55.6108;    
    maxLng = 12.6293;
    minLng = 12.4519;

}

void Visualizer::update(){
    
}

void Visualizer::debugDraw(){
    
}

void Visualizer::drawMap() {
    
    ofNoFill();    
    
    for (int i=0; i<data->locations.size(); i++) {
        
        if(data->locations[i].lat != 0 && data->locations[i].lng != 0) {
            
            float elapsed = sim->simElapsedTime / float(sim->simDuration);
            
            float aOne = data->locations[i].dir_one.sampleAt(elapsed);
            float aTwo = data->locations[i].dir_two.sampleAt(elapsed);
            
            ofSetColor(ofMap(aOne, 0, 2000, 80, 255), 100, ofMap(aTwo, 0, 2000, 0, 255));
            ofCircle(ofMap(data->locations[i].lat, minLat, maxLat, 20, 680), ofMap(data->locations[i].lng, minLng, maxLng, 20, 680), ofMap(aOne+aTwo, 0, 4000, 2, 36));
            
        } 
        
    }
    
}

void Visualizer::drawInterpolation(Location location) {
    
}