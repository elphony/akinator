#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "dump.h"

void create_dump(Tree* tree, Node* node, const char* file, int line, const char* func) {
    FILE* dump = fopen("dump/dump.dot", "w");

    fprintf(dump, "digraph tree {\n");
    fprintf(dump, "\tsplines = ortho\n");

    create_node(tree->root, dump);

    fprintf(dump, "\tnode%p [fillcolor = \"lightyellow\"]", node);

    fprintf(dump, "}\n");

    fclose(dump);
    
    char command[MAX_SIZE_OF_COMMAND] = {};
    sprintf(command, "dot -Tpng dump/dump.dot -o dump/dump%d.png", count_dump());
    system(command);
}

int count_dump() {
    static int num = 0;
    num++;
    return num;
}

void create_html() {
    int count = count_dump();
    FILE* html_file = fopen("dump/dump.html", "w");
    fprintf(html_file, "<pre>\n");
    for (int i = 1; i < count; ++i) {
        fprintf(html_file, "<img src=dump%d.png><hr>\n", i);
    }
    fclose(html_file);
}

void create_node(Node* node, FILE* dump) {

    fprintf(dump, "\tnode%p[shape = Mrecord, style = \"rounded, filled\","
                    "fillcolor = \"lightpink\", label = \"{hui: %d | { pizda: %p | skovoroda: %p }}\"]\n", 
                         node,                                  node->data,   node->left,     node->right);

    if (node->left) {
        fprintf(dump, "\tnode%p -> node%p\n", node, node->left);
        create_node(node->left, dump);
    }
    if (node->right) {
        fprintf(dump, "\tnode%p -> node%p\n", node, node->right);
        create_node(node->right, dump);
    }
}