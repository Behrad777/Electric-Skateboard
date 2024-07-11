double target;
double current_speed =0;


void setup() {
pinMode(2, OUTPUT);
pinMode(4, INPUT);

Serial.begin(115200);

}

void loop() {

target = pulseIn(4, HIGH) -1458.00;
target = int (target);

if(target>current_speed){

  //determining step amount
  current_speed += (target-current_speed)*0.025;
}
 else if (target< -200){
  current_speed=0;
}

else
 {
  current_speed -= (current_speed-target)*0.025;
}
analogWrite(2,current_speed/2.5);



Serial.print("Target: ");
Serial.println(target/2.5);
Serial.print("Current speed: ");
Serial.println( int (current_speed/2.5));

}
