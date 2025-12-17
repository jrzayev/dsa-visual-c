#include "dsa_visual.h"

void demo_linked_list() {
    clear_screen();
    print_header("LINKED LIST DEMONSTRATION");

    LinkedList* list = ll_create();

    ll_insert_back(list, 10);
    usleep(800000);

    ll_insert_back(list, 20);
    usleep(800000);

    ll_insert_front(list, 5);
    usleep(800000);

    ll_insert_at(list, 15, 2);
    usleep(800000);

    printf("\n" CYAN "Searching for element 15...\n" RESET);
    ll_search(list, 15);
    usleep(1000000);

    printf("\n" CYAN "Searching for element 100...\n" RESET);
    ll_search(list, 100);
    usleep(1000000);

    ll_delete_at(list, 1);
    usleep(800000);

    ll_delete_front(list);
    usleep(800000);

    ll_delete_back(list);
    usleep(800000);

    ll_free(list);

    printf("\n" GREEN "Press Enter to continue..." RESET);
    getchar();
}

void demo_stack() {
    clear_screen();
    print_header("STACK DEMONSTRATION");

    Stack* stack = stack_create(5);

    stack_push(stack, 10);
    usleep(800000);

    stack_push(stack, 20);
    usleep(800000);

    stack_push(stack, 30);
    usleep(800000);

    stack_push(stack, 40);
    usleep(800000);

    printf("\n" CYAN "Peek top element:\n" RESET);
    printf("  Top element: " YELLOW "%d\n\n" RESET, stack_peek(stack));
    usleep(1000000);

    stack_pop(stack);
    usleep(800000);

    stack_pop(stack);
    usleep(800000);

    stack_push(stack, 50);
    usleep(800000);

    stack_free(stack);

    printf("\n" GREEN "Press Enter to continue..." RESET);
    getchar();
}

void demo_queue() {
    clear_screen();
    print_header("QUEUE DEMONSTRATION");

    Queue* queue = queue_create(5);

    queue_enqueue(queue, 10);
    usleep(800000);

    queue_enqueue(queue, 20);
    usleep(800000);

    queue_enqueue(queue, 30);
    usleep(800000);

    queue_enqueue(queue, 40);
    usleep(800000);

    printf("\n" CYAN "Peek front element:\n" RESET);
    printf("  Front element: " YELLOW "%d\n\n" RESET, queue_peek(queue));
    usleep(1000000);

    queue_dequeue(queue);
    usleep(800000);

    queue_dequeue(queue);
    usleep(800000);

    queue_enqueue(queue, 50);
    usleep(800000);

    queue_enqueue(queue, 60);
    usleep(800000);

    queue_free(queue);

    printf("\n" GREEN "Press Enter to continue..." RESET);
    getchar();
}

void demo_binary_tree() {
    clear_screen();
    print_header("BINARY TREE DEMONSTRATION");

    BinaryTree* tree = tree_create();

    printf(CYAN "Inserting nodes: 50, 30, 70, 20, 40, 60, 80\n\n" RESET);

    tree->root = tree_insert(tree->root, 50);
    tree->root = tree_insert(tree->root, 30);
    tree->root = tree_insert(tree->root, 70);
    tree->root = tree_insert(tree->root, 20);
    tree->root = tree_insert(tree->root, 40);
    tree->root = tree_insert(tree->root, 60);
    tree->root = tree_insert(tree->root, 80);

    printf("\n" CYAN "Binary Search Tree Visualization:\n" RESET);
    tree_visualize(tree->root, 0);
    usleep(1500000);

    printf("\n" CYAN "Tree Traversals:\n" RESET);
    printf("  In-order:   ");
    tree_inorder(tree->root);
    printf("\n");

    printf("  Pre-order:  ");
    tree_preorder(tree->root);
    printf("\n");

    printf("  Post-order: ");
    tree_postorder(tree->root);
    printf("\n\n");
    usleep(1500000);

    printf(CYAN "Searching for values...\n" RESET);
    tree_search(tree->root, 40);
    usleep(1000000);
    tree_search(tree->root, 100);
    usleep(1000000);

    tree_free(tree->root);
    free(tree);

    printf("\n" GREEN "Press Enter to continue..." RESET);
    getchar();
}

