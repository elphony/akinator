#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>

#include "tree.h"
#include "akinator.h"
#include "dump.h"
#include "text_color.h"

void start_akinator(Tree* tree) {
    
    color_fprintf(stdout, COLOR_YELLOW, "What do you want:\n[G]uess, [D]efine, [S]how the tree, [E]xit without save progress or [W]ith saving?\n");

    char ans[MAX_SIZE_ANS] = {};

    while (scanf(" %s", ans)) {

        if (strcasecmp(ans, "g") == 0) {
            start_akinator_guess(tree);
        }

        else if (strcasecmp(ans, "d") == 0) {
            if (akinator_give_defenition(tree)) {
                printf("Do not find this object\n");
            }
            color_fprintf(stdout, COLOR_YELLOW, "\nWhat do you want:\n[G]uess, [D]efine, [S]how the tree, [E]xit without save progress or [W]ith saving?\n");
        }

        else if (strcasecmp(ans, "s") == 0) {

            TREE_DUMP(tree);
            char command[MAX_SIZE_OF_COMMAND] = {};

            sprintf(command, "eog dump/dump%d.png -f", count_dump() - 1);
            system(command);

           color_fprintf(stdout, COLOR_YELLOW, "\nWhat do you want:\n[G]uess, [D]efine, [S]how the tree, [E]xit without save progress or [W]ith saving?\n");
        }

        else if (strcasecmp(ans, "e") == 0) {
            system("eog bye_bye.png -f");
            return;
        }

        else if (strcasecmp(ans, "w") == 0) {
            tree_to_file("new_tree.txt", tree);
            printf("Bye bye\n");
            return;
        }

        else {
            printf("Unknown command\n");
            color_fprintf(stdout, COLOR_YELLOW, "\nWhat do you want:\n[G]uess, [D]efine, [S]how the tree, [E]xit without save progress or [W]ith saving?\n");
        }
    }
}

int akinator_give_defenition(Tree* tree) {

    printf("The definition of which object you want to get?\n");

    char object[MAX_DATA_SIZE] = {};
    scanf(" %[^\n]", object);

    printf("Object: %s\n", object);

    if (definition(tree->root, object)) {
        printf("\n");
        return 0;
    } 
    else {
        return 1;
    }
}

int definition(Node* node, TreeElem_t value) {

    if (strcasecmp(node->data, value) == 0) {
        printf("|");
        return 1;
    }

    if (node->left) {
        if (definition(node->left, value)) {
            printf(" No %s |", node->data);
            return 1;
        }
    }

    if (node->right) {
        if (definition(node->right, value)) {
            printf(" %s |", node->data);
            return 1;
        }
    }

    return 0;
}

void start_akinator_guess(Tree* tree) {

    char start_game[MAX_SIZE_ANS] = {}; 

    printf("Do you want to start the game? [yes/no]\n");

    while (1) {
        scanf(" %[^\n]", start_game);

        if (strcasecmp(start_game, "yes") == 0) {
            play_game(tree, tree->root);
            printf("Do you want to play again? [yes/no]\n");
        } 
        else if (strcasecmp(start_game, "no") == 0) {
            printf("Okay\n");
            color_fprintf(stdout, COLOR_YELLOW, "\nWhat do you want:\n[G]uess, [D]efine, [S]how the tree, [E]xit without save progress or [W]ith saving?\n");
            break;
        } 
        else {
            printf("Please, answer only \"yes\" or \"no\" :(\n");
            printf("Do you want to start the game? [yes/no]\n");
        }
    }
}

void play_game(Tree* tree, Node* node) {

    char ans[MAX_SIZE_ANS] = {};

    while (node->left != NULL && node->right != NULL) {

        printf("%s? [yes/no]\n", node->data);

        while (scanf("%s", ans)) {
            if (strcasecmp(ans, "yes") == 0 || strcasecmp(ans, "no") == 0) {
                break;
            } 
            else {
                printf("Please, answer only \"yes\" or \"no\")\n");
                printf("%s? [yes/no]\n", node->data);
            }
        }

        if (strcasecmp(ans, "yes") == 0) {
            node = node->right;
        } 
        else {
            node = node->left;
        }
    }

    color_fprintf(stdout, COLOR_GREEN, "I think, it is %s\n", node->data);

    printf("Did I guess right? [yes/no]\n");

    while (scanf("%s", ans)) {
        if (strcasecmp(ans, "yes") == 0) {
            printf("I won\n");
            break;
        } 
        else if (strcasecmp(ans, "no") == 0) {
            printf("Please, write the word you have in mind\n");
            add_new_word(tree, node);
            printf("The new word has been added\n");
            break;
        } 
        else {
            printf("Please, answer only \"yes\" or \"no\")\n");
            printf("Did I guess right? [yes/no]\n");
        }
    }
}

void add_new_word(Tree* tree, Node* node) {

    char* new_word = (char*)calloc(MAX_DATA_SIZE, sizeof(char));
    scanf(" %[^\n]", new_word); 

    printf("Please, write how %s differs from %s\n", new_word, node->data);

    char* new_question = (char*)calloc(MAX_DATA_SIZE, sizeof(char));
    scanf(" %[^\n]", new_question); 

    node->left  = node_ctor(node->data);
    node->right = node_ctor(new_word);
    node->data  = new_question;

    tree->size += 2;
}