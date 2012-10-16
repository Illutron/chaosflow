#define CHANNEL_NUM 5 

int commandValue = 0;   // for incoming serial data

String inputString;
boolean newCommand = false;

int channel = 0;
int value = 0;

int state = 2; //0 = auto 1 = pending 2 = controlled
long autoDelay = 400;
long lastContact = 0;

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
  
  
    waterValvePins[0] = 1;
    waterValvePins[1] = 2;
    waterValvePins[2] = 3;
    
    airValvePins[0] = 1;
    airValvePins[1] = 2;
    airValvePins[2] = 3;
    
    pumpPins[0] = 1;
    pumpPins[1] = 2;
    pumpPins[2] = 3;
    
    airRegulatorPins[0] = 1;
    airRegulatorPins[1] = 2;
    airRegulatorPins[2] = 3; 
}

char inData[80];
char parsedData[80];
byte index = 0;

void loop() {

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
          //auto control here   
        } else if (state == 2) {
          
        int c;    
        while(!Serial.available());    
        c = Serial.read();
        
        if (c!='c' && c!='p' && c!='s' && c!='a' && c!='w') {
            value = c;
        } else {
            if (c=='c') {
                channel = value;
                Serial.println("Set channel to " + String(value));
             } else if (c=='p') {
                setAirPressure(channel, value);
                Serial.println("Set air pressure to " + String(value));
             } else if (c=='s') {
                setWaterPressure(channel, value);
                Serial.println("Set water pressure to " + String(value));
             } else if (c=='a') {
                if (value==1) {
                  openAir(channel);
                  Serial.println("Open air valve");
                } else if (value == 0) {
                  closeAir(channel);
                  Serial.println("Close air valve");
                }
             } else if (c=='w') {
                if (value==1) {
                  openWater(channel);
                  Serial.println("Open water valve");
                } else if (value == 0) {
                  closeWater(channel);
                  Serial.println("Close water valve");
                }
             }
              
             value = 0;
        }
    }       
}
