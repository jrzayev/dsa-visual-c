#include "dsa_visual.h"

Stack* stack_create(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (int*)malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void stack_push(Stack* stack, int data) {
    if (stack_is_full(stack)) {
        printf(RED "✗ Stack Overflow! Cannot push %d\n" RESET, data);
        return;
    }
    
    stack->data[++stack->top] = data;
    printf(GREEN "✓ Pushed %d onto stack\n" RESET, data);
    stack_visualize(stack);
}

int stack_pop(Stack* stack) {
    if (stack_is_empty(stack)) {
        printf(RED "✗ Stack Underflow! Stack is empty\n" RESET);
        return -1;
    }
    
    int popped = stack->data[stack->top--];
    printf(YELLOW "✓ Popped %d from stack\n" RESET, popped);
    stack_visualize(stack);
    return popped;
}

int stack_peek(Stack* stack) {
    if (stack_is_empty(stack)) {
        printf(RED "✗ Stack is empty!\n" RESET);
        return -1;
    }
    return stack->data[stack->top];
}

int stack_is_empty(Stack* stack) {
    return stack->top == -1;
}

int stack_is_full(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

void stack_visualize(Stack* stack) {
    printf("\n" CYAN "Stack (Size: %d/%d):\n" RESET, stack->top + 1, stack->capacity);
    
    if (stack_is_empty(stack)) {
        printf("  " YELLOW "[EMPTY]\n" RESET);
        printf("\n");
        return;
    }
    
    printf("  ┌─────┐\n");
    for (int i = stack->top; i >= 0; i--) {
        if (i == stack->top) {
            printf("  │" BG_GREEN " %3d " RESET "│ ← TOP\n", stack->data[i]);
        } else {
            printf("  │" BG_BLUE " %3d " RESET "│\n", stack->data[i]);
        }
        printf("  ├─────┤\n");
    }
    printf("  └─────┘\n\n");
}

void stack_free(Stack* stack) {
    free(stack->data);
    free(stack);
}
