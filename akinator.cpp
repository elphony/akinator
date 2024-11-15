#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>

#include "tree.h"
#include "akinator.h"
#include "dump.h"

// add new struct: {object, path, logic_path} (?)                        

void start_akinator(Tree* tree) {
    
    printf("What do you want:\n[G]uess, [D]efine, [S]how the tree, [E]xit?\n");

    char ans[MAX_SIZE_ANS] = {};

    while (scanf("%s", ans)) {

        if (strcasecmp(ans, "g") == 0) {
            start_akinator_guess(tree);
        }

        if (strcasecmp(ans, "d") == 0) {
            printf("The definition of which object you want to get?\n");

            char object[MAX_DATA_SIZE] = {};
            fgetc(stdin);
            scanf("%[^\n]", object);

            char** path = (char**)calloc(tree->size, sizeof(char**));

            int* logic_path = (int*)calloc(tree->size, sizeof(int*));

            printf("Object: %s\n", object);

            akinator_give_defenition(tree, object, path, logic_path);

            free(path);
            free(logic_path);
        }

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

int akinator_give_defenition(Tree* tree, char* object, char** path, int* logic_path) {

    if (find_tree_elem(tree->root, object, path, logic_path)) {

        for (size_t i = 0; i < tree->size - 1; i++) {

            if (path[i]) {

                if (logic_path[i] == 1) {
                    printf("%s ", path[i]);
                } 
                else {
                    printf("No %s ", path[i]);
                }

                if (strcasecmp(path[i + 1], object) != 0) {
                    printf("| ");
                }
                else {
                    printf("\n"); 
                    break;
                }
            }
        }
        return 0;
    } 
    else {
        return 1;
    }
}

void start_akinator_guess(Tree* tree) {

    char start_game[MAX_SIZE_ANS] = {}; 
    fgetc(stdin);

    printf("Do you want to start the game? [yes/no]\n");

    while (scanf("%[^\n]", start_game)) {
        if (strcasecmp(start_game, "yes") == 0) {
            play_game(tree, tree->root);
            
            while (1) {
                printf("Do you want to play again? [yes/no]\n");
                fgetc(stdin);
                scanf("%[^\n]", start_game);

                if (strcasecmp(start_game, "yes") == 0) {
                    play_game(tree, tree->root);
                } 
                else if (strcasecmp(start_game, "no") == 0) {
                    printf("Okay\n");
                    printf("What do you want:\n[G]uess, [D]efine, [S]how the tree, [E]xit?\n");
                    break;
                } 
                else {
                    printf("Please, answer only \"yes\" or \"no\")\n");
                }
            }
            break;
        } 
        else if (strcasecmp(start_game, "no") == 0) {
            printf("Okay\n");
            printf("What do you want:\n[G]uess, [D]efine, [S]how the tree, [E]xit?\n");
            break;
        } 
        else {
            printf("Please, answer only \"yes\" or \"no\")\n");
            printf("Do you want to start the game? [yes/no]\n");
        }
    }
}

void play_game(Tree* tree, Node* node) {

    char ans[MAX_SIZE_ANS] = {};

    while (node->left != NULL || node->right != NULL) {

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
        } else {
            node = node->left;
        }
    }

    printf("I think, it is %s\n", node->data);

    printf("Did I guess right? [yes/no]\n");

    while (scanf("%s", ans)) {
        if (strcasecmp(ans, "yes") == 0) {
            printf("I won\n");
            printf("What do you want:\n[G]uess, [D]efine, [S]how the tree, [E]xit?\n");
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
    fgetc(stdin);
    scanf("%[^\n]", new_word); 

    printf("Please, write how %s differs from %s\n", new_word, node->data);

    char* new_question = (char*)calloc(MAX_DATA_SIZE, sizeof(char));
    fgetc(stdin);
    scanf("%[^\n]", new_question); 

    node->left  = node_ctor(node->data);
    node->right = node_ctor(new_word);
    node->data  = new_question;

    tree->size += 2;
}