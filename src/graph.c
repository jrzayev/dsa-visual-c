#include "dsa_visual.h"

Graph* graph_create(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->num_vertices = vertices;
    graph->adj_list = (GraphNode**)malloc(vertices * sizeof(GraphNode*));

    for (int i = 0; i < vertices; i++) {
        graph->adj_list[i] = NULL;
    }

    return graph;
}

void graph_add_edge(Graph* graph, int src, int dest) {
    GraphNode* new_node = (GraphNode*)malloc(sizeof(GraphNode));
    new_node->vertex = dest;
    new_node->next = graph->adj_list[src];
    graph->adj_list[src] = new_node;

    new_node = (GraphNode*)malloc(sizeof(GraphNode));
    new_node->vertex = src;
    new_node->next = graph->adj_list[dest];
    graph->adj_list[dest] = new_node;

    printf(GREEN "✓ Added edge: %d ↔ %d\n" RESET, src, dest);
}

void graph_bfs(Graph* graph, int start) {
    int* visited = (int*)calloc(graph->num_vertices, sizeof(int));
    int* queue = (int*)malloc(graph->num_vertices * sizeof(int));
    int front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    printf(CYAN "\nBFS Traversal starting from vertex %d:\n" RESET, start);
    printf("  ");

    while (front < rear) {
        int current = queue[front++];
        printf(BG_GREEN " %2d " RESET " → ", current);
        usleep(300000);

        GraphNode* temp = graph->adj_list[current];
        while (temp != NULL) {
            int adj_vertex = temp->vertex;
            if (!visited[adj_vertex]) {
                visited[adj_vertex] = 1;
                queue[rear++] = adj_vertex;
            }
            temp = temp->next;
        }
    }
    printf("END\n\n");

    free(visited);
    free(queue);
}

void graph_dfs_util(Graph* graph, int vertex, int* visited) {
    visited[vertex] = 1;
    printf(BG_BLUE " %2d " RESET " → ", vertex);
    usleep(300000);

    GraphNode* temp = graph->adj_list[vertex];
    while (temp != NULL) {
        int adj_vertex = temp->vertex;
        if (!visited[adj_vertex]) {
            graph_dfs_util(graph, adj_vertex, visited);
        }
        temp = temp->next;
    }
}

void graph_dfs(Graph* graph, int start) {
    int* visited = (int*)calloc(graph->num_vertices, sizeof(int));

    printf(CYAN "\nDFS Traversal starting from vertex %d:\n" RESET, start);
    printf("  ");

    graph_dfs_util(graph, start, visited);
    printf("END\n\n");

    free(visited);
}

void graph_visualize(Graph* graph) {
    printf("\n" CYAN "Graph Adjacency List:\n" RESET);

    for (int i = 0; i < graph->num_vertices; i++) {
        printf("  [%d] → ", i);

        GraphNode* temp = graph->adj_list[i];
        if (temp == NULL) {
            printf(YELLOW "NULL\n" RESET);
        } else {
            while (temp != NULL) {
                printf(BG_BLUE " %2d " RESET, temp->vertex);
                if (temp->next != NULL) {
                    printf(" → ");
                }
                temp = temp->next;
            }
            printf("\n");
        }
    }
    printf("\n");
}

void graph_free(Graph* graph) {
    for (int i = 0; i < graph->num_vertices; i++) {
        GraphNode* current = graph->adj_list[i];
        while (current != NULL) {
            GraphNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->adj_list);
    free(graph);
}