void demo_graph() {
    clear_screen();
    print_header("GRAPH DEMONSTRATION");

    Graph* graph = graph_create(6);

    printf(CYAN "Creating graph with 6 vertices...\n\n" RESET);

    graph_add_edge(graph, 0, 1);
    graph_add_edge(graph, 0, 2);
    graph_add_edge(graph, 1, 3);
    graph_add_edge(graph, 1, 4);
    graph_add_edge(graph, 2, 4);
    graph_add_edge(graph, 3, 5);
    graph_add_edge(graph, 4, 5);

    printf("\n");
    graph_visualize(graph);
    usleep(1500000);

    graph_bfs(graph, 0);
    usleep(1500000);

    graph_dfs(graph, 0);
    usleep(1500000);

    graph_free(graph);

    printf("\n" GREEN "Press Enter to continue..." RESET);
    getchar();
}

void demo_sorting() {
    clear_screen();
    print_header("SORTING ALGORITHMS DEMONSTRATION");

    printf(CYAN "Choose a sorting algorithm:\n" RESET);
    printf("  1. Bubble Sort\n");
    printf("  2. Selection Sort\n");
    printf("  3. Insertion Sort\n");
    printf("  4. Quick Sort\n");
    printf("  5. Merge Sort\n");
    printf("\n" YELLOW "Enter choice (1-5): " RESET);

    int choice;
    scanf("%d", &choice);
    getchar();

    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(arr) / sizeof(arr[0]);

    clear_screen();

    switch (choice) {
        case 1:
            bubble_sort(arr, size);
            break;
        case 2:
            selection_sort(arr, size);
            break;
        case 3:
            insertion_sort(arr, size);
            break;
        case 4:
            quick_sort(arr, 0, size - 1);
            break;
        case 5:
            merge_sort(arr, 0, size - 1);
            break;
        default:
            printf(RED "Invalid choice!\n" RESET);
    }

    printf("\n" GREEN "Press Enter to continue..." RESET);
    getchar();
}

void demo_searching() {
    clear_screen();
    print_header("SEARCHING ALGORITHMS DEMONSTRATION");

    printf(CYAN "Choose a searching algorithm:\n" RESET);
    printf("  1. Linear Search\n");
    printf("  2. Binary Search\n");
    printf("\n" YELLOW "Enter choice (1-2): " RESET);

    int choice;
    scanf("%d", &choice);
    getchar();

    clear_screen();

    if (choice == 1) {
        int arr[] = {64, 34, 25, 12, 22, 11, 90};
        int size = sizeof(arr) / sizeof(arr[0]);
        linear_search(arr, size, 22);
    } else if (choice == 2) {
        int arr[] = {11, 12, 22, 25, 34, 64, 90};
        int size = sizeof(arr) / sizeof(arr[0]);
        binary_search(arr, size, 25);
    } else {
        printf(RED "Invalid choice!\n" RESET);
    }

    printf("\n" GREEN "Press Enter to continue..." RESET);
    getchar();
}

void print_main_menu() {
    clear_screen();
    printf("\n");
    printf(CYAN "╔══════════════════════════════════════════════════════════════╗\n" RESET);
    printf(CYAN "║" YELLOW "          DATA STRUCTURES & ALGORITHMS VISUALIZER             " CYAN "║\n" RESET);
    printf(CYAN "║" YELLOW "                    Learning Library in C                     " CYAN "║\n" RESET);
    printf(CYAN "╚══════════════════════════════════════════════════════════════╝\n" RESET);
    printf("\n");
    printf(GREEN "DATA STRUCTURES:\n" RESET);
    printf("  1. Linked List\n");
    printf("  2. Stack\n");
    printf("  3. Queue\n");
    printf("  4. Binary Tree\n");
    printf("  5. Graph\n");
    printf("\n");
    printf(GREEN "ALGORITHMS:\n" RESET);
    printf("  6. Sorting Algorithms\n");
    printf("  7. Searching Algorithms\n");
    printf("\n");
    printf(RED "  0. Exit\n" RESET);
    printf("\n");
    printf(YELLOW "Enter your choice: " RESET);
}

int main() {
    int choice;

    while (1) {
        print_main_menu();
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                demo_linked_list();
                break;
            case 2:
                demo_stack();
                break;
            case 3:
                demo_queue();
                break;
            case 4:
                demo_binary_tree();
                break;
            case 5:
                demo_graph();
                break;
            case 6:
                demo_sorting();
                break;
            case 7:
                demo_searching();
                break;
            case 0:
                clear_screen();
                printf("\n" CYAN "Tschüss\n\n" RESET);
                return 0;
            default:
                printf(RED "\nInvalid choice! Please try again.\n" RESET);
                sleep(2);
        }
    }

    return 0;
}
