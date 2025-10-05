#ifndef GPIO_H
#define GPIO_H

#define BLINK_GPIO_BLUE   19
#define BLINK_GPIO_GREEN  21
#define BLINK_GPIO_YELLOW 23
#define BLINK_GPIO_RED    22

#define RED_CHANNEL_PIN 27
#define GREEN_CHANNEL_PIN 26
#define BLUE_CHANNEL_PIN 25

const int ALL_GPIOS[] = {
    // RGB GPIO
    RED_CHANNEL_PIN,
    GREEN_CHANNEL_PIN,
    BLUE_CHANNEL_PIN,

    // Plain GPIO
    BLINK_GPIO_BLUE, 
    BLINK_GPIO_GREEN, 
    BLINK_GPIO_YELLOW, 
    BLINK_GPIO_RED
};

const int NUM_GPIOS = sizeof(ALL_GPIOS) / sizeof(ALL_GPIOS[0]);

#endif