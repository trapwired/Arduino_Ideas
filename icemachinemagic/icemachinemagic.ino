    unsigned long fill_t = 35000;        //in ms
    unsigned long pre_cool_t = 900000;  //in ms
    unsigned long flush_t = 25000;        //in ms
    unsigned long build_cubes_t = 900000;  //in ms
    unsigned long time_now = 0;
    
    void setup() {
      //PIN 3 = Signal for Relay
      //PIN 13 = LED
      pinMode(3, OUTPUT);
      pinMode(13, OUTPUT);
      //Serial.begin(9600);

      time_now = millis();    
      
      // Fill with water
      digitalWrite(3, HIGH);   
      digitalWrite(13,HIGH);

      while(millis() < time_now + fill_t){
        //let us wait
      }
      
      time_now = millis();
      // Pre-Cooling
      digitalWrite(3, LOW);    
      digitalWrite(13, LOW);
         
      while(millis() < time_now + pre_cool_t){
        //let us wait
      }
    }
     
    // the loop function runs over and over again forever
    void loop() {
      time_now = millis();    
      
      //Spülen / fresh water
      digitalWrite(3, HIGH);   
      digitalWrite(13,HIGH);

      while(millis() < time_now + flush_t){
        //let us wait
        //Serial.println(time_now + flush_t - millis());
      }
      
      time_now = millis();
      //lets make some ice
      digitalWrite(3, LOW);    
      digitalWrite(13, LOW);
         
      while(millis() < time_now + build_cubes_t){
        //let us wait
      }         
    }
