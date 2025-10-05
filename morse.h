#ifndef MORSE_H
#define MORSE_H

#include <map>
#include <array>

#define RED_COLOR_HEX 0xff0000
#define GREEN_COLOR_HEX 0x00ff00
#define BLUE_COLOR_HEX 0x0000ff
#define YELLOW_COLOR_HEX 0xfdff00

#define CLEAR 0
#define DOT 1
#define DASH 2

std::map<char, std::array<int, 5>> morse_code_mapping{
    {'a', std::array<int, 5>{DOT, DASH, CLEAR, CLEAR, CLEAR}},
    {'b', std::array<int, 5>{DASH, DOT, DOT, DOT, CLEAR}},
    {'c', std::array<int, 5>{DASH, DOT, DASH, DOT, CLEAR}},
    {'d', std::array<int, 5>{DASH, DOT, DOT, CLEAR, CLEAR}},
    {'e', std::array<int, 5>{DOT, CLEAR, CLEAR, CLEAR, CLEAR}},
    {'f', std::array<int, 5>{DOT, DOT, DASH, DOT, CLEAR}},
    {'g', std::array<int, 5>{DASH, DASH, DOT, CLEAR, CLEAR}},
    {'h', std::array<int, 5>{DOT, DOT, DOT, DOT, CLEAR}},
    {'i', std::array<int, 5>{DOT, DOT, CLEAR, CLEAR, CLEAR}},
    {'j', std::array<int, 5>{DOT, DASH, DASH, DASH, CLEAR}},
    {'k', std::array<int, 5>{DASH, DOT, DASH, CLEAR, CLEAR}},
    {'l', std::array<int, 5>{DOT, DASH, DOT, DOT, CLEAR}},
    {'m', std::array<int, 5>{DASH, DASH, CLEAR, CLEAR, CLEAR}},
    {'n', std::array<int, 5>{DASH, DOT, CLEAR, CLEAR, CLEAR}},
    {'o', std::array<int, 5>{DASH, DASH, DASH, CLEAR, CLEAR}},
    {'p', std::array<int, 5>{DOT, DASH, DASH, DOT, CLEAR}},
    {'q', std::array<int, 5>{DASH, DASH, DOT, DASH, CLEAR}},
    {'r', std::array<int, 5>{DOT, DASH, DOT, CLEAR, CLEAR}},
    {'s', std::array<int, 5>{DOT, DOT, DOT, CLEAR, CLEAR}},
    {'t', std::array<int, 5>{DASH, CLEAR, CLEAR, CLEAR, CLEAR}},
    {'u', std::array<int, 5>{DOT, DOT, DASH, CLEAR, CLEAR}},
    {'v', std::array<int, 5>{DOT, DOT, DOT, DASH, CLEAR}},
    {'w', std::array<int, 5>{DOT, DASH, DASH, CLEAR, CLEAR}},
    {'x', std::array<int, 5>{DASH, DOT, DOT, DASH, CLEAR}},
    {'y', std::array<int, 5>{DASH, DOT, DASH, DASH, CLEAR}},
    {'z', std::array<int, 5>{DASH, DASH, DOT, DOT, CLEAR}}
};

// RGB GPIO
void setColorRGB(long hexColor);
void turnOffLED();
void resetColorRGB();

// Plain GPIO
void turnOffGPIOLEDs();
void resetColorGPIOLEDs();

#endif