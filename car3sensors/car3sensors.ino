// ================= ULTRASONIC SENSOR PINS =================
#define TRIG_LEFT   10
#define ECHO_LEFT   13

#define TRIG_CENTER 9
#define ECHO_CENTER 8

#define TRIG_RIGHT  7
#define ECHO_RIGHT  6

// ================= MOTOR DRIVER PINS (L293D) =================
#define M1_IN1 2
#define M1_IN2 3
#define M2_IN3 4
#define M2_IN4 5

// ================= VARIABLES =================
long distLeft, distCenter, distRight;

// ================= FUNCTION TO READ DISTANCE =================
long readDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 25000); // timeout
  if (duration == 0) return 100;                 // no object
  return duration * 0.034 / 2;
}

// ================= SETUP =================
void setup() {
  Serial.begin(9600);

  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);

  pinMode(TRIG_CENTER, OUTPUT);
  pinMode(ECHO_CENTER, INPUT);

  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);

  pinMode(M1_IN1, OUTPUT);
  pinMode(M1_IN2, OUTPUT);
  pinMode(M2_IN3, OUTPUT);
  pinMode(M2_IN4, OUTPUT);

  stopMotors();
}

// ================= LOOP =================
void loop() {
  distLeft   = readDistance(TRIG_LEFT, ECHO_LEFT);
  distCenter = readDistance(TRIG_CENTER, ECHO_CENTER);
  distRight  = readDistance(TRIG_RIGHT, ECHO_RIGHT);

  Serial.println("Distances (Left  Center  Right):");
  Serial.print(distLeft); Serial.print("   ");
  Serial.print(distCenter); Serial.print("   ");
  Serial.println(distRight);

  if (distCenter > 40) {
    moveForward();
    Serial.println("MOVE FORWARD");
  }
  else if (distLeft > distRight && distLeft > 40) {
    turnLeft();
    Serial.println("TURN LEFT");
    delay(500);
  }
  else if (distRight > 40) {
    turnRight();
    Serial.println("TURN RIGHT");
    delay(500);
  }
  else {
    stopMotors();
    Serial.println("STOP");
  }

  Serial.println("--------------------------------");
  delay(300);
}

// ================= MOTOR FUNCTIONS =================
void moveForward() {
  digitalWrite(M1_IN1, HIGH);
  digitalWrite(M1_IN2, LOW);
  digitalWrite(M2_IN3, HIGH);
  digitalWrite(M2_IN4, LOW);
}

void turnLeft() {
  digitalWrite(M1_IN1, LOW);
  digitalWrite(M1_IN2, HIGH);
  digitalWrite(M2_IN3, HIGH);
  digitalWrite(M2_IN4, LOW);
}

void turnRight() {
  digitalWrite(M1_IN1, HIGH);
  digitalWrite(M1_IN2, LOW);
  digitalWrite(M2_IN3, LOW);
  digitalWrite(M2_IN4, HIGH);
}

void stopMotors() {
  digitalWrite(M1_IN1, LOW);
  digitalWrite(M1_IN2, LOW);
  digitalWrite(M2_IN3, LOW);
  digitalWrite(M2_IN4, LOW);
}
