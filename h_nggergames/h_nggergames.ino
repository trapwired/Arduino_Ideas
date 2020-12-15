// pushbutton pin
const int buttonPin1 = 3;
const int buttonPin2 = 5;
const int resetPin = 6;
const int relay1 = 8;
const int relay2 = 12;

void setup(){
  // Set up the inputs:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(resetPin, INPUT);
   
  // Set up the outputs:
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);

  //set relay to high
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH); 
}


void loop(){

  //read the digital state of buttonPins
  int buttonState1 = digitalRead(buttonPin1);
  int buttonState2 = digitalRead(buttonPin2);
  
  if(buttonState1 == LOW){
    digitalWrite(relay1, LOW);
    boolean wait = true;
    while(wait){
      int buttonState = digitalRead(resetPin);
      if(buttonState == LOW){
        wait = false;
      }
    }
    // wait for reset to be released
    wait = true;
    digitalWrite(relay2, LOW);
    // reset: LL BUTTONS LOW
    while(wait){
      int buttonState = digitalRead(resetPin);
      int buttonState1 = digitalRead(buttonState1);
      int buttonState2 = digitalRead(buttonState2);
      if(buttonState == HIGH){
        wait = false;
      }
    }
    // reset both Lights
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
  }
  
  if (buttonState2 == LOW){
    digitalWrite(relay2, LOW);
    boolean wait = true;
    while(wait){
      int buttonState = digitalRead(resetPin);
      if(buttonState == LOW){
        wait = false;
      }
    }
    // wait for reset to be released
    wait = true;
    digitalWrite(relay1, LOW);
    while(wait){
      int buttonState = digitalRead(resetPin);
      if(buttonState == HIGH){
        wait = false;
      }
    }
    // reset both Lights
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
  }

  
  

}
