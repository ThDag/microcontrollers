#include <Arduino.h>
#include <BleGamepad.h>

// Deneyap Kart button pin definitions
const uint8_t buttonPin1 = D0; // Maps to X
const uint8_t buttonPin2 = D1; // Maps to Y
const uint8_t buttonPin3 = D4; // Maps to A
const uint8_t buttonPin4 = D6; // Maps to B

// Joystick analog pin definitions (Connect to ADC pins on your board)
const uint8_t joyXPin = A0;
const uint8_t joyYPin = A1;

// ESP32 ADC range is 0 - 4095 with center resting ~2048.
// Deadband threshold: values past these triggers are counted as pressed.
const int CENTER_VAL = 2048;
const int THRESHOLD_LOW = 1200;  // Pushed down or left
const int THRESHOLD_HIGH = 2800; // Pushed up or right

BleGamepad bleGamepad("Xbox Wireless Controller", "Microsoft", 100);
BleGamepadConfiguration bleGamepadConfig;

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);

  // ADC pins do not require pullups
  pinMode(joyXPin, INPUT);
  pinMode(joyYPin, INPUT);

  // Configure XInput mode for native iOS recognition
  bleGamepadConfig.setGamepadMode(GamepadMode::XInputSeriesX);
  bleGamepadConfig.setAutoReport(false);

  bleGamepad.begin(&bleGamepadConfig);
  Serial.println("BLE Gamepad ready. Waiting for iOS connection...");
}

void loop() {
  if (bleGamepad.isConnected()) {
    // Read face buttons (LOW = pressed due to INPUT_PULLUP)
    bool btn1 = (digitalRead(buttonPin1) == LOW);
    bool btn2 = (digitalRead(buttonPin2) == LOW);
    bool btn3 = (digitalRead(buttonPin3) == LOW);
    bool btn4 = (digitalRead(buttonPin4) == LOW);

    // Read analog joystick
    int joyX = analogRead(joyXPin);
    int joyY = analogRead(joyYPin);

    // Evaluate directions independently to naturally allow diagonals
    bool joyLeft = (joyX < THRESHOLD_LOW);
    bool joyRight = (joyX > THRESHOLD_HIGH);
    bool joyDown = (joyY < THRESHOLD_LOW);
    bool joyUp = (joyY > THRESHOLD_HIGH);

    // Update face buttons
    btn1 ? bleGamepad.press(BUTTON_3) : bleGamepad.release(BUTTON_3);
    btn2 ? bleGamepad.press(BUTTON_4) : bleGamepad.release(BUTTON_4);
    btn3 ? bleGamepad.press(BUTTON_1) : bleGamepad.release(BUTTON_1);
    btn4 ? bleGamepad.press(BUTTON_2) : bleGamepad.release(BUTTON_2);

    // Update directional inputs (D-Pad)
    joyUp ? bleGamepad.press(DPAD_UP) : bleGamepad.release(DPAD_UP);
    joyDown ? bleGamepad.press(DPAD_DOWN) : bleGamepad.release(DPAD_DOWN);
    joyLeft ? bleGamepad.press(DPAD_LEFT) : bleGamepad.release(DPAD_LEFT);
    joyRight ? bleGamepad.press(DPAD_RIGHT) : bleGamepad.release(DPAD_RIGHT);

    // Push states to connected device
    bleGamepad.sendReport();

    Serial.printf("Btns: [A:%d B:%d X:%d Y:%d] | Joy: [U:%d D:%d L:%d R:%d] "
                  "(X:%d Y:%d)\n",
                  btn3, btn4, btn1, btn2, joyUp, joyDown, joyLeft, joyRight,
                  joyX, joyY);
  }

  // Polling rate and basic debounce delay
  delay(15);
}
