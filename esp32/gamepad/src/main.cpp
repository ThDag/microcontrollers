#include <Arduino.h>
#include <BleGamepad.h>

// Deneyap Kart pin definitions
<<<<<<< HEAD
const uint8_t buttonPin1 = D0; // Maps to X (BUTTON_3)
const uint8_t buttonPin2 = D1; // Maps to Y (BUTTON_4)
const uint8_t buttonPin3 = D4; // Maps to A (BUTTON_1)
const uint8_t buttonPin4 = D6; // Maps to B (BUTTON_2)

// Joystick analog pin definitions
const uint8_t joyXPin = A4;
const uint8_t joyYPin = A5;

// ESP32 ADC thresholds (0 to 4095, center ~2048)
const int THRESHOLD_LOW = 1200;
const int THRESHOLD_HIGH = 2800;
=======
const uint8_t buttonPin1 = D0; // Maps to A
const uint8_t buttonPin2 = D1; // Maps to B
const uint8_t buttonPin3 = D4; // Maps to X
const uint8_t buttonPin4 = D6; // Maps to Y
>>>>>>> parent of e9128c0 (joystick as updownleftright buttons initial)

BleGamepad bleGamepad("Xbox Wireless Controller", "Microsoft", 100);
BleGamepadConfiguration bleGamepadConfig;

// State tracking to prevent redundant packets
bool lastBtn1 = false;
bool lastBtn2 = false;
bool lastBtn3 = false;
bool lastBtn4 = false;
signed char lastHat = HAT_CENTERED;

void setup() {
  Serial.begin(115200);

  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);

<<<<<<< HEAD
  pinMode(joyXPin, INPUT);
  pinMode(joyYPin, INPUT);

  // 1. Connection timing optimizations (1.25ms units)
  // 6 = 7.5ms, 12 = 15ms. 0 latency ensures immediate delivery.
  bleGamepadConfig.setMinInterval(6);
  bleGamepadConfig.setMaxInterval(12);
  bleGamepadConfig.setLatency(0);
  bleGamepadConfig.setTimeout(400); // 400 * 10ms = 4 seconds
  bleGamepadConfig.setTxPowerLevel(ESP_PWR_LVL_P9);

  // 2. Controller mode configuration
=======
  // Configure XInput mode for native iOS recognition
>>>>>>> parent of e9128c0 (joystick as updownleftright buttons initial)
  bleGamepadConfig.setGamepadMode(GamepadMode::XInputSeriesX);
  bleGamepadConfig.setAutoReport(false);

  bleGamepad.begin(&bleGamepadConfig);
  Serial.println("BLE Gamepad ready. Waiting for connection...");
}

void loop() {
<<<<<<< HEAD
  if (!bleGamepad.isConnected()) {
    delay(50); // Low-power sleep while searching for host
    return;
  }

  // Non-blocking rate-limit: 8ms ceiling (~125 Hz polling)
  static uint32_t lastPollTime = 0;
  uint32_t now = millis();
  if (now - lastPollTime < 8) {
    return;
  }
  lastPollTime = now;

  // 1. Read face buttons (LOW = pressed due to INPUT_PULLUP)
  bool btn1 = (digitalRead(buttonPin1) == LOW);
  bool btn2 = (digitalRead(buttonPin2) == LOW);
  bool btn3 = (digitalRead(buttonPin3) == LOW);
  bool btn4 = (digitalRead(buttonPin4) == LOW);

  // 2. Read analog joystick & calculate hat direction
  int joyX = analogRead(joyXPin);
  int joyY = analogRead(joyYPin);

  bool joyLeft = (joyX < THRESHOLD_LOW);
  bool joyRight = (joyX > THRESHOLD_HIGH);
  bool joyDown = (joyY < THRESHOLD_LOW);
  bool joyUp = (joyY > THRESHOLD_HIGH);

  signed char currentHat = HAT_CENTERED;

  if (joyUp && joyRight)
    currentHat = HAT_UP_RIGHT;
  else if (joyUp && joyLeft)
    currentHat = HAT_UP_LEFT;
  else if (joyDown && joyRight)
    currentHat = HAT_DOWN_RIGHT;
  else if (joyDown && joyLeft)
    currentHat = HAT_DOWN_LEFT;
  else if (joyUp)
    currentHat = HAT_UP;
  else if (joyDown)
    currentHat = HAT_DOWN;
  else if (joyLeft)
    currentHat = HAT_LEFT;
  else if (joyRight)
    currentHat = HAT_RIGHT;

  // 3. Transmit ONLY if physical state has changed
  bool stateChanged = (btn1 != lastBtn1) || (btn2 != lastBtn2) ||
                      (btn3 != lastBtn3) || (btn4 != lastBtn4) ||
                      (currentHat != lastHat);

  if (stateChanged) {
=======
  if (bleGamepad.isConnected()) {
    // Read pins (LOW = pressed due to INPUT_PULLUP)
    bool btn1 = (digitalRead(buttonPin1) == LOW);
    bool btn2 = (digitalRead(buttonPin2) == LOW);
    bool btn3 = (digitalRead(buttonPin3) == LOW);
    bool btn4 = (digitalRead(buttonPin4) == LOW);

    // Standard Xbox face buttons: BUTTON_1 (A), BUTTON_2 (B), BUTTON_3 (X),
    // BUTTON_4 (Y)
>>>>>>> parent of e9128c0 (joystick as updownleftright buttons initial)
    btn1 ? bleGamepad.press(BUTTON_3) : bleGamepad.release(BUTTON_3);
    btn2 ? bleGamepad.press(BUTTON_4) : bleGamepad.release(BUTTON_4);
    btn3 ? bleGamepad.press(BUTTON_1) : bleGamepad.release(BUTTON_1);
    btn4 ? bleGamepad.press(BUTTON_2) : bleGamepad.release(BUTTON_2);

<<<<<<< HEAD
    bleGamepad.setHat1(currentHat);
    bleGamepad.sendReport();

    // Store state
    lastBtn1 = btn1;
    lastBtn2 = btn2;
    lastBtn3 = btn3;
    lastBtn4 = btn4;
    lastHat = currentHat;
=======
    // Push states to iOS
    bleGamepad.sendReport();

    Serial.printf("Pressed: A:%d B:%d X:%d Y:%d\n", btn1, btn2, btn3, btn4);
>>>>>>> parent of e9128c0 (joystick as updownleftright buttons initial)
  }
}
