#include "dsa_visual.h"

LinkedList* ll_create() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->size = 0;
    return list;
}

void ll_insert_front(LinkedList* list, int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
    
    printf(GREEN "✓ Inserted %d at front\n" RESET, data);
    ll_visualize(list);
}

void ll_insert_back(LinkedList* list, int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->size++;
    
    printf(GREEN "✓ Inserted %d at back\n" RESET, data);
    ll_visualize(list);
}

void ll_insert_at(LinkedList* list, int data, int position) {
    if (position < 0 || position > list->size) {
        printf(RED "✗ Invalid position!\n" RESET);
        return;
    }
    
    if (position == 0) {
        ll_insert_front(list, data);
        return;
    }
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    
    Node* current = list->head;
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }
    
    new_node->next = current->next;
    current->next = new_node;
    list->size++;
    
    printf(GREEN "✓ Inserted %d at position %d\n" RESET, data, position);
    ll_visualize(list);
}

void ll_delete_front(LinkedList* list) {
    if (list->head == NULL) {
        printf(RED "✗ List is empty!\n" RESET);
        return;
    }
    
    Node* temp = list->head;
    int deleted_data = temp->data;
    list->head = list->head->next;
    free(temp);
    list->size--;
    
    printf(YELLOW "✓ Deleted %d from front\n" RESET, deleted_data);
    ll_visualize(list);
}

void ll_delete_back(LinkedList* list) {
    if (list->head == NULL) {
        printf(RED "✗ List is empty!\n" RESET);
        return;
    }
    
    if (list->head->next == NULL) {
        int deleted_data = list->head->data;
        free(list->head);
        list->head = NULL;
        list->size--;
        printf(YELLOW "✓ Deleted %d from back\n" RESET, deleted_data);
        ll_visualize(list);
        return;
    }
    
    Node* current = list->head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    
    int deleted_data = current->next->data;
    free(current->next);
    current->next = NULL;
    list->size--;
    
    printf(YELLOW "✓ Deleted %d from back\n" RESET, deleted_data);
    ll_visualize(list);
}

void ll_delete_at(LinkedList* list, int position) {
    if (position < 0 || position >= list->size) {
        printf(RED "✗ Invalid position!\n" RESET);
        return;
    }
    
    if (position == 0) {
        ll_delete_front(list);
        return;
    }
    
    Node* current = list->head;
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }
    
    Node* temp = current->next;
    int deleted_data = temp->data;
    current->next = temp->next;
    free(temp);
    list->size--;
    
    printf(YELLOW "✓ Deleted %d from position %d\n" RESET, deleted_data, position);
    ll_visualize(list);
}

int ll_search(LinkedList* list, int data) {
    Node* current = list->head;
    int position = 0;
    
    while (current != NULL) {
        if (current->data == data) {
            printf(GREEN "✓ Found %d at position %d\n" RESET, data, position);
            return position;
        }
        current = current->next;
        position++;
    }
    
    printf(RED "✗ Element %d not found\n" RESET, data);
    return -1;
}

void ll_visualize(LinkedList* list) {
    printf("\n" CYAN "Linked List (Size: %d):\n" RESET, list->size);
    
    if (list->head == NULL) {
        printf("  " YELLOW "[EMPTY]\n" RESET);
        printf("\n");
        return;
    }
    
    printf("  HEAD → ");
    
    Node* current = list->head;
    while (current != NULL) {
        printf(BG_BLUE " %3d " RESET " → ", current->data);
        current = current->next;
    }
    printf("NULL\n\n");
}

void ll_free(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}
