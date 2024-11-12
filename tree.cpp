#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tree.h"
#include "dump.h"

size_t count_node() {
    static size_t num = 0;
    num++;
    return num;
}

Tree* tree_from_file(FILE* text) {
    Tree* my_tree = {};
    my_tree = (Tree*)calloc(1, sizeof(Tree));
    my_tree->root = read_node(text);
    my_tree->size = count_node() - 1;
    return my_tree;
}

Node* read_node(FILE* text) {

    int symbol = fgetc(text);

    while (isspace(symbol)) {
        symbol = fgetc(text);
    }

    if (symbol == '*') {
        return NULL;
    }
    else if (symbol != '{') {
        fprintf(stderr, "%s: unknown symbol %c\n", __func__, symbol);
        return NULL; 
    }

    char* node_data = read_node_data(text);

    Node* node = node_ctor(node_data);
    count_node();

    
    node->left  = read_node(text);
    node->right = read_node(text);

    symbol = fgetc(text);

    while (symbol != '}'){
        symbol = fgetc(text);
    }

    return node; 
}

char* read_node_data(FILE* text) {

    int symbol = getc(text);
    
    while (isspace(symbol)){
        symbol = fgetc(text);
    }

    if (symbol != '"') {
        fprintf(stderr, "%s: unknown symbol %c\n", __func__, symbol);
    }

    char* node_data = (char*)calloc(1, MAX_DATA_SIZE * sizeof(char));

    //fscanf(text, "%s", node_data); 

    fscanf(text, "%[^\"]", node_data);

    symbol = fgetc(text);

    return node_data;
}

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
    free(node->data);
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