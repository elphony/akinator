#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "dump.h"

int main() {
    
    FILE* file = fopen("tree.txt", "r");
    Tree* my_tree = tree_from_file(file);
    TREE_DUMP(my_tree, my_tree->root);

    create_html();

    tree_dtor(my_tree);
}