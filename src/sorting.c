#include "dsa_visual.h"

void bubble_sort(int arr[], int size) {
    printf(CYAN "\n=== BUBBLE SORT ===\n" RESET);
    printf("Initial array:\n");
    visualize_array(arr, size, -1, -1);

    for (int i = 0; i < size - 1; i++) {
        printf(YELLOW "Pass %d:\n" RESET, i + 1);
        int swapped = 0;

        for (int j = 0; j < size - i - 1; j++) {
            printf("  Comparing arr[%d]=%d with arr[%d]=%d\n", j, arr[j], j+1, arr[j+1]);
            visualize_array(arr, size, j, j + 1);

            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
                printf(GREEN "  → Swapped!\n" RESET);
            } else {
                printf("  → No swap needed\n");
            }
            usleep(300000);
        }

        if (!swapped) {
            printf(GREEN "✓ Array is sorted!\n" RESET);
            break;
        }
    }

    printf("\n" GREEN "Final sorted array:\n" RESET);
    visualize_array(arr, size, -1, -1);
}

void selection_sort(int arr[], int size) {
    printf(CYAN "\n=== SELECTION SORT ===\n" RESET);
    printf("Initial array:\n");
    visualize_array(arr, size, -1, -1);

    for (int i = 0; i < size - 1; i++) {
        int min_idx = i;
        printf(YELLOW "Pass %d: Finding minimum from position %d\n" RESET, i + 1, i);

        for (int j = i + 1; j < size; j++) {
            visualize_array(arr, size, min_idx, j);

            if (arr[j] < arr[min_idx]) {
                min_idx = j;
                printf("  New minimum found: arr[%d]=%d\n", min_idx, arr[min_idx]);
            }
            usleep(200000);
        }

        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
            printf(GREEN "  → Swapped arr[%d] with arr[%d]\n" RESET, i, min_idx);
        }

        visualize_array(arr, size, i, -1);
        usleep(300000);
    }

    printf("\n" GREEN "Final sorted array:\n" RESET);
    visualize_array(arr, size, -1, -1);
}

void insertion_sort(int arr[], int size) {
    printf(CYAN "\n=== INSERTION SORT ===\n" RESET);
    printf("Initial array:\n");
    visualize_array(arr, size, -1, -1);

    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;

        printf(YELLOW "Pass %d: Inserting %d into sorted portion\n" RESET, i, key);
        visualize_array(arr, size, i, -1);

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            visualize_array(arr, size, j + 1, i);
            usleep(200000);
        }

        arr[j + 1] = key;
        printf(GREEN "  → Inserted %d at position %d\n" RESET, key, j + 1);
        visualize_array(arr, size, j + 1, -1);
        usleep(300000);
    }

    printf("\n" GREEN "Final sorted array:\n" RESET);
    visualize_array(arr, size, -1, -1);
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    printf("  Pivot = %d\n", pivot);

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quick_sort_helper(int arr[], int low, int high, int size) {
    if (low < high) {
        printf(YELLOW "Partitioning from index %d to %d\n" RESET, low, high);
        int pi = partition(arr, low, high);

        visualize_array(arr, size, pi, -1);
        usleep(400000);

        quick_sort_helper(arr, low, pi - 1, size);
        quick_sort_helper(arr, pi + 1, high, size);
    }
}

void quick_sort(int arr[], int low, int high) {
    int size = high + 1;
    printf(CYAN "\n=== QUICK SORT ===\n" RESET);
    printf("Initial array:\n");
    visualize_array(arr, size, -1, -1);

    quick_sort_helper(arr, low, high, size);

    printf("\n" GREEN "Final sorted array:\n" RESET);
    visualize_array(arr, size, -1, -1);
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void merge_sort_helper(int arr[], int left, int right, int size) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        printf(YELLOW "Dividing: [%d-%d]\n" RESET, left, right);
        visualize_array(arr, size, left, right);
        usleep(300000);

        merge_sort_helper(arr, left, mid, size);
        merge_sort_helper(arr, mid + 1, right, size);

        printf(GREEN "Merging: [%d-%d-%d]\n" RESET, left, mid, right);
        merge(arr, left, mid, right);
        visualize_array(arr, size, left, right);
        usleep(300000);
    }
}

void merge_sort(int arr[], int left, int right) {
    int size = right + 1;
    printf(CYAN "\n=== MERGE SORT ===\n" RESET);
    printf("Initial array:\n");
    visualize_array(arr, size, -1, -1);

    merge_sort_helper(arr, left, right, size);

    printf("\n" GREEN "Final sorted array:\n" RESET);
    visualize_array(arr, size, -1, -1);
}
