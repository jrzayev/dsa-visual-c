#include "dsa_visual.h"

BinaryTree* tree_create() {
    BinaryTree* tree = (BinaryTree*)malloc(sizeof(BinaryTree));
    tree->root = NULL;
    return tree;
}

TreeNode* tree_insert(TreeNode* root, int data) {
    if (root == NULL) {
        TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
        new_node->data = data;
        new_node->left = NULL;
        new_node->right = NULL;
        printf(GREEN "✓ Inserted %d\n" RESET, data);
        return new_node;
    }
    
    if (data < root->data) {
        root->left = tree_insert(root->left, data);
    } else if (data > root->data) {
        root->right = tree_insert(root->right, data);
    } else {
        printf(YELLOW "⚠ Duplicate value %d ignored\n" RESET, data);
    }
    
    return root;
}

TreeNode* tree_search(TreeNode* root, int data) {
    if (root == NULL) {
        printf(RED "✗ Value %d not found\n" RESET, data);
        return NULL;
    }
    
    if (data == root->data) {
        printf(GREEN "✓ Found %d\n" RESET, data);
        return root;
    }
    
    if (data < root->data) {
        printf("  Searching left subtree...\n");
        return tree_search(root->left, data);
    } else {
        printf("  Searching right subtree...\n");
        return tree_search(root->right, data);
    }
}

void tree_inorder(TreeNode* root) {
    if (root != NULL) {
        tree_inorder(root->left);
        printf("%d ", root->data);
        tree_inorder(root->right);
    }
}

void tree_preorder(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        tree_preorder(root->left);
        tree_preorder(root->right);
    }
}

void tree_postorder(TreeNode* root) {
    if (root != NULL) {
        tree_postorder(root->left);
        tree_postorder(root->right);
        printf("%d ", root->data);
    }
}

void tree_visualize(TreeNode* root, int space) {
    if (root == NULL) {
        return;
    }
    
    space += 5;
    
    tree_visualize(root->right, space);
    
    printf("\n");
    for (int i = 5; i < space; i++) {
        printf(" ");
    }
    printf(BG_BLUE " %3d " RESET "\n", root->data);
    
    tree_visualize(root->left, space);
}

void tree_free(TreeNode* root) {
    if (root != NULL) {
        tree_free(root->left);
        tree_free(root->right);
        free(root);
    }
}
