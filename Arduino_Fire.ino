#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const int buzzerPin = 7;
const float tempThreshold = 30.0;   // Set temperature limit (°C)

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);
}

void loop() {
  float temperature = dht.readTemperature();

  // Check if reading failed
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT11!");
    delay(2000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  if (temperature > tempThreshold) {
    digitalWrite(buzzerPin, HIGH);
    Serial.println("ALERT: High Temperature! Buzzer ON");
  } else {
    digitalWrite(buzzerPin, LOW);
    Serial.println("Temperature Normal. Buzzer OFF");
  }

  delay(2000);
}