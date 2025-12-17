#include "dsa_visual.h"

Queue* queue_create(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->data = (int*)malloc(capacity * sizeof(int));
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

void queue_enqueue(Queue* queue, int data) {
    if (queue_is_full(queue)) {
        printf(RED "✗ Queue Overflow! Cannot enqueue %d\n" RESET, data);
        return;
    }
    
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = data;
    queue->size++;
    
    printf(GREEN "✓ Enqueued %d\n" RESET, data);
    queue_visualize(queue);
}

int queue_dequeue(Queue* queue) {
    if (queue_is_empty(queue)) {
        printf(RED "✗ Queue Underflow! Queue is empty\n" RESET);
        return -1;
    }
    
    int dequeued = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    
    printf(YELLOW "✓ Dequeued %d\n" RESET, dequeued);
    queue_visualize(queue);
    return dequeued;
}

int queue_peek(Queue* queue) {
    if (queue_is_empty(queue)) {
        printf(RED "✗ Queue is empty!\n" RESET);
        return -1;
    }
    return queue->data[queue->front];
}

int queue_is_empty(Queue* queue) {
    return queue->size == 0;
}

int queue_is_full(Queue* queue) {
    return queue->size == queue->capacity;
}

void queue_visualize(Queue* queue) {
    printf("\n" CYAN "Queue (Size: %d/%d):\n" RESET, queue->size, queue->capacity);
    
    if (queue_is_empty(queue)) {
        printf("  " YELLOW "[EMPTY]\n" RESET);
        printf("\n");
        return;
    }
    
    printf("  FRONT → ");
    
    for (int i = 0; i < queue->size; i++) {
        int index = (queue->front + i) % queue->capacity;
        if (i == 0) {
            printf(BG_GREEN " %3d " RESET " → ", queue->data[index]);
        } else if (i == queue->size - 1) {
            printf(BG_YELLOW " %3d " RESET " ← REAR", queue->data[index]);
        } else {
            printf(BG_BLUE " %3d " RESET " → ", queue->data[index]);
        }
    }
    printf("\n\n");
}

void queue_free(Queue* queue) {
    free(queue->data);
    free(queue);
}
