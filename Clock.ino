#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

// Create RTC and LCD objects
RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change to 0x3F if 0x27 doesn't work

void setup() {
  Wire.begin();
  lcd.init();
  lcd.backlight();

  Serial.begin(9600); // For debugging

  if (!rtc.begin()) {
    lcd.setCursor(0, 0);
    lcd.print("RTC not found!");
    while (1); // Stop here if RTC is not found
  }

  if (!rtc.isrunning()) {
    lcd.setCursor(0, 1);
    lcd.print("RTC is stopped");
    // Set the RTC to the time the sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    delay(2000);
    lcd.clear();
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RTC Ready");
  delay(1000);
  lcd.clear();
}

void loop() {
  DateTime now = rtc.now(); // Always get a fresh copy

  // Format time with leading zeroes (HH:MM:SS)
  char timeBuffer[9];
  snprintf(timeBuffer, sizeof(timeBuffer), "%02d:%02d:%02d", now.hour(), now.minute(), now.second());

  // Format date (DD/MM/YYYY)
  char dateBuffer[11];
  snprintf(dateBuffer, sizeof(dateBuffer), "%02d/%02d/%04d", now.day(), now.month(), now.year());

  // Display time
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.print(timeBuffer);
  lcd.print(" "); // Optional: erase old characters

  // Display date
  lcd.setCursor(0, 1);
  lcd.print("Date: ");
  lcd.print(dateBuffer);
  lcd.print(" "); // Optional: erase old characters

  delay(1000);
}
