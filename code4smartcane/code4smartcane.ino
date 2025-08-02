#include <BluetoothSerial.h>
#include <Wire.h>
#include <MPU6050.h>

BluetoothSerial SerialBT;
MPU6050 mpu;

const int trigPin = 13;
const int echoPin = 12;
const int buzzerPin = 27;
const int vibrationPin = 26;

long duration;
int distance;
bool fallDetected = false;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("SmartCane_BT");  // Bluetooth device name

  Wire.begin();
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
  }

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(vibrationPin, OUTPUT);

  Serial.println("Smart Cane Initialized");
}

void loop() {
  checkObstacle();
  checkFall();
}

void checkObstacle() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  if (distance > 0 && distance < 40) {
    digitalWrite(vibrationPin, HIGH);
    delay(200);
    digitalWrite(vibrationPin, LOW);
  }
}

void checkFall() {
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  float accTotal = sqrt(ax * ax + ay * ay + az * az) / 16384.0;

  if (accTotal < 0.4 && !fallDetected) {
    fallDetected = true;
    sendSOS();
    buzzFall();
  }

  if (accTotal >= 0.4) {
    fallDetected = false;
  }
}

void buzzFall() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(buzzerPin, HIGH);
    delay(300);
    digitalWrite(buzzerPin, LOW);
    delay(300);
  }
}

void sendSOS() {
  SerialBT.println("⚠️ SOS! Fall detected from the smart cane!");
  Serial.println("SOS sent via ESP32 Bluetooth");
}
