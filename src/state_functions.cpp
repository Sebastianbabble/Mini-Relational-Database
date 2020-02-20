#include"state_functions.h"
//This initilizes the table to either 0 or 1
void init_table(int _table[][MAX_COLUMNS]){
    for(int row = 0; row < MAX_ROWS; row++)
        for(int col = 0; col < MAX_COLUMNS; col++ ){
            if(col == 0)
                _table[row][col] = 0;
            else
            _table[row][col] = -1;
        }
}
//This prints the table out in the terminal with the values
void print_table(int _table[][MAX_COLUMNS]){
    for(int row = 0; row < MAX_ROWS; row++){
        for(int col = 0; col < MAX_COLUMNS; col++ ){
            cout << _table[row][col];
        }
        cout << endl;
    }
}
//This function marks a cell as success
void mark_success(int _table[][MAX_COLUMNS], int state){
    _table[state][0] = 1;
}
//This function marks a cell as fail
void mark_fail(int _table[][MAX_COLUMNS], int state){
    _table[state][0] = 0;

}
//This function checks to see if the last state was a success or not
bool is_success(int _table[][MAX_COLUMNS], int state){
    if(_table[state][0] == 1)
        return true;
    else if(_table[state][0] == 0)
            return false;
}
//This function marks cells with whats given
void mark_cells(int row, int _table[][MAX_COLUMNS], int from, int to, int state){
    for(int i = from; i <= to; i++){
        _table[row][i] = state;
    }
}
//This is the same function as above but with di parapmeters
void mark_cells(int row, int _table[][MAX_COLUMNS], const char columns[], int state){
    int i = 0;
    while(columns[i] != '\0'){
        _table[row][(int)columns[i]] = state;
        i++;
    }
}
//This is the same function as above but with di parapmeters
void mark_cell(int row, int _table[][MAX_COLUMNS], int column, int state){
    _table[row][column] = state;
}
//This function shoes the current string with the given pos.
void show_string(char s[], int _pos){
    int i = 0;
    int j = 0;
    string temp = "";
    for(int i = 0; i <= _pos; i++){
        if(i != _pos)
            temp+= " ";
        else
            temp+="^";
    }
    cout << s;
    cout << endl;
    cout << temp;
    cout << endl;

}
//This function gets the token and returns it by reference and also returns true
// or false depending on the if it was a success or not.
bool extract_valid_token(int _table[][MAX_COLUMNS], const char input[],int &string_pos,int start_state,
                         string &tokenizer){
    int current_state = start_state;
    int count = string_pos;
    int success_count = 0;
    int last_state = 0;
    bool valid = true;

    tokenizer = "";

    while((input[count]) != '\0'){

        if((int)input[count] < -1){

            count = count+1;
            break;
        }

        if(_table[current_state][(int)input[count]] != -1 && (int)input[count] > 0){

          current_state = _table[current_state][(int)input[count]];
          success_count++;

        }
            if(!is_success(_table,current_state)){

               if((int)(input[count+1]) == '\0' || _table[last_state][(int)input[count+1]] == -1)
                   break;
            }
            else if (_table[current_state][(int)input[count]] == -1){
                break;
            }
        if(success_count == 0){
            return false;
        }
        else{
            if(input[count]!= '\"'){
                tokenizer += input[count];
            }
        }
        count++;
    }

    if(success_count == 0){
        return false;
    }
    string_pos = count;
    return valid;
}
