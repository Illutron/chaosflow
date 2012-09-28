#include "gui.h"

void Gui::setup(){
        
    ui = new ofxUICanvas(0,0,0,0);
    
    ui->setDrawBack(true);
    
    ui->addWidgetDown(new ofxUILabel("Chaotic flow", OFX_UI_FONT_MEDIUM));
    
    ui->addWidgetDown(new ofxUIToggle(32, 32, false, "FULLSCREEN"));
    
    //ui->addWidgetDown(new ofxUIToggle(32, 32, false, "PLAY/PAUSE"));
    
    //ui->addWidgetDown(new ofxUILabelToggle(&playToggle, "Play / Pause"));
    ui->addToggle("Play Pause", &playToggle, 32, 32);
    
    ui->addWidgetDown(new ofxUIRotarySlider(32, 32, 100, -1200, 1200, &simSpeed, "Speed")); 		

    //ui->addWidgetDown(new ofxUISlider(32, 32, false, "PLAY/PAUSE"));
    
    //ui->addToggle("Play / Pause",playToggle,304,16);

    
    ofAddListener(ui->newGUIEvent, this, &Gui::guiEvent); 
    
     
    
}

void Gui::loadSettings(){
    ui->loadSettings("GUI/guiSettings.xml");
}

void Gui::update(){
}

void Gui::draw(){    
    ui->draw();
    ui->drawBack();
    ui->ofxUIWidget::update();
}

void Gui::exit()
{
    ui->saveSettings("GUI/guiSettings.xml"); 
    delete ui; 
}

void Gui::guiEvent(ofxUIEventArgs &e)
{
    if(e.widget->getName() == "FULLSCREEN")
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