#ifndef AKINATOR_H
#define AKINATOR_H

const size_t MAX_SIZE_ANS = 10; 

void start_akinator(Tree* tree);

int akinator_give_defenition(Tree* tree);

void start_akinator_guess(Tree* tree);

void play_game(Tree* tree, Node* node);

void add_new_word(Tree* tree, Node* node);

int definition(Node* node, TreeElem_t value);

#endif // AKINATOR_H