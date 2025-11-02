# SmartVehicleSim
This project simulates an "In-Vehicle Smart Safety and Control System" based on the Arduino Mega 2560 platform
# 🚗 Araç İçi Akıllı Güvenlik ve Kontrol Sistemi | In-Vehicle Smart Safety & Control System

## 📌 Proje Özeti | Project Summary

Bu proje, Arduino Mega 2560 mikrodenetleyicisi ve çeşitli sensörler kullanılarak geliştirilen bir **araç içi güvenlik ve konfor simülasyonudur**. Sistem; motor başlatma, emniyet kemeri kontrolü, klima ve far kontrolü, yakıt seviyesi izleme ve kapı durumu gibi hayati fonksiyonları yerine getirir.

This project simulates a **smart in-vehicle safety and control system** using an Arduino Mega 2560 microcontroller and various sensors. The system includes key functionalities like engine start, seatbelt check, climate and headlight control, fuel level monitoring, and door status verification.

---
<img width="884" height="793" alt="image" src="https://github.com/user-attachments/assets/45dd1903-d128-4ad1-9ba4-5be67b8fe8a0" />
<img width="504" height="584" alt="image" src="https://github.com/user-attachments/assets/bf10997c-266d-4d2d-bb62-7e8ea08888a2" />

---

## 🧠 Kullanılan Teknolojiler | Technologies Used

- 👨‍💻 **Arduino Mega 2560**
- 🖥️ **Proteus** (simulation)
- 🧪 **Arduino IDE** (coding)
- 🔧 Sensörler: LDR, LM35, Potansiyometre, Buton, Anahtar
- 💡 Çıkışlar: LED, LCD (16x2), Buzzer, DC Motor

---

## 🔧 Sistem Özellikleri | System Features

| Özellikler (TR)                         | Features (EN)                                |
|----------------------------------------|----------------------------------------------|
| Emniyet kemeri takılmadan motor çalışmaz | Engine won't start unless seatbelt is fastened |
| Sıcaklık 25°C üstü ise klima açılır     | Climate turns on if temperature > 25°C       |
| Ortam ışığı düşükse farlar açılır       | Headlights turn on in low light conditions   |
| Yakıt seviyesi düştükçe uyarı verilir   | Fuel alerts are shown as level drops         |
| Kapı açıkken motor çalışmaz             | Engine won't start if the door is open       |
| LCD ekran tüm durumu gösterir           | LCD displays system status                   |

---

## 💡 Simülasyon Davranışları | Simulation Scenarios

- ✅ **Motor Başlatma & Kemer Kontrolü**: Kemer takılmazsa motor çalışmaz, buzzer uyarı verir.
- 🔥 **Klima Otomasyonu**: LM35 sensöründen okunan sıcaklık > 25°C → Klima çalışır.
- 🌙 **Far Otomasyonu**: Ortam ışığı < 250 → Farlar (LED) açılır.
- ⛽ **Yakıt Takibi**:
  - %10 altı: Sarı LED yanar.
  - %5 altı: Sarı LED yanıp söner.
  - %0: Motor kapanır, LCD uyarı verir.
- 🚪 **Kapı Durumu**: Kapı açıksa RGB LED aktif, motor çalışmaz.

---

## 📦 Dosya Yapısı | File Structure

```plaintext
project/
├── Proteus_Simulation_Diagram.png   # Devre şeması
├── project_code.ino                 # Arduino kodları
├── README.md                        # Proje açıklaması
```

---

## ▶️ How to Run | Nasıl Çalıştırılır?

### 🇬🇧 How to Run

> Follow these steps to simulate the system using Arduino IDE and Proteus:

1. Open `project_code.ino` in **Arduino IDE**.
2. If you have a **Proteus file** (.pdsprj), open it in **Proteus**.
3. Upload the code to the simulated Arduino Mega 2560 in Proteus.
4. Simulate the project and test interactions:
   - Use switches to toggle seatbelt and door states.
   - Observe changes in LEDs, LCD, and buzzer for each scenario.
5. Modify sensor values (temperature, light, fuel) and observe the system's reactions.

> **Note:** Proteus must be correctly configured with sensors (LDR, LM35, etc.) and connected to the Arduino pins matching the `.ino` code.

---

### 🇹🇷 Nasıl Çalıştırılır

> Arduino IDE ve Proteus kullanarak sistemi çalıştırmak için şu adımları izleyin:

1. `project_code.ino` dosyasını **Arduino IDE** ile açın.
2. Elinizde bir **Proteus devre dosyası** (.pdsprj) varsa, **Proteus** programında açın.
3. Kodunuzu simülasyondaki Arduino Mega 2560 üzerine yükleyin.
4. Simülasyonu başlatın ve senaryoları test edin:
   - Emniyet kemeri ve kapı anahtarlarını aç/kapa yaparak test edin.
   - LED, LCD ve buzzer tepkilerini gözlemleyin.
5. Sıcaklık, ışık ve yakıt gibi sensör değerlerini değiştirerek sistemin davranışlarını izleyin.

> **Not:** Proteus’ta kullanılan sensörlerin (LDR, LM35 vs.) `.ino` dosyasındaki pinlerle uyumlu şekilde bağlandığından emin olun.

## 👩‍💻 Ekip | Team

- **Rahime Uysal** – Kodlama, Donanım Testleri
- **Zeynep Vuslat Solmaz** – Algoritma, Proteus Devre Tasarımı, Raporlama

---

---

## 🧠 Anahtar Kelimeler | Keywords

`Arduino Mega` · `Araç Güvenlik Sistemi` · `Proteus` · `Sensör` · `LCD` · `Motor Kontrolü` · `Akıllı Sistem` · `Seatbelt Safety` · `Temperature Control` · `Fuel Warning`
