#include <DHT.h>

// ---------- DHT11 ----------
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const float TEMP_THRESHOLD = 30.0;
const int BUZZER_PIN = 7;

// ---------- Soil Moisture ----------
#define SOIL_PIN A0
#define RELAY_PIN 8
const int SOIL_THRESHOLD = 600;

// ---------- Ultrasonic ----------
const int TRIG_PIN = 3;
const int ECHO_PIN = 4;

long duration;
float distance;

void setup() {
  Serial.begin(9600);

  dht.begin();

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);   // Relay OFF (Active LOW)

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {

  // ---------- Temperature ----------
  float temp = dht.readTemperature();
  bool tempHigh = (!isnan(temp) && temp > TEMP_THRESHOLD);

  // ---------- Soil ----------
  int soil = analogRead(SOIL_PIN);
  bool soilDry = soil > SOIL_THRESHOLD;

  // Relay ON when soil is dry
  digitalWrite(RELAY_PIN, soilDry ? LOW : HIGH);

  // ---------- Ultrasonic ----------
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0)
    distance = -1;
  else
    distance = duration * 0.0343 / 2;

  bool broken = (distance >= 0 && distance < 10);

  // ---------- Buzzer ----------
  // ON if temperature is high OR object is too close
  digitalWrite(BUZZER_PIN, (tempHigh || broken) ? HIGH : LOW);

  // ---------- JSON Output ----------
  Serial.print("{\"temp\":");

  if (isnan(temp))
    Serial.print("null");
  else
    Serial.print(temp, 1);

  Serial.print(",\"temp_status\":\"");
  Serial.print(tempHigh ? "HIGH" : "NORMAL");

  Serial.print("\",\"soil\":");
  Serial.print(soil);

  Serial.print(",\"soil_status\":\"");
  Serial.print(soilDry ? "DRY" : "WET");

  Serial.print("\",\"distance\":");

  if (distance < 0)
    Serial.print("null");
  else
    Serial.print(distance, 1);

  Serial.print(",\"distance_status\":\"");

  if (distance < 0)
    Serial.print("OUT");
  else
    Serial.print(broken ? "BROKE" : "OK");

  Serial.println("\"}");

  delay(2000);
}