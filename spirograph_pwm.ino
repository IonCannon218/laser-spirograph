// set up pins
int motor1Pin = 3;
int motor1Val = 0;
int motor2Pin = 9;
int motor2Val = 0;
int motor3Pin = 10;
int motor3Val = 0;

int laserPin = 13;

int delta = 5;      //delta limit for randomizer
int minSpeed = 50;   // min PWM limit for motors
int maxSpeed = 255;   // max PWM limit for motors
int dmin, dmax;

void printvalues() {
	 // print values to serial
	Serial.print(motor1Val);
	Serial.print(", ");
	Serial.print(motor2Val);
	Serial.print(", ");
	Serial.println(motor3Val);
}

void setup() {
  Serial.begin(9600);
  
  Serial.println("Starting up");
  
  // set up pwm pin outputs
  pinMode(motor1Pin, OUTPUT);
  pinMode(motor2Pin, OUTPUT);
  pinMode(motor3Pin, OUTPUT);
  pinMode(laserPin, OUTPUT);
  
  // turn on laser
  digitalWrite(laserPin, HIGH);
  
  /*// spin up motors
  int startSpeed = 30;
  analogWrite(motor1Pin, startSpeed);
  delay(1000);
  analogWrite(motor2Pin, startSpeed);
  delay(1000);
  analogWrite(motor3Pin, startSpeed);
  delay(3000);*/
  
  // delay motor start up a little
  delay(1000);
  
  // spin up motors
  int delayms = 50;
  for (motor1Val = minSpeed; motor1Val < maxSpeed; motor1Val++) {
	  analogWrite(motor1Pin, motor1Val);
	  printvalues();
	  delay(delayms);
  }
  for (motor2Val = minSpeed; motor2Val < maxSpeed; motor2Val++) {
	  analogWrite(motor2Pin, motor2Val);
	  printvalues();
	  delay(delayms);
  }
  for (motor3Val = minSpeed; motor3Val < maxSpeed; motor3Val++) {
	  analogWrite(motor3Pin, motor3Val);
	  printvalues();
	  delay(delayms);
  }
  
  // set up random seed
  randomSeed(analogRead(0));
  
  // spin down motor to random speed
  Serial.println("Spinning down to random number");
  int randSpeed = random(minSpeed, maxSpeed);
  for (motor1Val = maxSpeed; motor1Val > randSpeed; motor1Val--) {
	  analogWrite(motor1Pin, motor1Val);
	  printvalues();
  }
  
  randSpeed = random(minSpeed, maxSpeed);
  for (motor2Val = maxSpeed; motor2Val > randSpeed; motor2Val--) {
	  analogWrite(motor2Pin, motor2Val);
	  printvalues();
  }
  
  randSpeed = random(minSpeed, maxSpeed);
  for (motor3Val = maxSpeed; motor3Val > randSpeed; motor3Val--) {
	  analogWrite(motor3Pin, motor3Val);
	  printvalues();
  }
  
  Serial.println("Holding for 5 seconds");
  delay(5000);
 
  Serial.println("Starting loop()");
}

void loop() {
  // turn off laser while changing motor speed
  digitalWrite(laserPin, LOW);
	
  // randomly change speed
  dmin = motor1Val - delta;
  dmin = max(dmin, minSpeed);
  dmax = motor1Val + delta;
  dmax = min(dmax, maxSpeed);
  motor1Val = random(dmin, dmax);
  
  dmin = motor2Val - delta;
  dmin = max(dmin, minSpeed);
  dmax = motor2Val + delta;
  dmax = min(dmax, maxSpeed);
  motor2Val = random(dmin, dmax);
  
  dmin = motor3Val - delta;
  dmin = max(dmin, minSpeed);
  dmax = motor3Val + delta;
  dmax = min(dmax, maxSpeed);
  motor3Val = random(dmin, dmax);
  
  // output to motors
  analogWrite(motor1Pin, motor1Val);
  analogWrite(motor2Pin, motor2Val);
  analogWrite(motor3Pin, motor3Val);
  
  // print values to serial
  printvalues();
  
  // code above executes too fast, add a delay
  delay(50);
  
  // turn laser back on
  digitalWrite(laserPin, HIGH);
  
  delay(500);
}

/*
// This interrupt is called every time timer0 counts up to the 8bit value
// stored in the register "ORC0A", which is configured in INT0 interrupt.
ISR(TIMER0_COMPA_vect) {
	// turn laser off
	if (laserOn == true) {
		laserOn = false;
		digitalWrite(laserPin, LOW);
		
		// Reset timer0
		TCNT0 = 0;
	} 
	
	// turn laser on
	if (laserOn == false) {
		laserOn = true;
		digitalWrite(laserPin, HIGH);
		
		// Reset timer0
		TCNT0 = 0;
	}
}*/