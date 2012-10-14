#define CHANNEL_NUM 5 

int incomingByte = 0;   // for incoming serial data

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

void loop() {

        // send data only when you receive data:
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
          
          // read the incoming byte:
          incomingByte = Serial.read();

          // say what you got:
          Serial.print("I received: ");
          Serial.println(incomingByte, DEC);
        }
        
        if (state=0) {
          
          //auto control here
          
        }
        
}
