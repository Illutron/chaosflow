#include "data.h"

void Data::setup(){
    DATA_HOST = "http://127.0.0.1:5000";
    
    maxStatEntry = 0;
    maxCombinedStatEntry = 0;
}


void Data::update(){
    
}

void Data::debugDraw(){
    
}

// import all data
void Data::getData(){
    
    // don't do this if we already have the datan
    
    cout<<"Importing data ... "<<endl;
    
    getLocations();    
    for (int i=0; i<locations.size(); i++) {
        getStatEntries(&locations[i]);
    }
    
    maxCombinedStatEntry = maxStatEntry * 2; // do this properly
    
}

void Data::getLocations(){
    
    string url = DATA_HOST + "/locations";
    
    ofHttpResponse response = ofLoadURL(url);
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
    
    //cout<<"Getting entries for "<<location->road<<endl;
    
    ofHttpResponse response = ofLoadURL(DATA_HOST + "/locations/" + location->oid + "/entries" );
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
