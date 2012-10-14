#include "flowControl.h"

void flowControl::setup(){
    // establish connection to arduino
}

void flowControl::update(){
    
}

void flowControl::debugDraw(){
    
}

void flowControl::injectAir(Channel * c, float duration) {
    openWaterValve(c);
    c->lock = true;
    // trigger close watervalve after duration time and set lock false;
}

void flowControl::openWaterValve(Channel * c) {
    c->waterOpen = true;
}

void flowControl::closeWaterValve(Channel * c) {
    c->waterOpen = false;
}

void flowControl::openAirValve(Channel * c) {
    c->airOpen = true;
}

void flowControl::closeAirValve(Channel * c) {
    c->airOpen = false;
}