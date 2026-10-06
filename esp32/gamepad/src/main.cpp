#include <Arduino.h>
#include <BleGamepad.h>

// Deneyap Kart pin definitions
const uint8_t buttonPin1 = D0; // Maps to A
const uint8_t buttonPin2 = D1; // Maps to B
const uint8_t buttonPin3 = D4; // Maps to X
const uint8_t buttonPin4 = D6; // Maps to Y

BleGamepad bleGamepad("Xbox Wireless Controller", "Microsoft", 100);
BleGamepadConfiguration bleGamepadConfig;

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);

  // Configure XInput mode for native iOS recognition
  bleGamepadConfig.setGamepadMode(GamepadMode::XInputSeriesX);
  bleGamepadConfig.setAutoReport(false);

  bleGamepad.begin(&bleGamepadConfig);
  Serial.println("BLE Gamepad ready. Waiting for iOS connection...");
}

void loop() {
  if (bleGamepad.isConnected()) {
    // Read pins (LOW = pressed due to INPUT_PULLUP)
    bool btn1 = (digitalRead(buttonPin1) == LOW);
    bool btn2 = (digitalRead(buttonPin2) == LOW);
    bool btn3 = (digitalRead(buttonPin3) == LOW);
    bool btn4 = (digitalRead(buttonPin4) == LOW);

    // Standard Xbox face buttons: BUTTON_1 (A), BUTTON_2 (B), BUTTON_3 (X),
    // BUTTON_4 (Y)
    btn1 ? bleGamepad.press(BUTTON_3) : bleGamepad.release(BUTTON_3);
    btn2 ? bleGamepad.press(BUTTON_4) : bleGamepad.release(BUTTON_4);
    btn3 ? bleGamepad.press(BUTTON_1) : bleGamepad.release(BUTTON_1);
    btn4 ? bleGamepad.press(BUTTON_2) : bleGamepad.release(BUTTON_2);

    // Push states to iOS
    bleGamepad.sendReport();

    Serial.printf("Pressed: A:%d B:%d X:%d Y:%d\n", btn1, btn2, btn3, btn4);
  }

  // Polling rate and basic debounce delay
  delay(15);
}
