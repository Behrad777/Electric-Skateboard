double target;
double speed;
const int pwmPin = 2;
const int brakePin = 5;  

void setup() {
pinMode(4, INPUT);
pinMode(pwmPin, OUTPUT);
pinMode(brakePin, OUTPUT);
Serial.begin(115200);
}

void loop() {
target = pulseIn(4, HIGH) -1458.00;
Serial.print("Zero:");
Serial.println(0);

if(target <= 10.0 && target >= -100.0){
  Serial.println("idle");
  
  speed = speed-5;
  if (speed<0){
    speed=0;
  }
  
  analogWrite(pwmPin,speed);
  
  digitalWrite(brakePin, LOW);  

  Serial.print("Target:");
  Serial.println(target);
  Serial.print("Speed:");
  Serial.println(speed);
  Serial.print("Max:");
  Serial.println(255);
  
}
else if (target < -10.0){
  Serial.println("brake");
  if(speed > 70){
    speed = speed-5;
  }
  else{
  speed=0;
  analogWrite(pwmPin,speed);
  digitalWrite(brakePin, HIGH);
  }
  

  Serial.print("Target:");
  Serial.println(target);
  Serial.print("Speed:");
  Serial.println(speed);
  Serial.print("Max:");
  Serial.println(255);
  
  //activate braking pin
}

else if (target > 10.0){
  digitalWrite(brakePin, LOW);  

  
  target = (target*2)/5;
  Serial.print("Target:");
  Serial.println(target);
  Serial.print("Max:");
  Serial.println(255);

  double diff = abs(target-speed);

  
  if(target > speed){
      speed = speed+(diff/30);
      Serial.print("Speed:");
      Serial.println(round(speed));
  } 
  else if (target < speed){
      speed = speed-(diff/30);
      Serial.print("Speed:");
      Serial.println(round(speed));

  }


}
delay(10);
}
