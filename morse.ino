#include <morse.h>

void setColorRGB(long hexColor) {
  int red = (hexColor >> 16) & 0xFF; // Shift right by 16 bits to get red, then mask
  int green = (hexColor >> 8) & 0xFF;  // Shift right by 8 bits to get green, then mask
  int blue = hexColor & 0xFF;          // Mask to get blue

  analogWrite(RED_CHANNEL_PIN, red);
  analogWrite(GREEN_CHANNEL_PIN, green);
  analogWrite(BLUE_CHANNEL_PIN, blue);
}
 
void turnOffLED() {
  analogWrite(RED_CHANNEL_PIN, 0);
  analogWrite(GREEN_CHANNEL_PIN, 0);
  analogWrite(BLUE_CHANNEL_PIN, 0);
}

void turnOffGPIOLEDs() {
  analogWrite(BLINK_GPIO_RED, 0);
  analogWrite(BLINK_GPIO_GREEN, 0);
  analogWrite(BLINK_GPIO_BLUE, 0);
  analogWrite(BLINK_GPIO_YELLOW, 0);
}

void resetColorRGB() {
  setColorRGB(YELLOW_COLOR_HEX);
}

void resetColorGPIOLEDs() {
  analogWrite(BLINK_GPIO_YELLOW, 255);
}

