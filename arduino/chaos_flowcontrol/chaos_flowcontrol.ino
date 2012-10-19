#define CHANNEL_NUM 5 

int commandValue = 0;   // for incoming serial data

String inputString;
boolean newCommand = false;

int channel = 0;
int value = 0;

int state = 2; //0 = auto 1 = pending 2 = controlled
long autoDelay = 400;
long lastContact = 0;

bool testing = false;

int channels [CHANNEL_NUM];

float waterPressure [CHANNEL_NUM];
boolean waterValveOpen [CHANNEL_NUM];
boolean airValveOpen [CHANNEL_NUM];
float airPressure [CHANNEL_NUM];

int waterValvePins [CHANNEL_NUM];
int airValvePins [CHANNEL_NUM]; 
int pumpPins [CHANNEL_NUM]; 
int airRegulatorPins [CHANNEL_NUM];

// syntax
// 2 W 1.0 

void setup() {
    Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
    inputString.reserve(200);
    
    pinMode(8, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    
    waterValvePins[0] = 8;
    waterValvePins[1] = 12;
    waterValvePins[2] = 13;
    
    airValvePins[0] = 2;
    airValvePins[1] = 4;
    airValvePins[2] = 7;
    
    pumpPins[0] = 3;
    pumpPins[1] = 5;
    pumpPins[2] = 6;
    
    airRegulatorPins[0] = 9;
    airRegulatorPins[1] = 10;
    airRegulatorPins[2] = 11;
    
    for(int i=0; i< CHANNEL_NUM; i++) {
      setAirPressure(i, 90);
      closeAir(i);
      openWater(i);
     
    }
    
    setAirPressure(1, 120);
    
    
   
}

void loop() {
       
       // //  
       // // arduino 1 
       // 0 is 2
       // 2 is 1
       // 3 - 0
       // 4 - 1 // 3 vand og 4 vand rør hindanden
       // 5 - 2
       // 6 - 0
       // 7 - 1
       
       // arduino 1
       // 0: virker ikke
       // 1: success
       // 2: success
       
       // arduino 2
       // 3: - pumpe trækker kun 0.2 ampere ved 12v
       // 4: success 
       // 5: - pumpe kortsluttet
       
       // arduino 3
       // 6: success
       // 7: success  
       
    int tc = 0;
    

    
    //setAirPressure(tc, 120);
    //openAir(tc);
    
    
       
       

 
        
 if (!testing) {   
        
        // send data only when yoSu receive data:
       if (!Serial.available()) {
          // no data
          if (state == 2) {
            state = 1;
            lastContact = millis();
          }
          
          if (millis() - lastContact > autoDelay) {
          // we waited long enough for a command, start auto state
            state = 0;
          }         
          
        } else {
          state = 2;
        }
        
        if (state==0) {
          
              for(int i=0; i< CHANNEL_NUM; i++) {
      
                 tc = i;
       
                 //setAirPressure(i, 100);
                 closeWater(tc); 
                 openAir(tc);
                 delay(400 + random(2000));
                 closeAir(tc);
                 openWater(tc);
                 delay(400 + random(2000));
       
       
             }
        
          
        } else if (state == 2) {
          
         int c;    
         //while(!Serial.available());    
         c = Serial.read();
        
         if (c!='c' && c!='p' && c!='s' && c!='a' && c!='w') {
             value = c;
         } else {
            if (c=='c') {
                channel = value;
                //Serial.println("Set channel to " + String(value));
             } else if (c=='p') {
                setAirPressure(channel, value);
                //Serial.println("Set air pressure to " + String(value));
             } else if (c=='s') {
                setWaterPressure(channel, value);
                //Serial.println("Set water pressure to " + String(value));
             } else if (c=='a') {
                if (value==1) {
                  openAir(channel);
                  //Serial.println("Open air valve");
                } else if (value == 0) {
                  closeAir(channel);
                  //Serial.println("Close air valve");
                }
             } else if (c=='w') {
                if (value==1) {
                  openWater(channel);
                  
                  //Serial.println("Open water valve");
                } else if (value == 0) {
                  closeWater(channel);
                  //Serial.println("Close water valve");
                }
             }
             
             value = 0;
        }
    }
  }    
}
