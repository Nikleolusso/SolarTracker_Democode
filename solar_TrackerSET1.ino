#include <U8x8lib.h>
#include <Servo.h>

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
char textBuffer[5]; // Variable for number output

// Servos
Servo servoV;
Servo servoH;


void setup() {
 
  u8x8.begin();
  u8x8.setPowerSave(0);
  
  u8x8.setFont(u8x8_font_victoriabold8_r);
  u8x8.drawString(0, 0, "SolarTrackerTest");
  
  u8x8.setFont(u8x8_font_victoriamedium8_r);
  u8x8.drawString(0, 1, "JV:      JH:");
  u8x8.drawString(0, 2, "S1:      S2:");
  u8x8.drawString(0, 3, "S3:      SP:");
  u8x8.drawString(0, 4, "DH:      DV:");
  u8x8.drawString(0, 5, "SH:      SV:");

  servoV.attach(SERVO_VERTICAL_PIN, 500, 2500);
  servoH.attach(SERVO_HORIZONTAL_PIN, 500, 2500);
}

void loop() {

 int S1= analogRead(PHOTORESISTOR_1_PIN);
 int S2= analogRead(PHOTORESISTOR_2_PIN);
 int S3= analogRead(PHOTORESISTOR_3_PIN);
 int SC= analogRead(SOLARPANEL_SENSE_PIN);
 int DifV= S1-(S2+S3)/2;
 int DifH= S2-S3;
 int SH= servoH.read();
 int SV= servoV.read();
 int JV= analogRead(JOY_VERTICAL_PIN );
 int JH=analogRead (JOY_HORIZONTAL_PIN);
 


    u8x8.setCursor(3, 1);
    sprintf(textBuffer, "%4d", JV);
    u8x8.print(textBuffer);

    u8x8.setCursor(12, 1);
    sprintf(textBuffer, "%4d", JH);
    u8x8.print(textBuffer);

    u8x8.setCursor(3, 2);
    sprintf(textBuffer, "%4d", S1);
    u8x8.print(textBuffer);

    u8x8.setCursor(12, 2);
    sprintf(textBuffer, "%4d", S2);
    u8x8.print(textBuffer);

    u8x8.setCursor(3, 3);
    sprintf(textBuffer, "%4d", S3);
    u8x8.print(textBuffer);

      u8x8.setCursor(12, 3);
    sprintf(textBuffer, "%4d", SC);
    u8x8.print(textBuffer);

     u8x8.setCursor(3, 4);
    sprintf(textBuffer, "%4d", DifH);
    u8x8.print(textBuffer);
    
    u8x8.setCursor(12, 4);
    sprintf(textBuffer, "%4d", DifV);
    u8x8.print(textBuffer);

     u8x8.setCursor(3, 5);
    sprintf(textBuffer, "%4d", SH);
    u8x8.print(textBuffer);
    
    u8x8.setCursor(12, 5);
    sprintf(textBuffer, "%4d", SV);
    u8x8.print(textBuffer);

    
if (DifV > 20) {SV= SV-1;}

if (DifV < -20) {SV= SV+1;}

if (SV > 180) {SV= 180;}
if (SV < 0) {SV = 0;}

     servoV.write (SV);
     delay (20);
        

if (DifH > 20) {SH= SH+1;}

if (DifH < -20) {SH= SH-1; }

if (SH > 180) {SH= 180;}
if (SH < 0) {SH = 0;}

     servoH.write (SH);
     delay (20);
}