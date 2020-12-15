const int voltageSensor = A0;

float vOUT = 0.0;
float vIN = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int value = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(D12, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  value = analogRead(voltageSensor);
  vOUT = (value * 5.0) / 1024.0;
  vIN = vOUT / (R2/(R1+R2));
  Serial.print("Input = ");
  Serial.println(vIN);
  if (vIN > 1.9){
    digitalWrite(12, HIGH);
    delay(1000);
    digitalWrite(12, LOW);
  }
}
