#include "dsa_visual.h"

static unsigned int hash_function(HashMap* map, const char* key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + *key;
        key++;
    }
    return hash % map->capacity;
}

HashMap* hashmap_create(int capacity) {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    map->buckets = (HashEntry**)calloc(capacity, sizeof(HashEntry*));
    map->capacity = capacity;
    map->size = 0;
    return map;
}

void hashmap_put(HashMap* map, const char* key, int value) {
    unsigned int index = hash_function(map, key);
    
    printf(CYAN "Inserting key '%s' with value %d\n" RESET, key, value);
    printf("  Hash('%s') = %u\n", key, index);
    
    HashEntry* current = map->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            printf(YELLOW "  ⚠ Key exists, updating value: %d → %d\n" RESET, current->value, value);
            current->value = value;
            hashmap_visualize(map);
            return;
        }
        current = current->next;
    }
    
    HashEntry* new_entry = (HashEntry*)malloc(sizeof(HashEntry));
    new_entry->key = strdup(key);
    new_entry->value = value;
    new_entry->next = map->buckets[index];
    map->buckets[index] = new_entry;
    map->size++;
    
    printf(GREEN "✓ Inserted at bucket[%u]\n" RESET, index);
    hashmap_visualize(map);
}

int hashmap_get(HashMap* map, const char* key, int* found) {
    unsigned int index = hash_function(map, key);
    
    printf(CYAN "Getting key '%s'\n" RESET, key);
    printf("  Hash('%s') = %u\n", key, index);
    
    HashEntry* current = map->buckets[index];
    int steps = 0;
    
    while (current != NULL) {
        steps++;
        printf("  Step %d: Checking '%s'\n", steps, current->key);
        
        if (strcmp(current->key, key) == 0) {
            printf(GREEN "✓ Found '%s' = %d\n" RESET, key, current->value);
            if (found) *found = 1;
            return current->value;
        }
        current = current->next;
    }
    
    printf(RED "✗ Key '%s' not found\n" RESET, key);
    if (found) *found = 0;
    return -1;
}

int hashmap_remove(HashMap* map, const char* key) {
    unsigned int index = hash_function(map, key);
    
    printf(CYAN "Removing key '%s'\n" RESET, key);
    printf("  Hash('%s') = %u\n", key, index);
    
    HashEntry* current = map->buckets[index];
    HashEntry* prev = NULL;
    
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) {
                map->buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }
            
            int value = current->value;
            printf(GREEN "✓ Removed '%s' = %d\n" RESET, key, value);
            
            free(current->key);
            free(current);
            map->size--;
            
            hashmap_visualize(map);
            return value;
        }
        prev = current;
        current = current->next;
    }
    
    printf(RED "✗ Key '%s' not found\n" RESET, key);
    return -1;
}

int hashmap_contains(HashMap* map, const char* key) {
    unsigned int index = hash_function(map, key);
    HashEntry* current = map->buckets[index];
    
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void hashmap_visualize(HashMap* map) {
    printf("\n" CYAN "HashMap (Size: %d, Capacity: %d, Load: %.2f):\n" RESET, 
           map->size, map->capacity, (float)map->size / map->capacity);
    
    for (int i = 0; i < map->capacity; i++) {
        printf("  [%2d] → ", i);
        
        if (map->buckets[i] == NULL) {
            printf(YELLOW "NULL\n" RESET);
        } else {
            HashEntry* current = map->buckets[i];
            while (current != NULL) {
                printf(BG_BLUE " %s:%d " RESET, current->key, current->value);
                if (current->next != NULL) {
                    printf(" → ");
                }
                current = current->next;
            }
            printf("\n");
        }
    }
    printf("\n");
}

void hashmap_free(HashMap* map) {
    for (int i = 0; i < map->capacity; i++) {
        HashEntry* current = map->buckets[i];
        while (current != NULL) {
            HashEntry* temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    free(map->buckets);
    free(map);
}
