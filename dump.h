#ifndef DUMP_HUI
#define DUMP_HUI

#include <stdio.h>
#include "tree.h"

const size_t MAX_SIZE_OF_COMMAND = 100;

#define TREE_DUMP(tree, node) create_dump(tree, node, __FILE__, __LINE__, __FUNCTION__) 

int count_dump();

void create_dump(Tree* tree, Node* node, const char* file, int line, const char* func);

void create_html();

void create_node(Node* node, FILE* dump);

#endif // DUMP_HUI