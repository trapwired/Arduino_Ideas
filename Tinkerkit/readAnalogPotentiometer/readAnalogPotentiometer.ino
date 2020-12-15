void setup() {
  // put your setup code here, to run once:
  pinMode(A3, INPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int x = analogRead(A3);
  Serial.print("Analog value: ");
  Serial.println(x);
  digitalWrite(12, HIGH);
  delay(x);
  digitalWrite(12, LOW);
  delay(x);
}
