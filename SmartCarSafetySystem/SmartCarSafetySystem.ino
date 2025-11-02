#include <LiquidCrystal.h>

// === LCD Tanımları ===
LiquidCrystal lcd(10, 6, 5, 4, 3, 2);

// === Pin Tanımları ===
const int ldrPin          = A0;
const int lm35Pin         = A1;
const int yakitPin        = A2;

const int kemerButonPin   = 7;
const int motorButonPin   = 9;
const int kapiSwitchPin   = 11;

const int blueLedPin      = 8;
const int redLedPin       = 13;
const int sariLedPin      = 26;

const int rgbRedPin       = 22;
const int rgbBluePin      = 24;

const int motorPin        = 23;
const int klimaMotorPin   = 25;
const int buzzerPin       = 12;

const float thresholdTemperature = 25.0;

// === Sistem Durumları ===
bool motorDurumu = false;
bool klimaDurumu = false;
bool farDurumu   = false;

// === LCD Kontrol ===
unsigned long previousDisplayChange = 0;
const long displayInterval = 5000;
int currentDisplayMode = 0;
String lastDisplayedText = "";

void setup() {
  pinMode(ldrPin, INPUT);
  pinMode(lm35Pin, INPUT);
  pinMode(yakitPin, INPUT);

  pinMode(kemerButonPin, INPUT_PULLUP);
  pinMode(motorButonPin, INPUT_PULLUP);
  pinMode(kapiSwitchPin, INPUT_PULLUP);

  pinMode(blueLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(sariLedPin, OUTPUT);
  pinMode(rgbRedPin, OUTPUT);
  pinMode(rgbBluePin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(klimaMotorPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  lcd.begin(16, 2);
  lcd.print("Sistem Hazir");
  delay(1000);
  lcd.clear();
}

void loop() {
  unsigned long currentMillis = millis();

  // Sensörleri oku
  int ldrValue = analogRead(ldrPin);
  int lm35Value = analogRead(lm35Pin);
  float sicaklik = (lm35Value * 5.0 / 1024.0) * 100.0;
  int yakitDegeri = analogRead(yakitPin);
  float yakitYuzde = map(yakitDegeri, 0, 1023, 0, 100);

  bool kemerTakili = (digitalRead(kemerButonPin) == LOW);
  bool motorButonaBasildi = (digitalRead(motorButonPin) == LOW);
  bool kapiKapali = (digitalRead(kapiSwitchPin) == HIGH);

  // Far kontrolü
  farDurumu = (ldrValue <= 500);
  digitalWrite(blueLedPin, farDurumu ? HIGH : LOW);

  // Klima kontrolü
  klimaDurumu = (sicaklik > thresholdTemperature);
  digitalWrite(klimaMotorPin, klimaDurumu ? HIGH : LOW);

  // Acil durum kontrolleri
  if (checkEmergencyConditions(yakitYuzde, kapiKapali, kemerTakili)) {
    return;
  }

  // Motor kontrol
  handleMotorControl(motorButonaBasildi);

  // Yakıt LED kontrol
  updateFuelWarning(yakitYuzde);

  // LCD ekran kontrol
  updateDisplay(currentMillis, sicaklik, yakitYuzde);
}

// === Fonksiyonlar ===

// Acil Durum Kontrolü
bool checkEmergencyConditions(float yakitYuzde, bool kapiKapali, bool kemerTakili) {
  String ekranMesaji = "";

  if (yakitYuzde <= 0) {
    shutdownSystem(false);
    ekranMesaji = "YAKIT BITTI!\nMOTOR DURDU";
  }
  else if (!kapiKapali) {
    shutdownSystem(true);
    ekranMesaji = "UYARI:\nKAPI ACIK!";
  }
  else if (!kemerTakili) {
    shutdownSystem(false);
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(redLedPin, HIGH);
    ekranMesaji = "EMNIYET KEMERI\nTAKILI DEGIL!";
  }
  else {
    digitalWrite(rgbRedPin, HIGH);
    digitalWrite(rgbBluePin, HIGH);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(redLedPin, LOW);
    return false;
  }

  if (ekranMesaji != lastDisplayedText) {
    lcd.clear();
    int sep = ekranMesaji.indexOf('\n');
    lcd.setCursor(0, 0);
    lcd.print(ekranMesaji.substring(0, sep));
    lcd.setCursor(0, 1);
    lcd.print(ekranMesaji.substring(sep + 1));
    lastDisplayedText = ekranMesaji;
  }
  return true;
}

// Sistem kapatma fonksiyonu
void shutdownSystem(bool kapidanDolayi) {
  digitalWrite(motorPin, LOW);
  motorDurumu = false;
  digitalWrite(sariLedPin, LOW);
  digitalWrite(redLedPin, LOW);
  digitalWrite(buzzerPin, LOW);
  digitalWrite(klimaMotorPin, LOW);

  if (kapidanDolayi) {
    digitalWrite(rgbRedPin, LOW);
    digitalWrite(rgbBluePin, LOW);
  } else {
    digitalWrite(rgbRedPin, HIGH);
    digitalWrite(rgbBluePin, HIGH);
  }
}

// Motor kontrol fonksiyonu
void handleMotorControl(bool motorButonaBasildi) {
  static bool oncekiButonDurumu = HIGH;

  if (oncekiButonDurumu == HIGH && motorButonaBasildi == LOW) {
    motorDurumu = !motorDurumu;
    digitalWrite(motorPin, motorDurumu ? HIGH : LOW);
  }
  oncekiButonDurumu = motorButonaBasildi;
}

// Yakıt seviyesi LED kontrol fonksiyonu
void updateFuelWarning(float yakitYuzde) {
  static unsigned long lastBlinkTime = 0;
  static bool blinkState = false;
  unsigned long now = millis();

  if (yakitYuzde < 5) {
    if (now - lastBlinkTime >= 500) {
      blinkState = !blinkState;
      digitalWrite(sariLedPin, blinkState);
      lastBlinkTime = now;
    }
  }
  else if (yakitYuzde < 10) {
    digitalWrite(sariLedPin, HIGH);
  }
  else {
    digitalWrite(sariLedPin, LOW);
  }
}

// LCD ekran güncelleme fonksiyonu
void updateDisplay(unsigned long currentMillis, float sicaklik, float yakitYuzde) {
  String yeniMesaj;

  if (yakitYuzde < 10) {
    if (yakitYuzde < 5) {
      yeniMesaj = "KRITIK UYARI!\nYAKIT:%" + String((int)yakitYuzde);
    } else {
      yeniMesaj = "UYARI:\nYAKIT DUSUK:%" + String((int)yakitYuzde);
    }
  }
  else {
    if (currentMillis - previousDisplayChange >= displayInterval) {
      previousDisplayChange = currentMillis;
      currentDisplayMode = (currentDisplayMode + 1) % 2;
    }

    if (currentDisplayMode == 0) {
      yeniMesaj = "SICAKLIK:" + String(sicaklik, 1) + "C\nKLIMA:" + (klimaDurumu ? "ACIK" : "KAPALI");
    } else {
      yeniMesaj = "FAR:" + String(farDurumu ? "ACIK" : "KAPALI") + "\nYAKIT:%" + String((int)yakitYuzde);
    }
  }

  if (yeniMesaj != lastDisplayedText) {
    lcd.clear();
    int sep = yeniMesaj.indexOf('\n');
    lcd.setCursor(0, 0);
    lcd.print(yeniMesaj.substring(0, sep));
    lcd.setCursor(0, 1);
    lcd.print(yeniMesaj.substring(sep + 1));
    lastDisplayedText = yeniMesaj;
  }
}