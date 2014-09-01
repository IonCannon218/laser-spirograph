// set up pins
int motor1Pin = 3;
int motor2Pin = 9;
int motor3Pin = 10;
int motor1Val, motor2Val, motor3Val;

int laserPin = 13;
boolean laserOn = 0;
int loopCount = 0;

int delta = 5;      //delta limit for randomizer
int minSpeed = 100;   // min PWM limit for motors
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
  
  // delay motor start up for a second
  delay(1000);
  
  // spin up motors
  int delayms = 50;
  for (motor1Val = minSpeed/2; motor1Val < maxSpeed; motor1Val++) {
	  analogWrite(motor1Pin, motor1Val);
	  printvalues();
	  delay(delayms);
  }
  delay(1000);
  for (motor2Val = minSpeed/2; motor2Val < maxSpeed; motor2Val++) {
	  analogWrite(motor2Pin, motor2Val);
	  printvalues();
	  delay(delayms);
  }
  delay(1000);
  for (motor3Val = minSpeed/2; motor3Val < maxSpeed; motor3Val++) {
	  analogWrite(motor3Pin, motor3Val);
	  printvalues();
	  delay(delayms);
  }
  delay(1000);
  
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
  // save previous speed
  int motor1Old = motor1Val;
  int motor2Old = motor2Val;
  int motor3Old = motor3Val;
  
  // randomly change speed
  motor1Val = random(minSpeed, maxSpeed);
  motor2Val = random(minSpeed, maxSpeed);
  
  // motor 3 on 50% "chance"
  int on = random(0,10);
  if (on <= 5) {
	  motor3Val = random(minSpeed, maxSpeed);
  } else {
	  motor3Val = 0;
  }
  
  /*
  // check if the 3 motor speeds are too close together
  // compare 1 and 2
  int diff = motor1Val - motor2Val;
  diff = abs(diff);
  if (diff >= 10) {
	  // compare 2 and 3
	  diff = motor2Val - motor3Val;
	  diff = abs(diff);
	  if (diff >= 10) {
		  // compare 1 and 3
		  diff = motor1Val - motor3Val;
		  diff = abs(diff);
		  if (diff >= 10) {
			  // output to motors
			  /*analogWrite(motor1Pin, motor1Val);
			  analogWrite(motor2Pin, motor2Val);
			  analogWrite(motor3Pin, motor3Val);
			  
			  
		  }
	  }
  }*/
  
  // sweep towards new speed
  int delayms = 50;
  if (motor1Old < motor1Val) { // motor 1 spin up
	  for(int x = motor1Old; x < motor1Val; x++) {
		analogWrite(motor1Pin, motor1Val);
		Serial.print("1: ");
		Serial.println(x);
		delay(delayms);
	  }
  } else if (motor1Old > motor1Val) { // motor 1 spin down
	  for(int x = motor1Old; x > motor1Val; x--) {
		analogWrite(motor1Pin, motor1Val);
		Serial.print("1: ");
		Serial.println(x);
		delay(delayms);
	  }
  }
  if (motor2Old < motor2Val) { // motor 2 spin up
	  for(int x = motor2Old; x < motor2Val; x++) {
		analogWrite(motor2Pin, motor2Val);
		Serial.print("2: ");
		Serial.println(x);
		delay(delayms);
	  }
  } else if (motor2Old > motor2Val) { // motor 2 spin down
	  for(int x = motor2Old; x > motor2Val; x--) {
		analogWrite(motor2Pin, motor2Val);
		Serial.print("2: ");
		Serial.println(x);
		delay(delayms);
	  }
  }
  if (motor3Old < motor3Val) { // motor 3 spin up
	  for(int x = motor3Old; x < motor3Val; x++) {
		analogWrite(motor3Pin, motor3Val);
		Serial.print("3: ");
		Serial.println(x);
		delay(delayms);
	  }
  } else if (motor3Old > motor3Val) { // motor 3 spin down
	  for(int x = motor3Old; x > motor3Val; x--) {
		analogWrite(motor3Pin, motor3Val);
		Serial.print("3: ");
		Serial.println(x);
		delay(delayms);
		if (x <= 100) { break; } // exit loop when <100
	  }
  }
  
  // print values to serial
  printvalues();
  
  // loop() delay
  delay(10000);
  
  loopCount++;
  // Break after ~1 minute
  if (loopCount > 6) {
	  // turn off laser and motors for break
	  analogWrite(motor1Pin, 0);
      analogWrite(motor2Pin, 0);
	  analogWrite(motor3Pin, 0);
	  digitalWrite(laserPin, LOW);
	  
	  Serial.println("Breaking for 30 seconds");
	  delay(30000); // 30 seconds
	  Serial.println("Resuming");
	  loopCount = 0;
	  
	  // turn laser back on
	  digitalWrite(laserPin, HIGH);
  }
}