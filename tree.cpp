#include <stdlib.h>

#include "tree.h"
#include "dump.h"

Node* node_ctor(TreeElem_t data) {
    Node* new_node  = (Node*)calloc(1, sizeof(Node));
    // проверка выделенной памяти
    new_node->data  = data;
    new_node->left  = NULL;
    new_node->right = NULL;
    return new_node;
}

Tree* tree_ctor(TreeElem_t data) {
    Tree* my_tree = (Tree*)calloc(1, sizeof(Tree));
    // проверка выделенной памяти
    my_tree->root = node_ctor(data);
    my_tree->size = 0;
    TREE_DUMP(my_tree, my_tree->root);
    return my_tree;
}

void node_dtor(Node* node) {
    if (node->left) {
        node_dtor(node->left);
    }
    if (node->right) {
        node_dtor(node->right);
    }
    free(node);
}

void tree_dtor(Tree* tree) {
    node_dtor(tree->root);
    free(tree);
}

void insert_elem(Tree* tree, Node* node, TreeElem_t data) {
    if (node->data > data) {
        if (!node->left) {
            node->left = node_ctor(data);
            tree->size++;
            TREE_DUMP(tree, node->left);
            return;
        }
        else {
            insert_elem(tree, node->left, data);
        }
    }
    if (node->data <= data) {
        if (!node->right) {
            node->right = node_ctor(data);
            tree->size++;
            TREE_DUMP(tree, node->right);
            return;
        }
        else {
            insert_elem(tree, node->right, data);
        }     
    }
}