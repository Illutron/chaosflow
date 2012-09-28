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
        loc.name = ofxjan.getValueS(data, "road");
        loc.lat = json_real_value(lat);
        loc.lng = json_real_value(lng);
        loc.dir_one_name = ofxjan.getValueS(data, "direction_one");
        loc.dir_two_name = ofxjan.getValueS(data, "direction_two");
        
        locations.push_back(loc);
        
    }
    
    json_decref(root);
}

void Data::getStatEntries(Location* loc){
    
    ofLogNotice()<<"Importing stat entries for "<<loc->name<<" ..."<<endl;
    
    ofHttpResponse response = ofLoadURL(endpoint + "locations/" + loc->oid + "/entries" );
    
    string responseStr = response.data;
    
    json_t* root;
    json_error_t error;
    
    root = json_loads(responseStr.c_str(), &error);
    
    int i;

    DataPoint newPoints [2];
    
    for(i = 0; i < json_array_size(root); i++)
    {
        json_t *data, *id;
        
        data = json_array_get(root, i);
        
        int direction = ofxjan.getValueI(data, "direction");
        int amount = ofxjan.getValueI(data, "amount");
        
        if (amount > maxStatEntry) {
            maxStatEntry = amount;
        }
        
        newPoints[direction-1].sum += amount;
        newPoints[direction-1].bikes.push_back(amount);
        
    }
    
    for(i = 0; i < 2; i++) {
        
        if (newPoints[i].sum != 0) {
            newPoints[i].loc = loc;
            dataPoints.push_back(newPoints[i]);
        }
    }
    
    
    
    json_decref(root);
}

void Path::addPoint(DataPoint * point) {
    points.push_back(point);
    update();
}

void Path::removeLocation(int index) {
    points.erase(points.begin()+index);
    update();
}


void Path::update() {
    sum.clear();
    
    for(int h=0; h<DATA_HOURS; h++) {
        int s = 0;
        
        for(int i=0; i<points.size(); i++) {
            DataPoint * point = points[i];
            
            //cout<<ofToString(loc->dir_one.size())<<" long"<<endl;
            
            if(point->bikes.size()>0) {
                s += point->bikes.at(h);
            }
        }
        
        sum.push_back(s);
    }

}
