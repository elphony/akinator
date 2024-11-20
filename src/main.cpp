#include <stdio.h>
#include <stdlib.h>

#include "../include/tree.h"
#include "../include/dump.h"
#include "../include/akinator.h"

int main() {
    
    Tree* my_tree = tree_from_file("word_base/new_tree.txt");

    start_akinator(my_tree);

    create_html();

    tree_dtor(my_tree);
}