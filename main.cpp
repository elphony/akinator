#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "dump.h"

int main() {
    Tree* my_tree = tree_ctor(50);

    insert_elem(my_tree, my_tree->root, 40);
    insert_elem(my_tree, my_tree->root, 30);
    insert_elem(my_tree, my_tree->root, 60);
    insert_elem(my_tree, my_tree->root, 10);
    insert_elem(my_tree, my_tree->root, 5);
    insert_elem(my_tree, my_tree->root, 70);
    insert_elem(my_tree, my_tree->root, 55);
    insert_elem(my_tree, my_tree->root, 45);

    create_html();

    tree_dtor(my_tree);
}