#include "stokenizer.h"
int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];
//Constructor
STokenizer::STokenizer(){
    make_table(_table);
}
//Constructor
STokenizer::STokenizer( char str[]){
    _pos = 0;
    memcpy(_buffer,str,MAX_BUFFER);
    make_table(_table);
}

STokenizer::STokenizer(string temp){
    _pos = 0;

}
//Opposite of more()
bool STokenizer::done(){
    if(_buffer[_pos] == '\0'){
        return true;
    }
    return false;

}
//Returns true if its the end of the token
bool STokenizer::more(){

    if(_buffer[_pos] != '\0')
        return true;
            else
    return false;
}
//Gets the token and finds the corresponding start state
STokenizer& operator >> (STokenizer& s, Token& t){
    string temp;
    string another;
    int start;
    int pos = 0;
    start = t.type();
    temp = s._buffer;
    if(s.get_token(DIGITS_START,temp)){
        t = Token(temp,DIGITS_START);
    }
    else if(s.get_token(ALPHA_START,temp)){
        t = Token(temp,ALPHA_START);
    }
    else if(s.get_token(SPACE_START,temp)){
        t = Token(temp,SPACE_START);
    }
    else if(s.get_token(UNKNOWN_START,temp)){
        t = Token(temp,UNKNOWN_START);
    }
    else if(s.get_token(99,temp)){
        t = Token(temp,99);
    }
    else{
        t = Token({s._buffer[s._pos], '\0'}, UNKNOWN_START);
        s._pos++;
    }

    return s;

}
// Sets up the string
void STokenizer::set_string(const char str[]){
    memcpy(_buffer,str,MAX_BUFFER-1 );
   _buffer[MAX_BUFFER]= '\0';
    _pos = 0;

}
//This functino intializes all the values into the table
void STokenizer::make_table(int _table[][MAX_COLUMNS]){

    init_table(_table);

    mark_fail(_table, 0);            //Mark states 0 and 2 as fail states
    mark_success(_table, 1);         //Mark states 1 and 3 as success states
    mark_fail(_table, 2);
    mark_success(_table, 3);

    //DIGITS
    mark_cells(0, _table, DIGITS, 1);    //state [0] --- DIGITS ---> [1]
    //mark_cells(0, _table, '.', '.', 2);  //state [0] --- '.' ------> [2]
    mark_cells(1, _table, DIGITS, 1);    //state [1] --- DIGITS ---> [1]
    mark_cells(1, _table, '.', '.', 2);  //state [1] --- '.' ------> [2]
    mark_cells(2, _table, DIGITS, 3);    //state [2] --- DIGITS ---> [3]
    mark_cells(3, _table, DIGITS, 3);    //state [3] --- DIGITS ---> [3]

    //ALPHA
    mark_fail(_table, 6);
    mark_success(_table, 7);         //Mark states 1 and 3 as success states
    mark_cells(6, _table, ALPHA, 7);    //state [0] --- DIGITS ---> [1]
    //mark_cells(0, _table, '.', '.', 2);  //state [0] --- '.' ------> [2]
    mark_cells(7, _table, ALPHA, 7);    //state [1] --- DIGITS ---> [1]

    //SPACE
    mark_fail(_table, 8);
    mark_success(_table,9);
    mark_cell(8, _table,32, 9);
    mark_cell(9,_table, 32, 9);

    //TAB
    mark_cell(8, _table,9,9);
    mark_cell(9,_table,9,9);
    //state [0] --- DIGITS ---> [1]

    //UKKNOWN
    mark_fail(_table,10);
    mark_success(_table,11);
    //1st set of unknown characters 33-46(ASCII)
    mark_cells(10,_table,35,47,11);
    mark_cells(11,_table,35,47,12);

    mark_fail(_table,99);
    mark_success(_table,100);
    mark_success(_table,101);
    mark_fail(_table,102);

    mark_cell(99,_table,34,100);
    mark_cells(100,_table,' ','!',100);
    mark_cells(100,_table,'#','~',100);
    mark_cell(100,_table,34,101);
    mark_cell(101,_table,34,99);

    //2nd set of unknown characters 58-64(ASCII)
    mark_cells(10,_table,58,64,11);
    mark_cells(11,_table,58,64,11);
    //3nd set of unknown characters
    mark_cells(10,_table,91,96,11);
    mark_cells(11,_table,91,96,12);
    //4th set of unknown characters
    mark_cells(10,_table,123,126,11);
    mark_cells(11,_table,123,126,12);


}
//This function calles extract valid token from state functions
bool STokenizer::get_token(int start_state, string& token){
    bool something;
    //This is turning temp into token
    something = extract_valid_token(_table,_buffer,_pos,start_state,token);
    return something;
}
//This function just prints the current string
void STokenizer::print(){
    int i = 0;
    while(_buffer[i] != '\0'){
        i++;
    }

}



