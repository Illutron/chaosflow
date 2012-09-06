#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    data = new Data();
    gui = new Gui();
    visualizer = new Visualizer();
    simulator = new Simulator();
    flowcontrol = new flowControl();
    
    data->setup();
    gui->setup();
    simulator->setup(data, gui);
    visualizer->setup(data, gui, simulator);
    flowcontrol->setup();
    
    data->getData();
    
    ofSetVerticalSync(true);    
    ofSetSphereResolution(128);
    ofBackground(0,0,0);
	ofSetColor(255,255,255);
    ofEnableAlphaBlending();
    
    maxLat = 55.7368;
    minLat = 55.6108;    
    maxLng = 12.6293;
    minLng = 12.4519;
    
    simulator->start();
    
}


//--------------------------------------------------------------
void testApp::update(){
    data->update();
    gui->update();
    simulator->update();
    visualizer->update();
    flowcontrol->update();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofNoFill();    
    
    for (int i=0; i<data->locations.size(); i++) {
        
        if(data->locations[i].lat != 0 && data->locations[i].lng != 0) {
        
            float sizeOne = 0;
            float sizeTwo = 0;
            
            // add up entries
            
            //int hour = (simulator->simElapsedTime / (1000*60*60)) + 7;
            //float fintohour = (simulator->simElapsedTime % (1000*60*60)) / 3600000.0;
            
            //cout<<ofToString(fintohour)<<endl;
            
            /*float hourOne;
            float hourTwo;
            
             
             
            for (int e=0; e<data->locations[i].dir_one.size(); e++) {
                
                if (data->locations[i].dir_one[e].hour == hour) {
                    hourOne = data->locations[i].dir_one[e].amount;
                } else if (data->locations[i].dir_one[e].hour == hour+1) {
                    hourTwo = data->locations[i].dir_one[e].amount;
                }
                
            }*/

            float elapsed = simulator->simElapsedTime / float(simulator->simDuration);
            
            //cout<<ofToString(elapsed)<<endl;
            
            sizeOne = data->locations[i].dir_one.sampleAt(elapsed);
            sizeTwo = data->locations[i].dir_two.sampleAt(elapsed);
            
            //sizeOne = (fintohour * hourTwo) + ((1.0-fintohour) * hourOne);
            // Create an interpolation function and move to simulator
            
            /*for (int e=0; e<data->locations[i].dir_two.size(); e++) {
                
                if (data->locations[i].dir_two[e].hour == hour) {
                    hourOne = data->locations[i].dir_two[e].amount;
                } else if (data->locations[i].dir_two[e].hour == hour+1) {
                    hourTwo = data->locations[i].dir_two[e].amount;
                }
                
            }*/
            
            //sizeTwo = (fintohour * hourTwo) + ((1.0-fintohour) * hourOne);
            
            /*if (size == 0) {
                cout<<locations[i].road<<" has no entries";
            }theese seem to be the motorways we should sort them out and add a database flag
             */
            
                
                ofSetColor(ofMap(sizeOne, 0, 2000, 80, 255), 100, ofMap(sizeTwo, 0, 2000, 0, 255));
                ofCircle(ofMap(data->locations[i].lat, minLat, maxLat, 20, 680), ofMap(data->locations[i].lng, minLng, maxLng, 20, 680), ofMap(sizeOne+sizeTwo, 0, 4000, 2, 36));
            
            
            
        /*
         // label
         ofDrawBitmapString(locations[i].road, ofMap(locations[i].lat, minLat, maxLat, 20, 680), ofMap(locations[i].lng, minLng, maxLng, 20, 680));
        */
        } 
        
    }
    
    data->debugDraw();
    visualizer->debugDraw();
    simulator->debugDraw();
    flowcontrol->debugDraw();
    
    gui->draw();
}


void testApp::keyPressed(int key){
    gui->keyPressed(key);
}

void testApp::keyReleased(int key){
    
}

void testApp::mouseMoved(int x, int y){

}

void testApp::mouseDragged(int x, int y, int button){

}

void testApp::mousePressed(int x, int y, int button){

}

void testApp::mouseReleased(int x, int y, int button){

}

void testApp::windowResized(int w, int h){

}

void testApp::gotMessage(ofMessage msg){

}

void testApp::dragEvent(ofDragInfo dragInfo){ 

}