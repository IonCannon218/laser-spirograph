// set up pins
int motor1Pin = 3;
int motor1Val = 255;
int motor2Pin = 9;
int motor2Val = 255;
int motor3Pin = 10;
int motor3Val = 255;

int laserPin = 13;

int delta = 5;      //delta limit for randomizer
int minSpeed = 50;   // min PWM limit for motors
int maxSpeed = 150;   // max PWM limit for motors
int dmin, dmax;

void setup() {
  Serial.begin(9600);
  
  Serial.println("Starting up");
  
  // set up pwm pin outputs
  pinMode(motor1Pin, OUTPUT);
  pinMode(motor2Pin, OUTPUT);
  pinMode(motor3Pin, OUTPUT);
  pinMode(laserPin, OUTPUT);
  
  // spin up motors
  int startSpeed = 30;
  analogWrite(motor1Pin, startSpeed);
  //delay(3000);
  analogWrite(motor2Pin, startSpeed);
  //delay(3000);
  analogWrite(motor3Pin, startSpeed);
  delay(3000);
  
  // set up random seed
  randomSeed(analogRead(0));
  
  // randomize speed
  motor1Val = random(minSpeed, maxSpeed);
  motor2Val = random(minSpeed, maxSpeed);
  motor3Val = random(minSpeed, maxSpeed);
 
}

void loop() {
  // turn off laser while changing motor speed
  digitalWrite(laserPin, LOW);
	
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
  
  // output to motors
  analogWrite(motor1Pin, motor1Val);
  analogWrite(motor2Pin, motor2Val);
  analogWrite(motor3Pin, motor3Val);
  
  // print values to serial
  Serial.print(motor1Val);
  Serial.print(", ");
  Serial.print(motor2Val);
  Serial.print(", ");
  Serial.println(motor3Val);
  
  // code above executes too fast, add a delay
  delay(250);
  
  // turn laser back on
  digitalWrite(laserPin, HIGH);
  
  delay(3000);
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