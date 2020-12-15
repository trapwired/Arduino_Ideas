void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < 10; i++){
    pinMode(i, OUTPUT);
  }
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 1; i < 10; i++){
    digitalWrite(i-1, HIGH);
    digitalWrite(i, LOW);
    delay(100);
  }
}
