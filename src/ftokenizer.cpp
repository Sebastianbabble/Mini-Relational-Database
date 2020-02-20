#include "ftokenizer.h"

FTokenizer::FTokenizer(){

}
FTokenizer::FTokenizer(char* fname){
    //Open the file
    _f.open(fname);
    _more = true;
    if(!_f){
        cout << "Could not find file please re-enter another name" << endl;
    }
    get_new_block();
}
//PRE:Getting the next token and checking if it needs to get new block
Token FTokenizer::next_token(){
    Token t;
    if(!(_stk.more())){
       _more = get_new_block();
    }
    _stk >> t;
    return t;
}
//PRE: returns the current value of _more
bool FTokenizer::more(){
    return _more;
}
//PRE: returns the value of _pos
int FTokenizer::pos(){
    return _pos;
}
//PRE: returns the value of _blockPos
int FTokenizer::block_pos(){
    return _blockPos;
}
//PRE: gets the new block from the file
bool FTokenizer::get_new_block(){
    char buffer[MAX_BUFFER];
    //Read in a block and put it into buffer
    _f.read(buffer,MAX_BUFFER-1);

    if (_f.gcount() == 0){
        return false;
    }
   _pos += _f.gcount();
    _stk.set_string(buffer);
    return true;
}

FTokenizer& operator >> (FTokenizer& f, Token& t){
    t = f.next_token();
    return f;

}
