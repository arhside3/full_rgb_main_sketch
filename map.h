#ifndef MAP_H
#define MAP_H

#include <stdbool.h>

typedef struct char_uint8_array_entry_t {
    char key;
    uint8_t *value_array;
    size_t array_size;
    struct char_uint8_array_entry_t *next;
} char_uint8_array_entry_t;

typedef struct {
    char_uint8_array_entry_t **buckets;
    size_t capacity;
    size_t size;
} char_uint8_array_map_t;

// Function declarations
char_uint8_array_map_t* char_uint8_array_map_create(size_t capacity);
void char_uint8_array_map_destroy(char_uint8_array_map_t *map);
bool char_uint8_array_map_put(char_uint8_array_map_t *map, char key, const uint8_t *value_array, size_t array_size);
bool char_uint8_array_map_get(char_uint8_array_map_t *map, char key, uint8_t **value_array, size_t *array_size);
bool char_uint8_array_map_get_copy(char_uint8_array_map_t *map, char key, uint8_t *output_array, size_t output_size);
bool char_uint8_array_map_remove(char_uint8_array_map_t *map, char key);
size_t char_uint8_array_map_size(char_uint8_array_map_t *map);
void char_uint8_array_map_foreach(char_uint8_array_map_t *map, void (*callback)(char key, const uint8_t *value_array, size_t array_size, void *userdata), void *userdata);
bool char_uint8_array_map_contains(char_uint8_array_map_t *map, char key);
bool char_uint8_array_map_update_element(char_uint8_array_map_t *map, char key, size_t index, uint8_t value);
#endif