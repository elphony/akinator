#ifndef DUMP_HUI
#define DUMP_HUI

#include "tree.h"

const size_t MAX_SIZE_OF_COMMAND = 100;

#define TREE_DUMP(tree) create_dump(tree, __FILE__, __LINE__, __FUNCTION__) 

int count_dump();

void create_dump(Tree* tree, const char* file, int line, const char* func);

void create_html();

void create_node(Node* node, FILE* dump);

#endif // DUMP_HUI