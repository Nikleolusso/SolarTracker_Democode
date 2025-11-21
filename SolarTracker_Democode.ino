/*
  IMPORTANT   : The U8g2 library is needed.
  Installation: "Werkzeuge" -> "Biblotheken verwalten..." -> Search for U8g2 -> Select it and press on install.
*/

// Libraries
#include <U8x8lib.h>
#include <Servo.h>

// Pins
#define JOY_VERTICAL_PIN     A0
#define JOY_HORIZONTAL_PIN   A1
#define PHOTORESISTOR_1_PIN  A2
#define PHOTORESISTOR_2_PIN  A3
#define PHOTORESISTOR_3_PIN  A4
#define SOLARPANEL_SENSE_PIN A5
#define JOY_BUTTON_PIN       2
#define SWITCH_1_PIN         3
#define SWITCH_2_PIN         4
#define LED_1_PIN            5
#define LED_2_PIN            6
#define SERVO_HORIZONTAL_PIN 7
#define DISPLAY_DC_PIN       8
#define DISPLAY_RESET_PIN    9
#define DISPLAY_CS_PIN       10
#define SERVO_VERTICAL_PIN   12

// Display
U8X8_SSD1306_128X64_NONAME_4W_HW_SPI u8x8(DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RESET_PIN);


// Servos
Servo servoV;
Servo servoH;

// Global variables
char textBuffer[5];   // String variable (array of 5 bytes) can hold a string of length 4 characters (+1 byte string termination)



void setup() {
  // Display
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFont(u8x8_font_victoriabold8_r);
  u8x8.drawString(0, 0, "SolarTrackerTest");
  u8x8.setFont(u8x8_font_victoriamedium8_r);
  u8x8.drawString(0, 2, "JV:      JH:    ");
  u8x8.drawString(0, 4, "S1:      S2:");
  u8x8.drawString(0, 5, "S3:      SP:");
  u8x8.drawString(0, 7, "B1:   B2:   JB:");
  u8x8.setFont(u8x8_font_victoriabold8_r);


  // Servo
  // servoV on Pin 12 MUST be initialized AFTER the disply, because the SPI changes it to an input
  // because it is MISO but unused with the display
  servoV.attach(SERVO_VERTICAL_PIN, 800, 2500);
  servoH.attach(SERVO_HORIZONTAL_PIN, 500, 2500);

  // Buttons
  pinMode(SWITCH_1_PIN, INPUT);
  pinMode(SWITCH_2_PIN, INPUT);
  pinMode(JOY_BUTTON_PIN, INPUT);

  // LEDs
  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
}

void loop() {

  // Local variables
  int joyV;
  int joyH;
  int sensor1;
  int sensor2;
  int sensor3;
  int solarPanel;
  int button1;
  int button2;
  int buttonJoy;
  int servoV_angle;
  int servoH_angle;
  

  // Read all ADC inputs and store into variables
  joyV      = analogRead(JOY_VERTICAL_PIN);
  joyH      = analogRead(JOY_HORIZONTAL_PIN);
  sensor1   = analogRead(PHOTORESISTOR_1_PIN);
  sensor2   = analogRead(PHOTORESISTOR_2_PIN);
  sensor3   = analogRead(PHOTORESISTOR_3_PIN);
  solarPanel = analogRead(SOLARPANEL_SENSE_PIN);

  // Read buttons state and store into variables
  button1   = digitalRead(SWITCH_1_PIN);
  button2   = digitalRead(SWITCH_2_PIN);
  buttonJoy = digitalRead(JOY_BUTTON_PIN);

  // Buttons are switching the LEDS and also writing state on display
  if (button1 == HIGH) {
    digitalWrite(LED_1_PIN, HIGH);
    u8x8.drawString(3, 7, "X");
  } else {
    digitalWrite(LED_1_PIN, LOW);
    u8x8.drawString(3, 7, "O");
  }

  if (button2 == HIGH) {
    digitalWrite(LED_2_PIN, HIGH);
    u8x8.drawString(9, 7, "X");
  } else {
    digitalWrite(LED_2_PIN, LOW);
    u8x8.drawString(9, 7, "O");
  }

  if (buttonJoy == HIGH) {
    u8x8.drawString(15, 7, "X");
  } else {
    u8x8.drawString(15, 7, "O");
  }


  // Write ADC values to display
  u8x8.setCursor(3, 2);
  sprintf(textBuffer, "%4d", joyV);
  u8x8.print(textBuffer);

  u8x8.setCursor(12, 2);
  sprintf(textBuffer, "%4d", joyH);
  u8x8.print(textBuffer);

  u8x8.setCursor(3, 4);
  sprintf(textBuffer, "%4d", sensor1);
  u8x8.print(textBuffer);

  u8x8.setCursor(12, 4);
  sprintf(textBuffer, "%4d", sensor2);
  u8x8.print(textBuffer);

  u8x8.setCursor(3, 5);
  sprintf(textBuffer, "%4d", sensor3);
  u8x8.print(textBuffer);


  sprintf(textBuffer, "%4d", solarPanel);
  u8x8.drawString(12, 5, textBuffer);
  //u8x8.setCursor(12, 5);
  //u8x8.print(textBuffer);


  // Set the servos
  // map joystick adc value (0...1023) to angle value (0...180)
  servoV_angle = map(joyV, 0, 1023, 0, 180);
  servoH_angle = map(joyH, 1023, 0, 0, 180);
  
  // Set the servos
  servoV.write(servoV_angle);
  servoH.write(servoH_angle);
  
  // Delay for 20ms => Update everything every 20ms
  delay(20);
  
}
