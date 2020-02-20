#ifndef STOKENIZER_H
#define STOKENIZER_H
#include "token.h"

class STokenizer
{
public:
    STokenizer();
    STokenizer(char str[]);
    STokenizer(string temp);
    bool done();                            //true: there are no more tokens
    bool more();                            //true: there are more tokens
    friend STokenizer& operator >> (STokenizer& s, Token& t);
    void set_string(const char str[]);
    void print();
private:
    void make_table(int _table[][MAX_COLUMNS]);
    bool get_token(int start_state, string& token);
    char _buffer[MAX_BUFFER];               //input string
     int _pos;                              //current position in the string
    static int _table[MAX_ROWS][MAX_COLUMNS];
};

#endif // STOKENIZER_H
