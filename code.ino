#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "" //Paste BLYNK Template ID
#define BLYNK_TEMPLATE_NAME "" //Paste BLYNK Template Name
#define BLYNK_AUTH_TOKEN "" //Paste BLYNK Auth Token

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// WiFi credentials
char ssid[] = ""; //wifi name goes here
char pass[] = ""; //wifi password goes here

// DHT11 Configuration
#define DHTPIN D1
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// LCD Configuration (I2C Address 0x27, 16x2 Display)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    Serial.begin(115200);

    // Initialize LCD and DHT sensor
    lcd.init();
    lcd.backlight();
    dht.begin();

    // Display "Starting System..." immediately
    lcd.setCursor(0, 0);
    lcd.print("Starting System...");
    delay(2000);

    // Start Wi-Fi connection in the background
    WiFi.begin(ssid, pass);
}

void loop() {
    // Read Temperature & Humidity from DHT11
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // Display sensor readings on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: "); lcd.print(temperature, 1); lcd.write(223); lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("Humidity: "); lcd.print(humidity, 1); lcd.print("%");

    // Try connecting to Wi-Fi if not already connected
    if (WiFi.status() == WL_CONNECTED) {
        Blynk.config(BLYNK_AUTH_TOKEN);
        Blynk.connect();
        Blynk.virtualWrite(V0, humidity);
        Blynk.virtualWrite(V1, temperature);
    }

    delay(2000);  // Update every 2 sec
}

