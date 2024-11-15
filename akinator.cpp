#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>

#include "tree.h"
#include "akinator.h"
#include "dump.h"

void start_akinator(Tree* tree) {
    
    printf("What do you want:\n[S]how the tree, [E]xit?\n");

    char ans[MAX_SIZE_ANS] = {};

    while (scanf("%s", ans)) {
        if (strcasecmp(ans, "s") == 0) {

            int dump_id = 0;
            TREE_DUMP_(tree, &dump_id);
            char command[MAX_SIZE_OF_COMMAND] = {};

            sprintf(command, "eog dump/dump%d.png -f", dump_id);
            system(command);
        }

        if (strcasecmp(ans, "e") == 0) {
            return;
        }
    }
}
