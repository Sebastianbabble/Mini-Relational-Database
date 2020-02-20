#ifndef STATE_FUNCTIONS_H
#define STATE_FUNCTIONS_H
#include"constants.h"
#include <string>
#include <iostream>

using namespace std;
void init_table(int _table[][MAX_COLUMNS]);
void mark_success(int _table[][MAX_COLUMNS], int state);
void mark_fail(int _table[][MAX_COLUMNS], int state);
bool is_success(int _table[][MAX_COLUMNS], int state);
void mark_cells(int row, int _table[][MAX_COLUMNS], int from, int to, int state);
void mark_cells(int row, int _table[][MAX_COLUMNS], const char columns[], int state);
void mark_cell(int row, int table[][MAX_COLUMNS], int column, int state);
void print_table(int _table[][MAX_COLUMNS]);
void show_string(char s[], int _pos);
bool extract_valid_token(int _table[][MAX_COLUMNS], const char input[],int& string_pos,int start_state,
                         string &tokenizer);


#endif // STATE_FUNCTIONS_H
