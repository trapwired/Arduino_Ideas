/*
Simple switching program for the EL-Sequencer
8 Channels are turned on and of at random, after rand(5,25) seconds, there is an update
no two channels are lit at the same time to save battery
*/
const int CHANNELS_SIZE = 8;          // channels on EL Sequencer

unsigned long next_update = 0;        // next update
int channels_open = 0;                // number of open channels, not zero elements in active_channels

int active_channels[CHANNELS_SIZE];   // list of open channels, for loop

// TUNABLES
int el_delay = 3;                     // [ms] - how long one watermelon stays on
int min_wait = 5;                     // [s] - how long to wait at least before updating lights
int max_wait = 25;                    // [s] - how long to wait at max before updating lights
// Setup
void setup() {                
  // The EL channels are on pins 2 through 9 on the ATMega328
  // Initialize the pins as outputs
  pinMode(2, OUTPUT);  // channel A  
  pinMode(3, OUTPUT);  // channel B   
  pinMode(4, OUTPUT);  // channel C
  pinMode(5, OUTPUT);  // channel D    
  pinMode(6, OUTPUT);  // channel E
  pinMode(7, OUTPUT);  // channel F
  pinMode(8, OUTPUT);  // channel G
  pinMode(9, OUTPUT);  // channel H

  //Pin 13 is the status LED
  pinMode(13, OUTPUT);   
  
  // init next_update 
  next_update = millis() + 1000;
  
  // init random element
  randomSeed(millis()); //or 
  // randomSeed(analogRead(0));
}


// Main Loop
void loop() {
  // Part 1: Update which channels open, if delay() over
  if (next_update < millis()) {
    // get random 8 bits
    int rand_temp = 0;
    channels_open = 0;
    int pointer = 0;
    for (int i = 2; i < CHANNELS_SIZE+2; i++) {
      rand_temp = random(0,2);
      if(rand_temp){
        channels_open++;
        active_channels[pointer] = i;
        pointer++;
      }
    }
    // update next_update as rand(5,25) + millis()
    unsigned long temp = random(min_wait,max_wait+1) * 1000;
    next_update = millis() + temp;  
  }
  
  // Part 2: Let there be light: loop through channels that are active
  for (int i = 0; i < channels_open; i++) {
    digitalWrite(active_channels[i], HIGH);
    delay(el_delay);
    digitalWrite(active_channels[i], LOW);
  }
  
  // digitalWrite(13, status);   // status LEDs
}
