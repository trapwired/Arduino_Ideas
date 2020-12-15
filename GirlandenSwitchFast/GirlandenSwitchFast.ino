int acPin = 9;
 int virgrd = 10;
 double val = 0 ;
 int freq = 50;
 double t = 0;
const double pi = 3.1415;
 const double fs=900;

void setup() {

pinMode(acPin, OUTPUT);

}

void loop(){
  t = millis();
  val = 127*sin(2*pi*(freq/fs)*t)+127;
  analogWrite(acPin,val);
  analogWrite(virgrd,127);

}
