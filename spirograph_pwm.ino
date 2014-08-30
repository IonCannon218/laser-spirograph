/*#ifndef F_CPU
#define F_CPU           16000000UL  // 16 MHz
#endif

#include                <avr/interrupt.h>

// The timers are configured with the prescaler set to 8, which means every
// 8 clock cycles equals on tick on the counter.  This is a constant to help
// convert timer cycles back to real time.
#define FREQ_DIV_8      (F_CPU / 8)

// Defines how many ticks a millisecond equals on our clock
#define MILLITICK       (FREQ_DIV_8 * .001)

// Helper macros for frobbing bits
#define bitset(var,bitno) ((var) |= (1 << (bitno)))
#define bitclr(var,bitno) ((var) &= ~(1 << (bitno)))
#define bittst(var,bitno) (var& (1 << (bitno)))*/

// set up pins
int motor1Pin = 3;
int motor1Val = 0;
int motor2Pin = 9;
int motor2Val = 0;
int motor3Pin = 10;
int motor3Val = 0;

int laserPin = 13;
boolean laserOn = 0;

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

  // disable global interrupts
  /*cli();
	
  // set timer1 interrupt at 1Hz
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1  = 0; //initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624; // = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  
  // enable global interrupts
  sei();*/
  
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
  // turn on laser
  digitalWrite(laserPin, HIGH);
  
  // randomly change speed
  /*dmin = motor1Val - delta;
  dmin = max(dmin, minSpeed);
  dmax = motor1Val + delta;
  dmax = min(dmax, maxSpeed);
  motor1Val = random(dmin, dmax);*/
  motor1Val = random(minSpeed, maxSpeed);
  
  /*dmin = motor2Val - delta;
  dmin = max(dmin, minSpeed);
  dmax = motor2Val + delta;
  dmax = min(dmax, maxSpeed);
  motor2Val = random(dmin, dmax);*/
  motor2Val = random(minSpeed, maxSpeed);
  
  /*dmin = motor3Val - delta;
  dmin = max(dmin, minSpeed);
  dmax = motor3Val + delta;
  dmax = min(dmax, maxSpeed);
  motor3Val = random(dmin, dmax);*/
  
  // motor 3 on 20% "chance"
  int on = random(0,10);
  if (on <= 2) {
	  motor3Val = random(minSpeed, maxSpeed);
  } else {
	  motor3Val = 0;
  }
  
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
			  analogWrite(motor1Pin, motor1Val);
			  analogWrite(motor2Pin, motor2Val);
			  analogWrite(motor3Pin, motor3Val);
		  }
	  }
  }
  
  // print values to serial
  printvalues();
  
  // loop() delay
  delay(5000);
  
  // turn laser off
  digitalWrite(laserPin, LOW);
  delay(1000);
}


// This interrupt is called every time timer1 counts up to the 16 bit value
/*ISR(TIMER1_COMPA_vect) {
	// turn laser off
	if (laserOn == 1) {
		laserOn = 0;
		digitalWrite(laserPin, LOW);
	} 
	
	// turn laser on
	if (laserOn == 0) {
		laserOn = 1;
		digitalWrite(laserPin, HIGH);
	}
}*/