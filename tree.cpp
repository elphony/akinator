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

Tree* tree_from_file(const char* name_file) {
    
    FILE* text = fopen(name_file, "r");

    Tree* my_tree = {};
    my_tree = (Tree*)calloc(1, sizeof(Tree));

    my_tree->root = read_node(text);
    my_tree->size = count_node() - 1;

    fclose(text);

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

    TreeElem_t node_data = read_node_data(text);

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

TreeElem_t read_node_data(FILE* text) {

    int symbol = fgetc(text);
    
    while (isspace(symbol)){
        symbol = fgetc(text);
    }

    if (symbol != '"') {
        fprintf(stderr, "%s: unknown symbol %c\n", __func__, symbol);
    }

    TreeElem_t node_data = (TreeElem_t)calloc(1, MAX_DATA_SIZE * sizeof(TreeElem_t));

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


void insert_elem(Tree* tree, Node* node, TreeElem_t data, compare_func comparator) {

    if (comparator(node->data, data) < 0) {
        if (!node->left) {
            node->left = node_ctor(data);
            tree->size++;
            return;
        }
        else {
            insert_elem(tree, node->left, data, comparator);
        }
    }
    if (comparator(node->data, data) > 0) {
        if (!node->right) {
            node->right = node_ctor(data);
            tree->size++;
            return;
        }
        else {
            insert_elem(tree, node->right, data, comparator);
        }     
    }
}

int find_tree_elem(Node* node, TreeElem_t value) {

    if (strcasecmp(node->data, value) == 0) {
        return 1;
    }

    if (node->left) {
        if (find_tree_elem(node->left, value)) {
            return 1;
        }
    }

    if (node->right) {
        if (find_tree_elem(node->right, value)) {
            return 1;
        }
    }

    return 0;
}