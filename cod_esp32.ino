#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 4       // Pinul DATA de la DHT22
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
//Pentru a construi acest circuit am utilizat 2 placi breadboard standard pe care le-am unit;
// Inițializare LCD pe adresa 0x27, 16x2 caractere
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);

  // Initializează I2C pe pinii specificați
  Wire.begin(23, 22); 

  dht.begin();

  lcd.init();
  lcd.backlight();
}

void loop() {
  float tempC = dht.readTemperature();
  float tempF = dht.readTemperature(true);
  float hum = dht.readHumidity();

  if (isnan(tempC) || isnan(tempF) || isnan(hum)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Eroare citire");
    lcd.setCursor(0, 1);
    lcd.print("DHT22");
    delay(2000);
    return;
  }

  // Afișare temperatură C și F
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(tempC, 1);
  lcd.print((char)223); // simbol ° (grad)
  lcd.print("C");

 // lcd.setCursor(0, 1);
 // lcd.print("    ");
 // lcd.print(tempF, 1);
 // lcd.print((char)223);
 // lcd.print("F");

  delay(2000);

  // Afișare umiditate
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Umiditate:");
  lcd.setCursor(0, 1);
  lcd.print(hum, 1);
  lcd.print(" %RH");

  delay(2000);
}
