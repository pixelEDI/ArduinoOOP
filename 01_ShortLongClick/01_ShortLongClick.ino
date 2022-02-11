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
Short/Long Click - One Button - 2 LEDs | V1.0 | 02/2022

*/

class Button{  
    int btnpin;
    int state;
    unsigned long buttonDownMS;
  public:
    Button(int pin){
      btnpin=pin;
    }

    void setup(){
      pinMode(btnpin,INPUT_PULLUP);
      state=HIGH;
    }

    void loop(){
      int prevState=state;
      state=digitalRead(btnpin);

      if (prevState == HIGH && state == LOW) {
        buttonDownMS = millis();
      }
      else if (prevState == LOW && state == HIGH) {
        if(millis() - buttonDownMS < 50) {
          //debounce
        }
        else if(millis() - buttonDownMS < 250){
          Serial.println("short click");
          digitalWrite(12, !digitalRead(12));
        }
        else {
          Serial.println("long click");
          digitalWrite(25, !digitalRead(25));
        }
      }
    }
};

Button btn_led(35);

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  btn_led.setup();
  // FOR TESTING
  pinMode(12, OUTPUT);
  pinMode(25, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  btn_led.loop();
}
