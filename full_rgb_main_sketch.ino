#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "map.h"
#include "gpio.h"
#include "morse.h"

typedef void (*morse_code_implementation)(int);
typedef void (*turn_off_implementation)();
typedef void (*reset_color_implementation)();

void setup() {
  Serial.begin(9600);

  for (size_t index = 0; index < NUM_GPIOS; ++index) {
    pinMode(ALL_GPIOS[index], OUTPUT);
  }
}

void morse_code_encoder(
  String word, 
  morse_code_implementation callback,
  turn_off_implementation turn_off_callback,
  reset_color_implementation reset_color_callback
) {
  int array_size = 5;
  reset_color_callback();
  delay(500);
  turn_off_callback();

  for (size_t index = 0; index < word.length(); ++index) {    
    std::array<int, 5> morse_sequence = morse_code_mapping.at(tolower(word[index]));

    for (size_t morse_index = 0; morse_index < array_size; ++morse_index) {
      int code = morse_sequence[morse_index];
      
      callback(code);
      delay(100);

      turn_off_callback();
      delay(500);
    }
  }
}

void rgb_led_impl(int code) {
  if (code == DOT) {
    setColorRGB(GREEN_COLOR_HEX);
  } else if (code == DASH) {
    setColorRGB(BLUE_COLOR_HEX);
  } else {
    setColorRGB(RED_COLOR_HEX);
  }
}

void plain_gpios_impl(int code) {
  if (code == DOT) {
    analogWrite(BLINK_GPIO_RED, 255);
  } else if (code == DASH) {
    analogWrite(BLINK_GPIO_BLUE, 255);
  } else {
    analogWrite(BLINK_GPIO_GREEN, 255);
  }
}

bool switchMode = false;

void loop() {
  delay(1000);
  
  if (Serial.available() > 0) {
    String word_to_encode = "";
    String UART_BUFFER = Serial.readStringUntil('\n');
    Serial.print("I received: ");
    Serial.println(UART_BUFFER);

    if (UART_BUFFER == "switchmode") {
      switchMode = !switchMode;
      word_to_encode = "";
    } else {
      word_to_encode = UART_BUFFER;
    }
    

    Serial.print("Word to encode: ");
    Serial.println(word_to_encode);

    if (switchMode) {
      morse_code_encoder(
        word_to_encode, 
        plain_gpios_impl, 
        turnOffGPIOLEDs,
        resetColorGPIOLEDs
      );
    } else {
      morse_code_encoder(
        word_to_encode,
        rgb_led_impl, 
        turnOffLED,
        resetColorRGB
      );
    }
  }
} 