#ifndef DSA_VISUAL_H
#define DSA_VISUAL_H

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE "\033[44m"

// ============================================================================
// LINKED LIST
// ============================================================================
typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
} LinkedList;

LinkedList* ll_create();
void ll_insert_front(LinkedList* list, int data);
void ll_insert_back(LinkedList* list, int data);
void ll_insert_at(LinkedList* list, int data, int position);
void ll_delete_front(LinkedList* list);
void ll_delete_back(LinkedList* list);
void ll_delete_at(LinkedList* list, int position);
int ll_search(LinkedList* list, int data);
void ll_visualize(LinkedList* list);
void ll_free(LinkedList* list);

// ============================================================================
// STACK
// ============================================================================
typedef struct {
    int* data;
    int top;
    int capacity;
} Stack;

Stack* stack_create(int capacity);
void stack_push(Stack* stack, int data);
int stack_pop(Stack* stack);
int stack_peek(Stack* stack);
int stack_is_empty(Stack* stack);
int stack_is_full(Stack* stack);
void stack_visualize(Stack* stack);
void stack_free(Stack* stack);

// ============================================================================
// QUEUE
// ============================================================================
typedef struct {
    int* data;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

Queue* queue_create(int capacity);
void queue_enqueue(Queue* queue, int data);
int queue_dequeue(Queue* queue);
int queue_peek(Queue* queue);
int queue_is_empty(Queue* queue);
int queue_is_full(Queue* queue);
void queue_visualize(Queue* queue);
void queue_free(Queue* queue);

// ============================================================================
// BINARY TREE
// ============================================================================
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct {
    TreeNode* root;
} BinaryTree;

BinaryTree* tree_create();
TreeNode* tree_insert(TreeNode* root, int data);
TreeNode* tree_search(TreeNode* root, int data);
void tree_inorder(TreeNode* root);
void tree_preorder(TreeNode* root);
void tree_postorder(TreeNode* root);
void tree_visualize(TreeNode* root, int space);
void tree_free(TreeNode* root);

// ============================================================================
// GRAPH (Adjacency List)
// ============================================================================
typedef struct GraphNode {
    int vertex;
    struct GraphNode* next;
} GraphNode;

typedef struct {
    int num_vertices;
    GraphNode** adj_list;
} Graph;

Graph* graph_create(int vertices);
void graph_add_edge(Graph* graph, int src, int dest);
void graph_bfs(Graph* graph, int start);
void graph_dfs_util(Graph* graph, int vertex, int* visited);
void graph_dfs(Graph* graph, int start);
void graph_visualize(Graph* graph);
void graph_free(Graph* graph);

// ============================================================================
// HASHMAP
// ============================================================================
typedef struct HashEntry {
    char* key;
    int value;
    struct HashEntry* next;
} HashEntry;

typedef struct {
    HashEntry** buckets;
    int capacity;
    int size;
} HashMap;

HashMap* hashmap_create(int capacity);
void hashmap_put(HashMap* map, const char* key, int value);
int hashmap_get(HashMap* map, const char* key, int* found);
int hashmap_remove(HashMap* map, const char* key);
int hashmap_contains(HashMap* map, const char* key);
void hashmap_visualize(HashMap* map);
void hashmap_free(HashMap* map);

// ============================================================================
// HASHSET
// ============================================================================
typedef struct SetEntry {
    int value;
    struct SetEntry* next;
} SetEntry;

typedef struct {
    SetEntry** buckets;
    int capacity;
    int size;
} HashSet;

HashSet* hashset_create(int capacity);
int hashset_add(HashSet* set, int value);
int hashset_remove(HashSet* set, int value);
int hashset_contains(HashSet* set, int value);
int hashset_contains_silent(HashSet* set, int value);
HashSet* hashset_union(HashSet* set1, HashSet* set2);
HashSet* hashset_intersection(HashSet* set1, HashSet* set2);
void hashset_visualize(HashSet* set);
void hashset_free(HashSet* set);

// ============================================================================
// DYNAMIC ARRAY
// ============================================================================
typedef struct {
    int* data;
    int size;
    int capacity;
} DynamicArray;

DynamicArray* array_create(int initial_capacity);
void array_push_back(DynamicArray* arr, int value);
void array_push_front(DynamicArray* arr, int value);
void array_insert_at(DynamicArray* arr, int index, int value);
int array_pop_back(DynamicArray* arr);
int array_pop_front(DynamicArray* arr);
int array_remove_at(DynamicArray* arr, int index);
int array_get(DynamicArray* arr, int index);
void array_set(DynamicArray* arr, int index, int value);
int array_search(DynamicArray* arr, int value);
void array_reverse(DynamicArray* arr);
void array_visualize(DynamicArray* arr);
void array_free(DynamicArray* arr);

// ============================================================================
// STRING BUILDER
// ============================================================================
typedef struct {
    char* data;
    int length;
    int capacity;
} StringBuilder;

StringBuilder* string_create(const char* initial);
void string_append(StringBuilder* sb, const char* str);
void string_append_char(StringBuilder* sb, char c);
void string_insert(StringBuilder* sb, int index, const char* str);
void string_delete(StringBuilder* sb, int start, int end);
char string_char_at(StringBuilder* sb, int index);
int string_index_of(StringBuilder* sb, const char* substr);
void string_replace(StringBuilder* sb, const char* old_str, const char* new_str);
void string_reverse(StringBuilder* sb);
void string_to_upper(StringBuilder* sb);
void string_to_lower(StringBuilder* sb);
void string_trim(StringBuilder* sb);
StringBuilder* string_substring(StringBuilder* sb, int start, int end);
int string_is_palindrome(StringBuilder* sb);
void string_visualize(StringBuilder* sb);
void string_free(StringBuilder* sb);

// ============================================================================
// SORTING ALGORITHMS
// ============================================================================
void visualize_array(int arr[], int size, int highlight1, int highlight2);
void bubble_sort(int arr[], int size);
void selection_sort(int arr[], int size);
void insertion_sort(int arr[], int size);
void quick_sort(int arr[], int low, int high);
void merge_sort(int arr[], int left, int right);

// ============================================================================
// SEARCHING ALGORITHMS
// ============================================================================
int linear_search(int arr[], int size, int target);
int binary_search(int arr[], int size, int target);

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================
void clear_screen();
void print_header(const char* title);
void pause_execution();

#endif
