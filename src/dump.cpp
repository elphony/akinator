#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/dump.h"

void create_dump(Tree* tree, const char* file, int line, const char* func) {
    FILE* dump = fopen("dump/dump.dot", "w");

    fprintf(dump, "digraph tree {\n");
    fprintf(dump, "\tsplines = ortho\n");
    fprintf(dump, "\theader [shape = Mrecord, style = \"filled\", label = \"tree dump from file %s | function %s | line %d | size %zu\"" 
                    "fillcolor = \"white\", color = \"white\"]",                                file,         func,     line,     tree->size);

    create_node(tree->root, dump);

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
                    "fillcolor = \"lightpink\", label = \"{%s | { %p | %p }}\"]\n", 
                         node,                                  node->data,   node->left,     node->right);

    if (node->left) {
        fprintf(dump, "\tnode%p -> node%p [xlabel = \"No\"]\n", node, node->left);
        create_node(node->left, dump);
    }
    if (node->right) {
        fprintf(dump, "\tnode%p -> node%p [xlabel = \"Yes\"]\n", node, node->right);
        create_node(node->right, dump);
    }
}