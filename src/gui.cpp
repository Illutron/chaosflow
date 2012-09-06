#include "gui.h"

void Gui::setup(){
    
    ui = new ofxUICanvas(0,0,320,320);
    
    ui->addWidgetDown(new ofxUILabel("Chaotic flow", OFX_UI_FONT_MEDIUM));
    
    ui->addSlider("BACKGROUND VALUE",0.0,255.0,100.0,304,16);
    ui->addWidgetDown(new ofxUIToggle(32, 32, false, "FULLSCREEN"));
    
    
    //ui->addSlider("Speed",&data->speed,255.0,100.0,304,16);
    
    ofAddListener(ui->newGUIEvent, this, &Gui::guiEvent); 
    
    ui->loadSettings("GUI/guiSettings.xml"); 
    
}

void Gui::update(){
}

void Gui::draw(){    
    
}

void Gui::exit()
{
    ui->saveSettings("GUI/guiSettings.xml"); 
    delete ui; 
}

void Gui::guiEvent(ofxUIEventArgs &e)
{
    if(e.widget->getName() == "BACKGROUND VALUE")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;    
        ofBackground(slider->getScaledValue());
    }
    else if(e.widget->getName() == "FULLSCREEN")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        ofSetFullscreen(toggle->getValue());   
    }
}

void Gui::keyPressed(int key)
{
    switch (key) {
        case 'p':
            ui->setDrawWidgetPadding(true);
            break;
        case 'P':
            ui->setDrawWidgetPadding(false);
            break;
            
            
        default:
            break;
    }
}