#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "esp_log.h"
#include "map.h"

#define TAG "MAP"

static unsigned long char_hash(char c) {
    return (unsigned long)c;
}

char_uint8_array_map_t* char_uint8_array_map_create(size_t capacity) {
    char_uint8_array_map_t *map = (char_uint8_array_map_t*)malloc(sizeof(char_uint8_array_map_t));
    if (!map) {
        ESP_LOGE(TAG, "Failed to allocate map");
        return NULL;
    }
    
    map->buckets = (char_uint8_array_entry_t**)calloc(capacity, sizeof(char_uint8_array_entry_t*));
    if (!map->buckets) {
        ESP_LOGE(TAG, "Failed to allocate buckets");
        free(map);
        return NULL;
    }
    
    map->capacity = capacity;
    map->size = 0;
    return map;
}

void char_uint8_array_map_destroy(char_uint8_array_map_t *map) {
    if (!map) return;
    
    for (size_t i = 0; i < map->capacity; i++) {
        char_uint8_array_entry_t *entry = map->buckets[i];
        while (entry) {
            char_uint8_array_entry_t *next = entry->next;
            free(entry->value_array);
            free(entry);
            entry = next;
        }
    }
    
    free(map->buckets);
    free(map);
}

bool char_uint8_array_map_put(char_uint8_array_map_t *map, char key, const uint8_t *value_array, size_t array_size) {
    if (!map || !value_array || array_size == 0) return false;
    
    unsigned long index = char_hash(key) % map->capacity;
    char_uint8_array_entry_t *entry = map->buckets[index];
    
    // Check if key already exists
    while (entry) {
        if (entry->key == key) {
            // Update existing entry - reallocate array if size changed
            if (entry->array_size != array_size) {
                uint8_t *new_array = (uint8_t*)realloc(entry->value_array, array_size * sizeof(uint8_t));
                if (!new_array) {
                    ESP_LOGE(TAG, "Failed to reallocate array");
                    return false;
                }
                entry->value_array = new_array;
                entry->array_size = array_size;
            }
            memcpy(entry->value_array, value_array, array_size * sizeof(uint8_t));
            return true;
        }
        entry = entry->next;
    }
    
    // Create new entry
    char_uint8_array_entry_t *new_entry = (char_uint8_array_entry_t*)malloc(sizeof(char_uint8_array_entry_t));
    if (!new_entry) {
        ESP_LOGE(TAG, "Failed to allocate new entry");
        return false;
    }
    
    new_entry->value_array = (uint8_t*)malloc(array_size * sizeof(uint8_t));
    if (!new_entry->value_array) {
        ESP_LOGE(TAG, "Failed to allocate value array");
        free(new_entry);
        return false;
    }
    
    new_entry->key = key;
    new_entry->array_size = array_size;
    memcpy(new_entry->value_array, value_array, array_size * sizeof(uint8_t));
    new_entry->next = map->buckets[index];
    map->buckets[index] = new_entry;
    map->size++;
    
    return true;
}

bool char_uint8_array_map_get(char_uint8_array_map_t *map, char key, uint8_t **value_array, size_t *array_size) {
    if (!map || !value_array || !array_size) return false;
    
    unsigned long index = char_hash(key) % map->capacity;
    char_uint8_array_entry_t *entry = map->buckets[index];
    
    while (entry) {
        if (entry->key == key) {
            *value_array = entry->value_array;
            *array_size = entry->array_size;
            return true;
        }
        entry = entry->next;
    }
    
    return false;
}

bool char_uint8_array_map_get_copy(char_uint8_array_map_t *map, char key, uint8_t *output_array, size_t output_size) {
    if (!map || !output_array) return false;
    
    unsigned long index = char_hash(key) % map->capacity;
    char_uint8_array_entry_t *entry = map->buckets[index];
    
    while (entry) {
        if (entry->key == key) {
            size_t copy_size = (output_size < entry->array_size) ? output_size : entry->array_size;
            memcpy(output_array, entry->value_array, copy_size * sizeof(uint8_t));
            return true;
        }
        entry = entry->next;
    }
    
    return false;
}

bool char_uint8_array_map_remove(char_uint8_array_map_t *map, char key) {
    if (!map) return false;
    
    unsigned long index = char_hash(key) % map->capacity;
    char_uint8_array_entry_t *entry = map->buckets[index];
    char_uint8_array_entry_t *prev = NULL;
    
    while (entry) {
        if (entry->key == key) {
            if (prev) {
                prev->next = entry->next;
            } else {
                map->buckets[index] = entry->next;
            }
            
            free(entry->value_array);
            free(entry);
            map->size--;
            return true;
        }
        prev = entry;
        entry = entry->next;
    }
    
    return false;
}

size_t char_uint8_array_map_size(char_uint8_array_map_t *map) {
    return map ? map->size : 0;
}

bool char_uint8_array_map_contains(char_uint8_array_map_t *map, char key) {
    if (!map) return false;
    
    unsigned long index = char_hash(key) % map->capacity;
    char_uint8_array_entry_t *entry = map->buckets[index];
    
    while (entry) {
        if (entry->key == key) {
            return true;
        }
        entry = entry->next;
    }
    
    return false;
}

bool char_uint8_array_map_update_element(char_uint8_array_map_t *map, char key, size_t index, uint8_t value) {
    if (!map) return false;
    
    unsigned long hash_index = char_hash(key) % map->capacity;
    char_uint8_array_entry_t *entry = map->buckets[hash_index];
    
    while (entry) {
        if (entry->key == key) {
            if (index < entry->array_size) {
                entry->value_array[index] = value;
                return true;
            }
            return false; // Index out of bounds
        }
        entry = entry->next;
    }
    
    return false; // Key not found
}

void char_uint8_array_map_foreach(char_uint8_array_map_t *map, void (*callback)(char key, const uint8_t *value_array, size_t array_size, void *userdata), void *userdata) {
    if (!map || !callback) return;
    
    for (size_t i = 0; i < map->capacity; i++) {
        char_uint8_array_entry_t *entry = map->buckets[i];
        while (entry) {
            callback(entry->key, entry->value_array, entry->array_size, userdata);
            entry = entry->next;
        }
    }
}