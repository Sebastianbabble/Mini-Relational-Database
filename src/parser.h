#ifndef PARSER_H
#define PARSER_H
#include "mmap_class.h"
#include "map_class.h"
#include "stokenizer.h"
#include <sstream>
using namespace std;
class Parser
{
public:

    Parser();
    ~Parser();
    Parser(const char* user_input);
    void initilize_Map();
    void init_table();                              //Initilize parser table
    void make_table();                              //Initilize make table
    void print_table();                             //Prints table
    void mark_success(int state);                   //Marks cells 1
    void mark_fail(int state);                      //Marks cells 0
    void mark_cell(int row,int column,int state);   //Create cell for next state
    MMap<string,string>& sm_translator(bool &success);
    int state_checker(int next_row);
    void print_keywords();
    void print_parse_tree();

private:
    enum keys{SELECT=1,SYMBOL,FROM,WHERE,VALUES,
              EQUAL = 6,GT,LT,GTET,LTET,
              AND = 11, OR,
              MAKE = 13, TABLE,FIELDS,CREATE,
             INSERT =17, INTO , INVALUES};
    vector<string> commands;
    Token token;
    STokenizer stk;
    int table[PARSER_ROWS][PARSER_COLUMNS];
    Map<string,keys> keywords;
    MMap<string,string> parse_tree;

};

#endif // PARSER_H
