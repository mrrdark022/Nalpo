#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Servo.h>

Servo yawServo;
Servo pitchServo;

#define YAW_SERVO_PIN 0
#define PITCH_SERVO_PIN 2
#define LED_PIN1 5
#define LED_PIN2 16

int yawAngle = 90;
int pitchAngle = 90;
const int yawCenter = 90;
const int pitchCenter = 90;

const char* ssid = "drk";
const char* password = "password";
WiFiUDP Udp;
const int localPort = 12345;

void setup() {
  Serial.begin(115200);
  yawServo.attach(YAW_SERVO_PIN);
  pitchServo.attach(PITCH_SERVO_PIN);
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  digitalWrite(LED_PIN1, LOW);
  digitalWrite(LED_PIN2, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");
  Udp.begin(localPort);
}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    char incomingPacket[255];
    int len = Udp.read(incomingPacket, 255);
    if (len > 0) incomingPacket[len] = 0;
    String message = String(incomingPacket);
    handleCommand(message);
  }
  idleScan();
  idleBlinkEffect();
  
}

void handleCommand(String command) {
  if (command.startsWith("voicedetected")) {
    int duration = command.substring(13).toInt();
    lookForward(duration);
  } else if (command.startsWith("processing")) {
    int duration = command.substring(10).toInt();
    processing(duration);
  } else if (command == "idleScan") {
    idleScan();
    idleBlinkEffect();
  } else if (command.startsWith("mov ")) {
    String direction = command.substring(4);
    moveDirection(direction);
  }
}
void moveDirection(String direction) {
  int step = 10;  // Adjust the step size as needed

  if (direction == "left") {
    yawAngle = constrain(yawAngle + step, 20, 160);
  } else if (direction == "right") {
    yawAngle = constrain(yawAngle - step, 20, 160);
  } else if (direction == "up") {
    pitchAngle = constrain(pitchAngle - step, 45, 105);
  } else if (direction == "down") {
    pitchAngle = constrain(pitchAngle + step, 45, 105);
  } else {
    Serial.println("Unknown direction command");
    return;
  }

  // Move to the updated position smoothly
  smoothMoveTo(yawServo, yawAngle, yawAngle, 300);
  smoothMoveTo(pitchServo, pitchAngle, pitchAngle, 300);

  Serial.print("Moved to Yaw: ");
  Serial.print(yawAngle);
  Serial.print(", Pitch: ");
  Serial.println(pitchAngle);
}

void idleScan() {
  static unsigned long lastMoveTime = 0;
  static bool isPausing = false;
  static unsigned long pauseEndTime = 0;

  if (isPausing) {
    if (millis() > pauseEndTime) {
      isPausing = false;
    }
  } else if (millis() - lastMoveTime > random(800, 2000)) {
    int targetYaw = random(20, 150);
    int targetPitch = random(45, 105);
    smoothMoveTo(yawServo, yawAngle, targetYaw, random(500, 1000));
    smoothMoveTo(pitchServo, pitchAngle, targetPitch, random(500, 1000));

    lastMoveTime = millis();
    isPausing = true;
    pauseEndTime = millis() + random(1000, 3000);
  }
}
void lookForward(int duration) {
  ledAnimation(duration);
  smoothMoveTo(yawServo, yawAngle, yawCenter, 800);
  smoothMoveTo(pitchServo, pitchAngle, pitchCenter, 800);
  delay(1500);
}


void processing(int duration) {
  unsigned long startTime = millis();
  while (millis() - startTime < duration) {
    ledAnimation(200); // Or any other effect you want
  }

  smoothMoveTo(yawServo, yawAngle, yawCenter, 800);
  smoothMoveTo(pitchServo, pitchAngle, pitchCenter, 800);

  delay(1500);
}


void ledAnimation(int duration) {
  unsigned long startTime = millis();
  while (millis() - startTime < duration) {
    digitalWrite(LED_PIN1, HIGH);
    digitalWrite(LED_PIN2, HIGH);
    delay(200);
    digitalWrite(LED_PIN1, LOW);
    digitalWrite(LED_PIN2, HIGH);
    delay(200);
  }
  digitalWrite(LED_PIN1, LOW);
  digitalWrite(LED_PIN2, LOW);
}

void idleBlinkEffect() {
  static unsigned long lastBlinkTime = 0;
  if (millis() - lastBlinkTime > 1000) {
    digitalWrite(LED_PIN1, HIGH);
    digitalWrite(LED_PIN2, HIGH);
    delay(250);
    digitalWrite(LED_PIN1, LOW);
    digitalWrite(LED_PIN2, LOW);
    lastBlinkTime = millis();
  }
}

void smoothMoveTo(Servo &servo, int &currentAngle, int targetAngle, int duration) {
  int startAngle = currentAngle;
  unsigned long startTime = millis();
  unsigned long endTime = startTime + duration;

  while (millis() < endTime) {
    idleBlinkEffect();
    float progress = (float)(millis() - startTime) / duration;
    progress = constrain(progress, 0.0, 1.0);
    float easedProgress = progress * progress * (3 - 2 * progress);
    currentAngle = startAngle + (targetAngle - startAngle) * easedProgress;
    servo.write(currentAngle);
    delay(20);
  }
  currentAngle = targetAngle;
  servo.write(currentAngle);
}
