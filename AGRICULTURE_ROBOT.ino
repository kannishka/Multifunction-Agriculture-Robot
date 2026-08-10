#include <Servo.h>

Servo sprinkler;  // Servo for water spraying (now on pin 8)

char command;

void setup() {
  Serial.begin(9600);
  sprinkler.attach(7);       // Sprinkler servo to pin 8
  sprinkler.write(30);        // Initial position

  // Motor pins for L293D (movement)
  pinMode(2, OUTPUT);  // IN1
  pinMode(3, OUTPUT);  // IN2
  pinMode(4, OUTPUT);  // IN3
  pinMode(5, OUTPUT);  // IN4

  // Water Pump (via relay or MOSFET)
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);      // Start with pump OFF

  // Grass cutting motor
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);     // Cutter OFF initially (LOW = ON)
}

void loop() {
  if (Serial.available()) {
    command = Serial.read();
    Serial.print("Received: ");
    Serial.println(command);

    if (command == 'F') forward();
    else if (command == 'B') backward();
    else if (command == 'L') left();
    else if (command == 'R') right();
    else if (command == 'S') stopCar();
    else if (command == 'W') rotateSprinkler();  // Servo spray
    else if (command == 'C') cutterOn();         // Cutter ON
    else if (command == 'O') cutterOff();        // Cutter OFF
    else if (command == 'P') pumpOn();           // Pump ON
    else if (command == 'Q') pumpOff();          // Pump OFF
  }
}

// Movement functions
void forward() {
  digitalWrite(2, HIGH); digitalWrite(3, LOW);
  digitalWrite(4, HIGH); digitalWrite(5, LOW);
}

void backward() {
  digitalWrite(2, LOW); digitalWrite(3, HIGH);
  digitalWrite(4, LOW); digitalWrite(5, HIGH);
}

void left() {
  digitalWrite(2, LOW); digitalWrite(3, HIGH);
  digitalWrite(4, HIGH); digitalWrite(5, LOW);
}

void right() {
  digitalWrite(2, HIGH); digitalWrite(3, LOW);
  digitalWrite(4, LOW); digitalWrite(5, HIGH);
}

void stopCar() {
  digitalWrite(2, LOW); digitalWrite(3, LOW);
  digitalWrite(4, LOW); digitalWrite(5, LOW);
}

// Sprinkler Servo sweep
void rotateSprinkler() {
  Serial.println("Starting sprinkler rotation...");
  for (int pos = 30; pos <= 120; pos += 10) {
    sprinkler.write(pos);
    void pumpOn();
    delay(10);
  }
  delay(500);
  for (int pos = 120; pos >= 30; pos -= 10) {
    sprinkler.write(pos);
    void pumpOn();
    delay(10);
  }
  sprinkler.write(0);
  Serial.println("Sprinkler rotation complete.");
}

// Cutter control
void cutterOn() {
  digitalWrite(9, HIGH);  // Cutter motor ON (depends on wiring)
  Serial.println("Grass cutter ON");
}

void cutterOff() {
  digitalWrite(9, LOW); // Cutter motor OFF
  Serial.println("Grass cutter OFF");
}

// Pump control
void pumpOn() {
  digitalWrite(6, HIGH); // Relay ON
  Serial.println("Pump ON");
}

void pumpOff() {
  digitalWrite(6, LOW);  // Relay OFF
  Serial.println("Pump OFF");
}
