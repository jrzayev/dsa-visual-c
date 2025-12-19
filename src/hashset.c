#include "dsa_visual.h"

static unsigned int hashset_hash(HashSet* set, int value) {
    unsigned int hash = (unsigned int)(value < 0 ? -value : value);
    return hash % set->capacity;
}

HashSet* hashset_create(int capacity) {
    HashSet* set = (HashSet*)malloc(sizeof(HashSet));
    set->buckets = (SetEntry**)calloc(capacity, sizeof(SetEntry*));
    set->capacity = capacity;
    set->size = 0;
    return set;
}

int hashset_add(HashSet* set, int value) {
    unsigned int index = hashset_hash(set, value);
    
    printf(CYAN "Adding value %d\n" RESET, value);
    printf("  Hash(%d) = %u\n", value, index);
    
    SetEntry* current = set->buckets[index];
    while (current != NULL) {
        if (current->value == value) {
            printf(YELLOW "⚠ Value %d already exists in set\n" RESET, value);
            hashset_visualize(set);
            return 0;
        }
        current = current->next;
    }
    
    SetEntry* new_entry = (SetEntry*)malloc(sizeof(SetEntry));
    new_entry->value = value;
    new_entry->next = set->buckets[index];
    set->buckets[index] = new_entry;
    set->size++;
    
    printf(GREEN "✓ Added %d at bucket[%u]\n" RESET, value, index);
    hashset_visualize(set);
    return 1;
}

int hashset_remove(HashSet* set, int value) {
    unsigned int index = hashset_hash(set, value);
    
    printf(CYAN "Removing value %d\n" RESET, value);
    printf("  Hash(%d) = %u\n", value, index);
    
    SetEntry* current = set->buckets[index];
    SetEntry* prev = NULL;
    
    while (current != NULL) {
        if (current->value == value) {
            if (prev == NULL) {
                set->buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }
            
            printf(GREEN "✓ Removed %d\n" RESET, value);
            free(current);
            set->size--;
            
            hashset_visualize(set);
            return 1;
        }
        prev = current;
        current = current->next;
    }
    
    printf(RED "✗ Value %d not found\n" RESET, value);
    return 0;
}

int hashset_contains(HashSet* set, int value) {
    unsigned int index = hashset_hash(set, value);
    
    printf(CYAN "Checking if %d exists\n" RESET, value);
    printf("  Hash(%d) = %u\n", value, index);
    
    SetEntry* current = set->buckets[index];
    int steps = 0;
    
    while (current != NULL) {
        steps++;
        printf("  Step %d: Checking %d\n", steps, current->value);
        
        if (current->value == value) {
            printf(GREEN "✓ Found %d in set\n" RESET, value);
            return 1;
        }
        current = current->next;
    }
    
    printf(RED "✗ Value %d not in set\n" RESET, value);
    return 0;
}

HashSet* hashset_union(HashSet* set1, HashSet* set2) {
    printf(CYAN "\nComputing Union of two sets...\n" RESET);
    
    int new_capacity = set1->capacity > set2->capacity ? set1->capacity : set2->capacity;
    HashSet* result = hashset_create(new_capacity);
    
    for (int i = 0; i < set1->capacity; i++) {
        SetEntry* current = set1->buckets[i];
        while (current != NULL) {
            unsigned int index = hashset_hash(result, current->value);
            SetEntry* new_entry = (SetEntry*)malloc(sizeof(SetEntry));
            new_entry->value = current->value;
            new_entry->next = result->buckets[index];
            result->buckets[index] = new_entry;
            result->size++;
            current = current->next;
        }
    }
    
    for (int i = 0; i < set2->capacity; i++) {
        SetEntry* current = set2->buckets[i];
        while (current != NULL) {
            if (!hashset_contains_silent(result, current->value)) {
                unsigned int index = hashset_hash(result, current->value);
                SetEntry* new_entry = (SetEntry*)malloc(sizeof(SetEntry));
                new_entry->value = current->value;
                new_entry->next = result->buckets[index];
                result->buckets[index] = new_entry;
                result->size++;
            }
            current = current->next;
        }
    }
    
    printf(GREEN "✓ Union complete\n" RESET);
    return result;
}

HashSet* hashset_intersection(HashSet* set1, HashSet* set2) {
    printf(CYAN "\nComputing Intersection of two sets...\n" RESET);
    
    int new_capacity = set1->capacity < set2->capacity ? set1->capacity : set2->capacity;
    HashSet* result = hashset_create(new_capacity);
    
    for (int i = 0; i < set1->capacity; i++) {
        SetEntry* current = set1->buckets[i];
        while (current != NULL) {
            if (hashset_contains_silent(set2, current->value)) {
                unsigned int index = hashset_hash(result, current->value);
                SetEntry* new_entry = (SetEntry*)malloc(sizeof(SetEntry));
                new_entry->value = current->value;
                new_entry->next = result->buckets[index];
                result->buckets[index] = new_entry;
                result->size++;
            }
            current = current->next;
        }
    }
    
    printf(GREEN "✓ Intersection complete\n" RESET);
    return result;
}

int hashset_contains_silent(HashSet* set, int value) {
    unsigned int index = hashset_hash(set, value);
    SetEntry* current = set->buckets[index];
    
    while (current != NULL) {
        if (current->value == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void hashset_visualize(HashSet* set) {
    printf("\n" CYAN "HashSet (Size: %d, Capacity: %d):\n" RESET, set->size, set->capacity);
    
    printf("  { ");
    int first = 1;
    for (int i = 0; i < set->capacity; i++) {
        SetEntry* current = set->buckets[i];
        while (current != NULL) {
            if (!first) printf(", ");
            printf(BG_GREEN " %d " RESET, current->value);
            first = 0;
            current = current->next;
        }
    }
    if (first) printf(YELLOW "EMPTY" RESET);
    printf(" }\n");
    
    printf("\n  Buckets:\n");
    for (int i = 0; i < set->capacity; i++) {
        printf("  [%2d] → ", i);
        if (set->buckets[i] == NULL) {
            printf(YELLOW "NULL\n" RESET);
        } else {
            SetEntry* current = set->buckets[i];
            while (current != NULL) {
                printf(BG_BLUE " %d " RESET, current->value);
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

void hashset_free(HashSet* set) {
    for (int i = 0; i < set->capacity; i++) {
        SetEntry* current = set->buckets[i];
        while (current != NULL) {
            SetEntry* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(set->buckets);
    free(set);
}
