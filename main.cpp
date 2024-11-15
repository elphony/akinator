#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "dump.h"
#include "akinator.h"

int main() {
    
    Tree* my_tree = tree_from_file("tree.txt");

    start_akinator(my_tree);

    create_html();

    tree_dtor(my_tree);
}