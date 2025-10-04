#include <morse.h>

void setColor(long hexColor) {
  int red = (hexColor >> 16) & 0xFF; // Shift right by 16 bits to get red, then mask
  int green = (hexColor >> 8) & 0xFF;  // Shift right by 8 bits to get green, then mask
  int blue = hexColor & 0xFF;          // Mask to get blue

  analogWrite(RED_CHANNEL_PIN, red);
  analogWrite(GREEN_CHANNEL_PIN, green);
  analogWrite(BLUE_CHANNEL_PIN, blue);

  delay(1500);
}

void turnOffLED() {
  analogWrite(RED_CHANNEL_PIN, 0);
  analogWrite(GREEN_CHANNEL_PIN, 0);
  analogWrite(BLUE_CHANNEL_PIN, 0);
}