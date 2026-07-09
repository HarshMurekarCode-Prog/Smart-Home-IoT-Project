#define SOIL_PIN A0
#define RELAY_PIN 8

// Adjust this value after testing your sensor
const int THRESHOLD = 600;

void setup() {
  Serial.begin(9600);

  pinMode(RELAY_PIN, OUTPUT);

  // Relay OFF (Active LOW)
  digitalWrite(RELAY_PIN, HIGH);
}

void loop() {
  int soilValue = analogRead(SOIL_PIN);

  Serial.print("Soil Moisture Value: ");
  Serial.println(soilValue);

  // Higher value = Drier soil
  if (soilValue > THRESHOLD) {
    digitalWrite(RELAY_PIN, LOW);   // Relay ON
    Serial.println("Soil Dry -> Pump ON");
  }
  else {
    digitalWrite(RELAY_PIN, HIGH);  // Relay OFF
    Serial.println("Soil Wet -> Pump OFF");
  }

  delay(1000);
}