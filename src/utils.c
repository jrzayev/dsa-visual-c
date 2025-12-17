#include "dsa_visual.h"

void clear_screen() {
    printf("\033[2J\033[H");
}

void print_header(const char* title) {
    printf("\n");
    printf(CYAN "╔══════════════════════════════════════════════════════════════╗\n" RESET);
    printf(CYAN "║" YELLOW "  %-58s" CYAN "║\n" RESET, title);
    printf(CYAN "╚══════════════════════════════════════════════════════════════╝\n" RESET);
    printf("\n");
}

void pause_execution() {
    usleep(500000);
}

void visualize_array(int arr[], int size, int highlight1, int highlight2) {
    printf("\n");

    printf("  ");
    for (int i = 0; i < size; i++) {
        if (i == highlight1 || i == highlight2) {
            printf(BG_YELLOW " %3d " RESET " ", arr[i]);
        } else {
            printf(BG_BLUE " %3d " RESET " ", arr[i]);
        }
    }
    printf("\n");

    printf("  ");
    for (int i = 0; i < size; i++) {
        printf("  %2d   ", i);
    }
    printf("\n\n");
}
