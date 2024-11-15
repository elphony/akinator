#ifndef DUMP_HUI
#define DUMP_HUI

#include "tree.h"

const size_t MAX_SIZE_OF_COMMAND = 100;

#define TREE_DUMP_(tree, dump_id) create_dump(tree, dump_id, __FILE__, __LINE__, __FUNCTION__) 

int count_dump();

void create_dump(Tree* tree, int* dump_id, const char* file, int line, const char* func);

void create_html();

void create_node(Node* node, FILE* dump);

#endif // DUMP_HUI