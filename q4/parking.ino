/* Smart parking indicator
   Ultrasonic sensor -> Arduino Uno -> green LED, red LED, buzzer */

/* pin numbers */
int trigPin = 9;
int echoPin = 10;
int greenLed = 3;
int redLed = 4;
int buzzer = 5;

/* a car closer than this (in cm) means the space is occupied */
int threshold = 50;

long duration;
int distance;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  /* 1. send a short 10 microsecond pulse from the trig pin */
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  /* 2. measure how long the echo takes to come back (microseconds) */
  duration = pulseIn(echoPin, HIGH);

  /* 3. turn the time into cm: sound moves 0.034 cm per microsecond,
     and the sound goes to the car and back, so divide by 2 */
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  /* 4. decide and control the outputs */
  if (distance < threshold)
  {
    /* car detected: space occupied */
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    tone(buzzer, 1000);
    Serial.println("Status: OCCUPIED");
  }
  else
  {
    /* no car: space available */
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
    noTone(buzzer);
    Serial.println("Status: AVAILABLE");
  }

  delay(500);
}
