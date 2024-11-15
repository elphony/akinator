#ifndef AKINATOR_H
#define AKINATOR_H

const size_t MAX_SIZE_ANS = 10; 

void start_akinator(Tree* tree);

int akinator_give_defenition(Tree* tree, char* object, char** path, int* logic_path);

void start_akinator_guess(Tree* tree);

void play_game(Tree* tree, Node* node);

void add_new_word(Tree* tree, Node* node);

#endif // AKINATOR_H