const int trigPin = 3;
const int echoPin = 4;

long duration;
float distance;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Clear the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send 10 µs trigger pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo
  duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    Serial.println("Distance: Out of Range");
  } else {
    // Calculate distance (cm)
    distance = duration * 0.0343 / 2;

    // Print current distance
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" cm\t");

    // Print status
    if (distance < 10) {
      Serial.println("BROKE");
    } else {
      Serial.println("OK");
    }
  }

  delay(200);
}