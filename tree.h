#ifndef TREE_H
#define TREE_H

typedef int TreeElem_t;

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

#endif // TREE_H