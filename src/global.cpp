#include "global.h"
bool led1_state = false;
bool led2_state = false;

String WIFI_SSID;
String WIFI_PASS;
String CORE_IOT_TOKEN = "AnGdNEIQNZjoIejnBilZ";
String CORE_IOT_SERVER = "app.coreiot.io";
String CORE_IOT_PORT = "1883";

String ssid = "ESP32 2CE1CS";
String password = "12345678";
String wifi_ssid;
String wifi_password;
boolean isWifiConnected = false;
QueueHandle_t xSensorQueue = xQueueCreate(1, sizeof(SensorData_t));
SemaphoreHandle_t xBinarySemaphoreInternet = xSemaphoreCreateBinary();
SemaphoreHandle_t xMutexWifi = xSemaphoreCreateMutex();
