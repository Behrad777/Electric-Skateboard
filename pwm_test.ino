double target;

void setup() {
pinMode(2, OUTPUT);
pinMode(4, INPUT);

Serial.begin(115200);

}

void loop() {

target = pulseIn(4, HIGH) -1458.00;

if(target>20){
  target = int (target);
  Serial.println(target);
  analogWrite(2, target*0.2);
}
else{
  analogWrite(2,0);
}

}
