#ifndef TREE_H
#define TREE_H

#include <stdio.h>

typedef int (*compare_func)(char* str1, char* str2);

typedef char* TreeElem_t;

const size_t MAX_DATA_SIZE = 100;

struct Node {
    TreeElem_t data;
    Node*      left;
    Node*     right;
};

struct Tree {
    Node*  root;
    size_t size;
};

Node* node_ctor(TreeElem_t data);

Tree* tree_ctor(TreeElem_t data);

void node_dtor(Node* node);

void tree_dtor(Tree* tree);

void insert_elem(Tree* tree, Node* node, TreeElem_t data, compare_func comparator);

TreeElem_t read_node_data(FILE* text);

Node* read_node(FILE* text);

Tree* tree_from_file(const char* name_file);

size_t count_node();

int find_tree_elem(Node* node, TreeElem_t value, char** path, int* logic_path);

#endif // TREE_H