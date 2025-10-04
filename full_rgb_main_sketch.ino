#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <array>

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "map.h"
#include "characters.h"
#include "gpio.h"
#include "morse.h"

char_uint8_array_map_t *my_map = char_uint8_array_map_create(8);

void print_callback(char key, const uint8_t *value_array, size_t array_size, void *userdata) {
    printf("Key: '%c', Array: [", key);
    for (size_t i = 0; i < array_size; i++) {
        printf("%d", value_array[i]);
        if (i < array_size - 1) printf(", ");
    }
    printf("], Size: %zu\n", array_size);
}

void setup() {
  Serial.begin(9600);
  pinMode(RED_CHANNEL_PIN, OUTPUT); 
  pinMode(GREEN_CHANNEL_PIN, OUTPUT);
  pinMode(BLUE_CHANNEL_PIN, OUTPUT); 

  for (int i = 0; i < NUM_GPIOS; i++) {
    GPIO current_gpio = ALL_GPIOS[i];
    printf("Processing gpio value: %d\n", current_gpio);
    analogWrite(current_gpio, BRIGHTNESS);
  }

  int character_bindings_size = sizeof(character_bindings) / sizeof(character_bindings[0]);
  int characters_size = sizeof(characters) / sizeof(characters[0]);

  // TODO: figure out nested loop and spaces
  for (size_t i = 0; i < character_bindings_size; ++i) {
    for (size_t j = 0; j < characters_size; ++j) {
      char_uint8_array_map_put(my_map, characters[j], character_bindings[i], sizeof(character_bindings[i]));
    }
  }
  
  // Iterate through all entries
  printf("All entries:\n");
  char_uint8_array_map_foreach(my_map, print_callback, NULL);
  
  printf("Map size: %zu\n", char_uint8_array_map_size(my_map));
}

char* word_from_uart = "ol";
char letter;

void morse_code_encoder(char* word) {
  int array_size = 5;
  setColor(0xfdff00);
  delay(1000);
  turnOffLED();
  for (size_t index = 0; index < strlen(word); ++index) {    
    std::array<int, 5> morse_sequence = morse_code_mapping.at(tolower(word[index]));

    for (size_t morse_index = 0; morse_index < array_size; ++morse_index) {
      int code = morse_sequence[morse_index];
      
      if (code == DOT) {
        setColor(GREEN_COLOR_HEX);
      } else if (code == DASH) {
        setColor(BLUE_COLOR_HEX);
      } else {
        setColor(RED_COLOR_HEX);
      }



      turnOffLED();
      delay(500);
    }
  }
}

void loop() {
  delay(1000);
  // for (size_t index = 0; index < strlen(word_to_encode); ++index) {
  //   uint8_t *retrieved_array;
  //   size_t array_size;

    // if (char_uint8_array_map_get(my_map, tolower(word_to_encode[index]), &retrieved_array, &array_size)) {
    //   for (int i = 0; i < NUM_GPIOS; i++) {
    //     GPIO current_gpio = ALL_GPIOS[i];
    //     analogWrite(current_gpio, retrieved_array[i]);
    //   }
    // }

  //   delay(5000);
  // }

  // morse_code_encoder(word_from_uart);

  // if (letter == '1' ) {
  //   Serial.println(letter);
  //   setColor(255, 0, 0);  // Красный
  //   delay(1200);

  //   setColor(0, 0, 255);  // Синий
  //   delay(1200);

  //   setColor(0, 255, 0);  // Зелёный
  //   delay(1200);
  // }
  // else if (letter == '2') {
    for (int i = 0; i < NUM_GPIOS; i++) {
      GPIO current_gpio = ALL_GPIOS[i];
      analogWrite(current_gpio, 1);
    }
  // }


  // analogWrite(19, 1);
} 