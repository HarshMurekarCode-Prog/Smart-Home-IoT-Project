const int outputPin = 7;
const int inputPin = A0;

void setup() {
  Serial.begin(9600);

  pinMode(outputPin, OUTPUT);
  digitalWrite(outputPin, LOW);   // Drive LOW

  pinMode(inputPin, INPUT_PULLUP); // Internal pull-up
}

void loop() {
  if (digitalRead(inputPin) == LOW) {
    Serial.println("OK");
  } else {
    Serial.println("BROKEN");
  }

  delay(500);
}