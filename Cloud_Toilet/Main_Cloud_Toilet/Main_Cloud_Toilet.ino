// color swirl! connect an RGB LED to the PWM pins as indicated
// in the #defines

/* Cloud-Toilet 
 *  Main-LED Strip (5m) MAIN
 *  Accent-LED Strip (2x 3'cm): ACC
 *  Lightning Strips (10cm, only white): lightning
 */

// Pins
#define MAIN_R 3
#define MAIN_G 3
#define MAIN_B 6
#define ACC_R 9
#define ACC_G 10
#define ACC_B 11

// Parameters
#define RED 0
#define GREEN 1
#define BLUE 2
#define MAIN 0
#define ACC 1
int* lightning[6] = {2, 4, 7, 8, 12, 13};
int* current_main[3] = {0, 0, 0};
int* current_accent[3] = {0, 0, 0};

// Colors
int white[3] = {255, 255, 255};
int black[3] = {0, 0, 0};
int red[3] = {255, 0 , 0};
int green[3] = {0, 255, 0};
int blue[3] = {0, 0, 255};
int light_violet[3] = {173, 149, 173};
int brown_orange[3] = {140, 110, 102};
int lighter_blue[3] = {199, 214, 255};
int light_blue[3] = {109, 127, 177};
int blue_gray[3] = {73, 96, 148};
int dark_blue[3] = {40, 63, 107};
int yellow[3] = {252, 186, 3};

long randNumber;

void setup() {
  Serial.begin(9600);

  // Setup pins
  pinMode(MAIN_R, OUTPUT);
  pinMode(MAIN_G, OUTPUT);
  pinMode(MAIN_B, OUTPUT);
  pinMode(ACC_R, OUTPUT);
  pinMode(ACC_G, OUTPUT);
  pinMode(ACC_B, OUTPUT);
  pinMode(lightning[0], OUTPUT);
  pinMode(lightning[1], OUTPUT);
  pinMode(lightning[2], OUTPUT);
  pinMode(lightning[3], OUTPUT);
  pinMode(lightning[4], OUTPUT);
  pinMode(lightning[5], OUTPUT);
}

void set_main(int* color){
  analogWrite(MAIN_R, color[RED]);
  current_main[RED] = color[RED];
  analogWrite(MAIN_G, color[GREEN]);
  current_main[GREEN] = color[GREEN];
  analogWrite(MAIN_B, color[BLUE]);
  current_main[BLUE] = color[BLUE];
}

void set_accent(int* color) {
  analogWrite(ACC_R, color[RED]);
  current_accent[RED] = color[RED];
  analogWrite(ACC_G, color[GREEN]);
  current_accent[GREEN] = color[GREEN];
  analogWrite(ACC_B, color[BLUE]);
  current_accent[BLUE] = color[BLUE];
}

void normal_lightning_wave(int min_delay, int small_change, bool backward = false){
  if (backward) {
    digitalWrite(lightning[0], HIGH);
    for (int i = 1; i < 6; ++i) {
      delay(min_delay + random(small_change));
      digitalWrite(lightning[i], HIGH);
      digitalWrite(lightning[i-1], LOW);
    }
    delay(min_delay + random(small_change));
    digitalWrite(lightning[5], LOW);
  } else {
    digitalWrite(lightning[5], HIGH);
    for (int i = 5; i >= 0; --i) {
      delay(min_delay + random(small_change));
      digitalWrite(lightning[i], HIGH);
      digitalWrite(lightning[i+1], LOW);
    }
    delay(min_delay + random(small_change));
    digitalWrite(lightning[0], LOW);
  }
}

void inward_lightning_wave(int min_delay, int small_change) {
  digitalWrite(lightning[0], HIGH);
  delay(min_delay + random(small_change));
  digitalWrite(lightning[1], HIGH);
  digitalWrite(lightning[0], LOW);
  delay(min_delay + random(small_change));
  digitalWrite(lightning[2], HIGH);
  digitalWrite(lightning[1], LOW);
  delay(min_delay + random(small_change));
  digitalWrite(lightning[3], HIGH);
  digitalWrite(lightning[2], LOW);
  delay(min_delay + random(small_change));
  digitalWrite(lightning[4], HIGH);
  digitalWrite(lightning[3], LOW);
  delay(min_delay + random(small_change));
  digitalWrite(lightning[5], HIGH);
  digitalWrite(lightning[4], LOW);
  delay(min_delay + random(small_change));
  digitalWrite(lightning[5], LOW);
}

void fade_to_black(int* target_color, int target) {
  // TODO
}

void fade_to_white(int* target_color, int target) {
  // TODO
}

void crossfade(int* target_color, int target) {
  // TODO
}

void show_config(int val, char* msg) {
  Serial.print("Value: ");
  Serial.print(val);
  Serial.print(" -> ");
  Serial.println(msg);
}

void loop() {
  int val = analogRead(0);    // read the value from the sensor
  if (val >= 0 && val < 256) {
    show_config(val, "Forward lightning");
    normal_lightning_wave(val, 50);
  } else if (val >= 256 && val < 512) {
    show_config(val, "Backward lightning");
    normal_lightning_wave(val - 256, 50, true);
  } else if (val >= 512 && val < 768) {
    show_config(val, "Inward lightning");
    inward_lightning_wave(val - 512, 50);
  } else if (val >= 786 && val < 1024) {
    show_config(val, "Base colors");
    if (val < 850) {
      set_main(white);
      set_accent(light_violet);
    } else if (val >= 850 && val < 950) {
      set_main(blue_gray);
      set_accent(lighter_blue);
    } else if (val >= 950 && val < 1000) {
      set_main(brown_orange);
      set_accent(red);
    } else {
      set_main(green);
      set_accent(blue);
    }
  }
  delay(1000);
}
