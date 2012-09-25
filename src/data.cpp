#include "data.h"

void Data::setup(){
    maxStatEntry = 0;
    maxCombinedStatEntry = 0;
    endpoint = "http://" + ofToString(DATA_HOST) + ":" + ofToString(DATA_PORT) + "/";    
}


void Data::update(){
}

void Data::debugDraw(){
}

// import all data
void Data::getData(){
    
    // todo: don't do this if we already have the data
    
    ofLogNotice()<<"Importing data from endpoint at "<<endpoint<<" ..."<<endl;
    
    getLocations();    
    for (int i=0; i<locations.size(); i++) {
        getStatEntries(&locations[i]);
    }
    
    maxCombinedStatEntry = maxStatEntry * 2; // do this properly
    
}

void Data::getLocations(){
    
    ofLogNotice()<<"Importing all locations ..."<<endl;
    
    ofHttpResponse response = ofLoadURL(endpoint + "/locations");
    string responseStr = response.data;
    
    // todo: add error handling here and tell me to turn on the db and start flask
    
    //cout<<response.status<<endl;
    
    
    json_t* root;
    json_error_t error;
    
    root = json_loads(responseStr.c_str(), &error);
    
    int i;
    
    for(i = 0; i < json_array_size(root); i++)
    {
        json_t *data, *road, *id, *lat, *lng;
        
        data = json_array_get(root, i);      
        
        //cout<<"Getting: "<<ofxjan.getValueS(data, "road")<<endl;
        
        id = json_object_get(data, "_id");                
        lat = json_object_get(data, "lat");
        lng = json_object_get(data, "lng");
        
        Location loc;
        loc.oid = ofxjan.getValueS(id, "$oid");
        loc.road = ofxjan.getValueS(data, "road");
        loc.dir_one_label = ofxjan.getValueS(data, "direction_one");
        loc.dir_two_label = ofxjan.getValueS(data, "direction_two");
        loc.lat = json_real_value(lat);
        loc.lng = json_real_value(lng);
        
        locations.push_back(loc);
        
    }
    
    json_decref(root);
}

void Data::getStatEntries(Location* location){
    
    ofLogNotice()<<"Importing stat entries for "<<location->road<<" ..."<<endl;
    
    ofHttpResponse response = ofLoadURL(endpoint + "locations/" + location->oid + "/entries" );
    
    string responseStr = response.data;
    
    json_t* root;
    json_error_t error;
    
    root = json_loads(responseStr.c_str(), &error);
    
    int i;    
    for(i = 0; i < json_array_size(root); i++)
    {
        json_t *data, *id;
        
        data = json_array_get(root, i);
        
        int direction = ofxjan.getValueI(data, "direction");
        int amount = ofxjan.getValueI(data, "amount");
        
        if (amount > maxStatEntry) {
            maxStatEntry = amount;
        }
        
        if (direction == 1) {
            location->dir_one.push_back(amount);
        } else if (direction == 2) {
            location->dir_two.push_back(amount);
        }
    }
    
    json_decref(root);
}

void Path::addLocation(Location * loc) {
    locations.push_back(loc);
    update();
}

void Path::removeLocation(int index) {
    locations.erase(locations.begin()+index);
    update();
}


void Path::update() {
    dir_one.clear();
    dir_two.clear();
    
    for(int h=0; h<DATA_HOURS; h++) {
        int dir_one_a = 0;
        int dir_two_a = 0;
        
        for(int i=0; i<locations.size(); i++) {
            Location * loc = locations[i];
            
            //cout<<ofToString(loc->dir_one.size())<<" long"<<endl;
            
            if(loc->dir_one.size()>0) {
                //cout<<"dir_one +"<<endl;
                dir_one_a += loc->dir_one.at(h);
            }
            if(loc->dir_two.size()>0) {
                //cout<<"dir_two +"<<endl;
                dir_two_a += loc->dir_two.at(h);
            }
        }
        
        dir_one.push_back(dir_one_a);
        dir_two.push_back(dir_two_a);
    }

}
