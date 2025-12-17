#include "dsa_visual.h"

int linear_search(int arr[], int size, int target) {
    printf(CYAN "\n=== LINEAR SEARCH ===\n" RESET);
    printf("Searching for: " YELLOW "%d\n" RESET, target);
    printf("\nInitial array:\n");
    visualize_array(arr, size, -1, -1);
    
    for (int i = 0; i < size; i++) {
        printf("Step %d: Checking arr[%d] = %d\n", i + 1, i, arr[i]);
        visualize_array(arr, size, i, -1);
        
        if (arr[i] == target) {
            printf(GREEN "\n✓ Found %d at index %d!\n" RESET, target, i);
            printf(GREEN "Total comparisons: %d\n\n" RESET, i + 1);
            return i;
        }
        
        printf("  → Not a match, continue searching...\n");
        usleep(400000);
    }
    
    printf(RED "\n✗ Element %d not found in array\n" RESET, target);
    printf(YELLOW "Total comparisons: %d\n\n" RESET, size);
    return -1;
}

int binary_search(int arr[], int size, int target) {
    printf(CYAN "\n=== BINARY SEARCH ===\n" RESET);
    printf("Searching for: " YELLOW "%d\n" RESET, target);
    printf(MAGENTA "Note: Array must be sorted for binary search!\n" RESET);
    printf("\nInitial array:\n");
    visualize_array(arr, size, -1, -1);
    
    int left = 0;
    int right = size - 1;
    int comparisons = 0;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        comparisons++;
        
        printf("\nStep %d:\n", comparisons);
        printf("  Left = %d, Right = %d, Mid = %d\n", left, right, mid);
        printf("  Checking arr[%d] = %d\n", mid, arr[mid]);
        visualize_array(arr, size, mid, -1);
        
        if (arr[mid] == target) {
            printf(GREEN "\n✓ Found %d at index %d!\n" RESET, target, mid);
            printf(GREEN "Total comparisons: %d\n\n" RESET, comparisons);
            return mid;
        }
        
        if (arr[mid] < target) {
            printf("  → %d > %d, search right half\n", target, arr[mid]);
            left = mid + 1;
        } else {
            printf("  → %d < %d, search left half\n", target, arr[mid]);
            right = mid - 1;
        }
        
        usleep(500000);
    }
    
    printf(RED "\n✗ Element %d not found in array\n" RESET, target);
    printf(YELLOW "Total comparisons: %d\n\n" RESET, comparisons);
    return -1;
}
