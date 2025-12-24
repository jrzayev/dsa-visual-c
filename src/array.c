#include "dsa_visual.h"

DynamicArray* array_create(int initial_capacity) {
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    arr->data = (int*)malloc(initial_capacity * sizeof(int));
    arr->size = 0;
    arr->capacity = initial_capacity;
    
    printf(GREEN "✓ Created dynamic array with capacity %d\n" RESET, initial_capacity);
    return arr;
}

static void array_resize(DynamicArray* arr, int new_capacity) {
    printf(YELLOW "  ⚡ Resizing array: %d → %d\n" RESET, arr->capacity, new_capacity);
    
    int* new_data = (int*)malloc(new_capacity * sizeof(int));
    for (int i = 0; i < arr->size; i++) {
        new_data[i] = arr->data[i];
    }
    
    free(arr->data);
    arr->data = new_data;
    arr->capacity = new_capacity;
}

void array_push_back(DynamicArray* arr, int value) {
    printf(CYAN "Pushing %d to back\n" RESET, value);
    
    if (arr->size >= arr->capacity) {
        array_resize(arr, arr->capacity * 2);
    }
    
    arr->data[arr->size++] = value;
    printf(GREEN "✓ Pushed %d at index %d\n" RESET, value, arr->size - 1);
    array_visualize(arr);
}

void array_push_front(DynamicArray* arr, int value) {
    printf(CYAN "Pushing %d to front\n" RESET, value);
    
    if (arr->size >= arr->capacity) {
        array_resize(arr, arr->capacity * 2);
    }
    
    for (int i = arr->size; i > 0; i--) {
        arr->data[i] = arr->data[i - 1];
    }
    
    arr->data[0] = value;
    arr->size++;
    
    printf(GREEN "✓ Pushed %d at front (shifted %d elements)\n" RESET, value, arr->size - 1);
    array_visualize(arr);
}

void array_insert_at(DynamicArray* arr, int index, int value) {
    if (index < 0 || index > arr->size) {
        printf(RED "✗ Invalid index %d (size: %d)\n" RESET, index, arr->size);
        return;
    }
    
    printf(CYAN "Inserting %d at index %d\n" RESET, value, index);
    
    if (arr->size >= arr->capacity) {
        array_resize(arr, arr->capacity * 2);
    }
    
    for (int i = arr->size; i > index; i--) {
        arr->data[i] = arr->data[i - 1];
    }
    
    arr->data[index] = value;
    arr->size++;
    
    printf(GREEN "✓ Inserted %d at index %d\n" RESET, value, index);
    array_visualize(arr);
}

int array_pop_back(DynamicArray* arr) {
    if (arr->size == 0) {
        printf(RED "✗ Array is empty!\n" RESET);
        return -1;
    }
    
    int value = arr->data[--arr->size];
    printf(YELLOW "✓ Popped %d from back\n" RESET, value);
    
    if (arr->size > 0 && arr->size <= arr->capacity / 4) {
        array_resize(arr, arr->capacity / 2);
    }
    
    array_visualize(arr);
    return value;
}

int array_pop_front(DynamicArray* arr) {
    if (arr->size == 0) {
        printf(RED "✗ Array is empty!\n" RESET);
        return -1;
    }
    
    int value = arr->data[0];
    
    for (int i = 0; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }
    arr->size--;
    
    printf(YELLOW "✓ Popped %d from front (shifted %d elements)\n" RESET, value, arr->size);
    
    if (arr->size > 0 && arr->size <= arr->capacity / 4) {
        array_resize(arr, arr->capacity / 2);
    }
    
    array_visualize(arr);
    return value;
}

int array_remove_at(DynamicArray* arr, int index) {
    if (index < 0 || index >= arr->size) {
        printf(RED "✗ Invalid index %d (size: %d)\n" RESET, index, arr->size);
        return -1;
    }
    
    int value = arr->data[index];
    printf(CYAN "Removing element at index %d\n" RESET, index);
    
    for (int i = index; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }
    arr->size--;
    
    printf(YELLOW "✓ Removed %d from index %d\n" RESET, value, index);
    
    if (arr->size > 0 && arr->size <= arr->capacity / 4) {
        array_resize(arr, arr->capacity / 2);
    }
    
    array_visualize(arr);
    return value;
}

int array_get(DynamicArray* arr, int index) {
    if (index < 0 || index >= arr->size) {
        printf(RED "✗ Index %d out of bounds (size: %d)\n" RESET, index, arr->size);
        return -1;
    }
    
    printf(GREEN "✓ arr[%d] = %d\n" RESET, index, arr->data[index]);
    return arr->data[index];
}

void array_set(DynamicArray* arr, int index, int value) {
    if (index < 0 || index >= arr->size) {
        printf(RED "✗ Index %d out of bounds (size: %d)\n" RESET, index, arr->size);
        return;
    }
    
    int old_value = arr->data[index];
    arr->data[index] = value;
    printf(GREEN "✓ arr[%d]: %d → %d\n" RESET, index, old_value, value);
    array_visualize(arr);
}

int array_search(DynamicArray* arr, int value) {
    printf(CYAN "Searching for %d\n" RESET, value);
    
    for (int i = 0; i < arr->size; i++) {
        printf("  Checking index %d: %d\n", i, arr->data[i]);
        usleep(200000);
        
        if (arr->data[i] == value) {
            printf(GREEN "✓ Found %d at index %d\n" RESET, value, i);
            return i;
        }
    }
    
    printf(RED "✗ Value %d not found\n" RESET, value);
    return -1;
}

void array_reverse(DynamicArray* arr) {
    printf(CYAN "Reversing array\n" RESET);
    
    int left = 0, right = arr->size - 1;
    
    while (left < right) {
        printf("  Swapping arr[%d]=%d ↔ arr[%d]=%d\n", 
               left, arr->data[left], right, arr->data[right]);
        
        int temp = arr->data[left];
        arr->data[left] = arr->data[right];
        arr->data[right] = temp;
        
        left++;
        right--;
        usleep(300000);
    }
    
    printf(GREEN "✓ Array reversed\n" RESET);
    array_visualize(arr);
}

void array_visualize(DynamicArray* arr) {
    printf("\n" CYAN "Dynamic Array (Size: %d, Capacity: %d):\n" RESET, arr->size, arr->capacity);
    
    if (arr->size == 0) {
        printf("  " YELLOW "[EMPTY]\n" RESET);
        printf("\n");
        return;
    }
    
    printf("  ");
    for (int i = 0; i < arr->capacity; i++) {
        if (i < arr->size) {
            printf(BG_BLUE " %3d " RESET " ", arr->data[i]);
        } else {
            printf(YELLOW " --- " RESET " ");
        }
    }
    printf("\n");
    
    printf("  ");
    for (int i = 0; i < arr->capacity; i++) {
        printf("  %2d   ", i);
    }
    printf("\n");
    
    printf("  ");
    for (int i = 0; i < arr->capacity; i++) {
        if (i < arr->size) {
            printf(GREEN " used " RESET " ");
        } else {
            printf(YELLOW " free " RESET " ");
        }
    }
    printf("\n\n");
}

void array_free(DynamicArray* arr) {
    free(arr->data);
    free(arr);
}
