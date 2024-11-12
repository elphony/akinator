#ifndef TREE_H
#define TREE_H

#include <stdio.h>

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

void insert_elem(Tree* tree, Node* node, TreeElem_t data);

char* read_node_data(FILE* text);

Node* read_node(FILE* text);

Tree* tree_from_file(FILE* text);

size_t count_node();

#endif // TREE_H