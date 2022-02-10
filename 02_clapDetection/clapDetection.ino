/*


        _          _ ______ _____ _____ 
       (_)        | |  ____|  __ \_   _|
  _ __  ___  _____| | |__  | |  | || |  
 | '_ \| \ \/ / _ \ |  __| | |  | || |  
 | |_) | |>  <  __/ | |____| |__| || |_ 
 | .__/|_/_/\_\___|_|______|_____/_____|
 | |                                    
 |_|                                    
                             
www.pixeledi.eu | twitter.com/pixeledi
Simple Clapping detection | V1.0 | 02/2022

*/

class clap{
  private:
    int soundsensor;
    int led;
    int statusSensor;
    int timeWindowInMS;
    long detectClappingStartMS=0;
    long detectClappingMS=0;
    int clapCounter=0;
    
  public:
  clap(int soundpin, int ledpin){
    soundsensor=soundpin;
    led=ledpin;
  }
  void setup(){
    pinMode(soundsensor,INPUT);
    pinMode(led,OUTPUT);
  }

  void readSensorState(){
    //analogsensor must add logic for threshold
    statusSensor = digitalRead(soundsensor);
  }

  void detectClapping(int timeWindow){
    timeWindowInMS=timeWindow;
    readSensorState();

    if(statusSensor==1){
      if(clapCounter==0){
        detectClappingStartMS = detectClappingMS = millis();
        clapCounter++;
      }
      else if(clapCounter>0 && (millis() - detectClappingMS >= 50)){
        detectClappingMS=millis();
        clapCounter++;
        Serial.println("clapped");
      } 
    }

    checkTimeWindow();

  }

  void checkTimeWindow(){
  
    if(millis() - detectClappingStartMS >= timeWindowInMS){
      if(clapCounter==2){
        //toggle LED
          digitalWrite(led,!digitalRead(led));
      }
      clapCounter=0;
    }
  }


};

//sensor, led
clap clapping(27,25);
clap clapping2(27,26);

void setup(){
  Serial.begin(115200);
  clapping.setup();  
  clapping2.setup();  
}
void loop(){
  clapping.detectClapping(500);
  clapping2.detectClapping(1000);
}
