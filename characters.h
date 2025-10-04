#ifndef CHARACTERS_H
#define CHARACTERS_H

#define ROW_SIZE 5

char characters[] = {
    'a', 
    'b'
};

#define COLUMN_SIZE (sizeof(characters) / sizeof(characters[0]))

uint8_t character_bindings[COLUMN_SIZE][ROW_SIZE] = {
    {1, 1, 1, 1, 1}, // a
    {1, 1, 1, 1, 1}  // b
};

#endif