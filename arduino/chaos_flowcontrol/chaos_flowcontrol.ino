int incomingByte = 0;   // for incoming serial data

int state = 2; //0 = auto 1 = pending 2 = controlled
long autoDelay = 400;
long lastContact = 0;

int channels [3];

float waterPressure [];

// syntax
// 2 W 1.0 


void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
        
        
        
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
