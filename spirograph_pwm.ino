// set up motor pins
int motor1Pin = 3;
int motor1Val = 255;
int motor2Pin = 9;
int motor2Val = 255;
int motor3Pin = 10;
int motor3Val = 255;
int motor4Pin = 11;
int motor4Val = 255;

int delta = 5;      //delta limit for randomizer
int minSpeed = 10;   // min PWM limit for motors
int maxSpeed = 40;   // max PWM limit for motors
int dmin, dmax;

void setup() {
  Serial.begin(115200);
  
  Serial.println("Starting up");
  
  // set up pwm pin outputs
  pinMode(motor1Pin, OUTPUT);
  pinMode(motor2Pin, OUTPUT);
  pinMode(motor3Pin, OUTPUT);
  pinMode(motor4Pin, OUTPUT);
  
  // spin up motors
  int startSpeed = 30;
  analogWrite(motor1Pin, startSpeed);
  //delay(3000);
  analogWrite(motor2Pin, startSpeed);
  //delay(3000);
  analogWrite(motor3Pin, startSpeed);
  //delay(3000);
  analogWrite(motor4Pin, startSpeed);
  delay(3000);
  
  // set up random seed
  randomSeed(analogRead(0));
  
  // randomize speed
  motor1Val = random(minSpeed, maxSpeed);
  motor2Val = random(minSpeed, maxSpeed);
  motor3Val = random(minSpeed, maxSpeed);
  motor4Val = random(minSpeed, maxSpeed);
 
}

/*
void loop() {
  for (motor1Val = maxSpeed; motor1Val < minSpeed; motor1Val--) {
    analogWrite(motor1Pin, motor1Val);
  }
  
  for (motor2Val = maxSpeed; motor2Val < minSpeed; motor2Val--) {
    analogWrite(motor2Pin, motor2Val);
  }
  
  for (motor3Val = maxSpeed; motor3Val < minSpeed; motor3Val--) {
    analogWrite(motor1Pin, motor3Val);
  }
        
  for (motor4Val = maxSpeed; motor4Val < minSpeed; motor4Val--) {
    analogWrite(motor1Pin, motor4Val);
  }
  
  // print values to serial
  Serial.print(motor1Val);
  Serial.print(", ");
  Serial.print(motor2Val);
  Serial.print(", ");
  Serial.print(motor3Val);
  Serial.print(", ");
  Serial.println(motor4Val);
  delay(1000);
}*/


void loop() {
  // randomly change speed
  dmin = min(motor1Val - delta, minSpeed);
  dmax = max(motor1Val + delta, maxSpeed);
  motor1Val = random(dmin, dmax);
  
  dmin = min(motor2Val - delta, minSpeed);
  dmax = max(motor2Val + delta, maxSpeed);
  motor2Val = random(dmin, dmax);
  
  dmin = min(motor3Val - delta, minSpeed);
  dmax = max(motor3Val + delta, maxSpeed);
  motor3Val = random(dmin, dmax);
  
  dmin = min(motor4Val - delta, minSpeed);
  dmax = max(motor4Val + delta, maxSpeed);
  motor4Val = random(dmin, dmax);
  
  // output to motors
  analogWrite(motor1Pin, motor1Val);
  analogWrite(motor2Pin, motor2Val);
  analogWrite(motor3Pin, motor3Val);
  analogWrite(motor4Pin, motor4Val);
  // print values to serial
  Serial.print(motor1Val);
  Serial.print(", ");
  Serial.print(motor2Val);
  Serial.print(", ");
  Serial.print(motor3Val);
  Serial.print(", ");
  Serial.println(motor4Val);
  
  delay(30000);
}
