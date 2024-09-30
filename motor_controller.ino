double input = 0.0;    //current speed    
double output = 0.0;   //Pwm value
double target;

bool debug = false;
const int pwmPin = 2;
const int brakePin = 5;  
const int remotePin = 4;
const int hallPin1 = 6;     // Hall sensor 1
const int hallPin2 = 7;     // Hall sensor 2
const int hallPin3 = 8;     // Hall sensor 3

volatile int pulseCount = 0;
unsigned long lastPulseTime = 0;




//-----PID vars----

const double Kp = 2.0;  
const double Ki = 1.0;  
const double Kd = 0.5; 

double error = 0.0;
double previous_error = 0.0;
double integral = 0.0;
double derivative = 0.0;

//time vars
unsigned long lastTime;
double sampleTime = 100.0; // Sample time in milliseconds



void countPulse() {
  pulseCount++;
  lastPulseTime = millis();
}

void setup() {
Serial.begin(115200);
pinMode(remotePin, INPUT);
pinMode(pwmPin, OUTPUT);
pinMode(brakePin, OUTPUT);
pinMode(hallPin1, INPUT_PULLUP);
pinMode(hallPin2, INPUT_PULLUP);
pinMode(hallPin3, INPUT_PULLUP);

  // Attach interrupts to hall sensors
attachInterrupt(digitalPinToInterrupt(hallPin2), countPulse, RISING);
attachInterrupt(digitalPinToInterrupt(hallPin3), countPulse, RISING);
attachInterrupt(digitalPinToInterrupt(hallPin1), countPulse, RISING);

lastTime = millis();

}

void loop() {

unsigned long currentTime = millis();
double elapsedTime = (double)(currentTime - lastTime);


if (elapsedTime >= sampleTime) {
  noInterrupts();
  int pulses = pulseCount;
  pulseCount = 0;
  interrupts();

  double revolutions = pulses / 6.0;
  double rpm = (revolutions / (elapsedTime / 60000.0)); // revolutions per minute
  input = rpm;
  
  target = pulseIn(4, HIGH) -1458.00; //radio receiver pin input

  error = target - input;
  integral += error * (elapsedTime / 1000.0);
  derivative = (error - previous_error) / (elapsedTime / 1000.0);


  output = Kp * error + Ki * integral + Kd * derivative;
  output = constrain(output, 0, 255); // PWM range

  analogWrite(pwmPin, (int)output);


    if(debug){
    Serial.print("Target: ");
    Serial.print(target);
    Serial.print(" RPM | Input: ");
    Serial.print(input);
    Serial.print(" RPM | Output (PWM): ");
    Serial.println((int)output);
    }
    

    previous_error = error;

    lastTime = currentTime;

}
delay(10);
}
