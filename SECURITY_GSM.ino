#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

// PIR sensor pin
const int pirPin = 9;
// Buzzer pin
const int buzzerPin = 10;
// GSM module pins (SoftwareSerial)
SoftwareSerial gsm(7, 8); // RX, TX

// LCD configuration
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // Initialize LCD
  lcd.begin(16, 2); // Adjust if you're using a different size LCD

  // Initialize PIR sensor and buzzer
  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  // Start serial communication with GSM module
  gsm.begin(9600);
  delay(1000);

  // Clear LCD initially
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Security System");
  lcd.setCursor(0, 1);
  lcd.print("Ready");
}

void loop() {
  int pirValue = digitalRead(pirPin);

  if (pirValue == HIGH) {
    triggerAlarm();
    sendSMS();
  }
}

void triggerAlarm() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Intruder Detected!");
  
  digitalWrite(buzzerPin, HIGH); // Sound the buzzer
  delay(3000); // Buzzer on for 1 second
  digitalWrite(buzzerPin, LOW); // Turn off the buzzer
  
  delay(5000); // Delay to prevent multiple detections in a short time

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Security System");
  lcd.setCursor(0, 1);
  lcd.print("Ready");
}

void sendSMS() {
  gsm.println("AT+CMGF=1"); // Set SMS mode to text
  delay(100);
  gsm.println("AT + CMGS = \"+254734567890\""); // Replace with your destination number
  delay(100);
  gsm.println("Intruder alert!"); // SMS content
  delay(100);
  gsm.println((char)26); // End AT command with Ctrl+Z
  delay(100);
  gsm.println();
  delay(5000); // Give module time to send SMS
}
