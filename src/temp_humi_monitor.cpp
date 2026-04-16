#include "temp_humi_monitor.h"

DHT20 dht20;
LiquidCrystal_I2C lcd(33, 16, 2);

void temp_humi_monitor(void *pvParameters) {
  Serial.println("[Temp/Humidity Monitor] Starting...");
  
  Wire.begin(11, 12);
  dht20.begin();
  
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  
  Serial.println("[Temp/Humidity Monitor] LCD initialized");
  Serial.println("[Temp/Humidity Monitor] DHT20 sensor ready");

  while (1) {
    dht20.read();
    
    float temperature = dht20.getTemperature();
    float humidity = dht20.getHumidity();

    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("[Temp/Humidity Monitor] Failed to read from DHT20!");
      
      lcd.setCursor(0, 0);
      lcd.print("Error: DHT20    ");
      lcd.setCursor(0, 1);
      lcd.print("Read failed     ");
      
      temperature = humidity = -1;
    } else {
      glob_temperature = temperature;
      glob_humidity = humidity;

      Serial.print("[Temp/Humidity Monitor] Temp: ");
      Serial.print(temperature);
      Serial.print("°C  Humidity: ");
      Serial.print(humidity);
      Serial.println("%");
      
      lcd.setCursor(0, 0);
      lcd.print("Temp:");
      lcd.print(temperature, 2);  
      lcd.print("C ");
      
      lcd.setCursor(0, 1);
      lcd.print("Humi:");
      lcd.print(humidity, 2);
      lcd.print("%");
    }

    vTaskDelay(pdMS_TO_TICKS(5000));
  }
}
