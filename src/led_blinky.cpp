#include "led_blinky.h"

// Morse code dictionary (A-Z 0-9)
const char* morseDictionary[] = {
  ".-",     // A
  "-...",   // B
  "-.-.",   // C
  "-..",    // D
  ".",      // E
  "..-.",   // F
  "--.",    // G
  "....",   // H
  "..",     // I
  ".---",   // J
  "-.-",    // K
  ".-..",   // L
  "--",     // M
  "-.",     // N
  "---",    // O
  ".--.",   // P
  "--.-",   // Q
  ".-.",    // R
  "...",    // S
  "-",      // T
  "..-",    // U
  "...-",   // V
  ".--",    // W
  "-..-",   // X
  "-.--",   // Y
  "--..",   // Z
  "-----",  // 0
  ".----",  // 1
  "..---",  // 2
  "...--",  // 3
  "....-",  // 4
  ".....",  // 5
  "-....",  // 6
  "--...",  // 7
  "---..",  // 8
  "----."   // 9
};

// Morse code timing (in milliseconds)
#define DOT_DURATION 100      // Short blink (dit)
#define DASH_DURATION 300     // Long blink (dah) = 3x dot
#define GAP_IN_CHAR 100       // Gap within character
#define GAP_BETWEEN_CHAR 300  // Gap between characters = 3x dot
#define GAP_BETWEEN_WORD 700  // Gap between words = 7x dot

// Get morse code for a character (A-Z, 0-9)
const char* getMorseCode(char c) {
  if (c >= 'A' && c <= 'Z') {
    return morseDictionary[c - 'A'];
  } else if (c >= 'a' && c <= 'z') {
    return morseDictionary[c - 'a'];
  } else if (c >= '0' && c <= '9') {
    return morseDictionary[26 + (c - '0')];
  }
  return NULL;
}

// Blink a single morse character
void blinkMorseChar(const char* morse) {
  for (int i = 0; morse[i] != '\0'; i++) {
    if (morse[i] == '.') {
      // Dot: short blink
      digitalWrite(LED_GPIO, HIGH);
      vTaskDelay(pdMS_TO_TICKS(DOT_DURATION));
      digitalWrite(LED_GPIO, LOW);
    } else if (morse[i] == '-') {
      // Dash: long blink
      digitalWrite(LED_GPIO, HIGH);
      vTaskDelay(pdMS_TO_TICKS(DASH_DURATION));
      digitalWrite(LED_GPIO, LOW);
    }
    
    // Gap within character (between dots/dashes)
    if (morse[i + 1] != '\0') {
      vTaskDelay(pdMS_TO_TICKS(GAP_IN_CHAR));
    }
  }
}

// Task to blink message in morse code
void led_blinky(void *pvParameters) {
  pinMode(LED_GPIO, OUTPUT);
  digitalWrite(LED_GPIO, LOW);
  
  const char* message = (const char*)pvParameters;
  
  while (1) {
    if (message == NULL) {
      // Default message if none provided
      message = "HELLO";
    }
    
    // Transmit each character
    for (int i = 0; message[i] != '\0'; i++) {
      if (message[i] == ' ') {
        // Word gap
        vTaskDelay(pdMS_TO_TICKS(GAP_BETWEEN_WORD));
      } else {
        // Get morse code for character
        const char* morse = getMorseCode(message[i]);
        if (morse != NULL) {
          blinkMorseChar(morse);
          // Gap between characters
          vTaskDelay(pdMS_TO_TICKS(GAP_BETWEEN_CHAR));
        }
      }
    }
    
    // Wait before repeating message
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}
