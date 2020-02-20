#include "parser.h"
//PRE: Constructor
Parser::Parser(){
    init_table();
}
//PRE: Destructor
Parser::~Parser(){

}
//PRE: Constructor
Parser::Parser(const char* user_input){
    stringstream ss;
    string quotes;
    bool hold;
   //1. Intilize table to -1;
   init_table();
   //2. Create string tokenizer with string
   stk.set_string(user_input);
   //3. Push all the key/commands into a vector
   while(stk.more()){
       stk >> token;
       if(token.type_string() != "SPACE" && token.token_str() != ",")
            commands.push_back(token.token_str());
   }
   initilize_Map();
   //4. Create a table
   make_table();
}

void Parser::initilize_Map(){
    //1. Select machine keywords;
    keywords.insert("select",SELECT);
    keywords.insert("symbol",SYMBOL);
    keywords.insert("from",FROM);
    keywords.insert("where", WHERE);
    //2. Hard insert relational operators cause seems easier to parse
    keywords.insert("=",EQUAL);
    keywords.insert(">",GT);
    keywords.insert("<",LT);
    keywords.insert(">=",GTET);
    keywords.insert("<=",LTET);
    keywords.insert("and",AND);
    keywords.insert("or",OR);
    //3. Create/Make machine keywords
    keywords.insert("make",MAKE);
    keywords.insert("table",TABLE);
    keywords.insert("fields",FIELDS);
    keywords.insert("create",CREATE);
    //4. Insert machine keywords
    keywords.insert("insert",INSERT);
    keywords.insert("into",INTO);
    keywords.insert("values",INVALUES);

}
//PRE: takes in a table
//POST: Initilizes table
void Parser::init_table(){
    //1.Creates of value -1
    for(int row = 0; row < PARSER_ROWS; row++)
        for(int col = 0; col < PARSER_COLUMNS; col++ ){
            if(col == 0)
                table[row][col] = 0;
            else
            table[row][col] = -1;
        }
}
//PRE: Make table
void Parser::make_table(){
    //1. Mark column with success for Select state machine
    //Mark_cells(row,column,state)
    mark_success(4);
    mark_success(8);
    mark_success(16);
    mark_success(17);
    mark_success(20);
    //2.SELECT state machine
    mark_cell(0,1,SELECT);                  // SELECT = 1
    mark_cell(SELECT,2,SYMBOL);             //SYMBOL = 2;
    mark_cell(SYMBOL,SYMBOL,SYMBOL);
    mark_cell(SYMBOL,3,FROM);               // FROM = 3
    mark_cell(3,SYMBOL,4);
    mark_cell(4,SYMBOL,4);
    mark_cell(4,4,5);                       // WHERE = 4
    mark_cell(5,SYMBOL,6);
    mark_cell(7,SYMBOL,8);
    mark_cell(6,EQUAL,7);                   //GT = 6
    mark_cell(6,GT,7);                      //GT = 7
    mark_cell(6,LT,7);                      //LT = 8
    mark_cell(6,GTET,7);                    //GTET = 9
    mark_cell(6,LTET,7);                    //LTET = 10
    mark_cell(7,VALUES,8);
    mark_cell(8,AND,5);
    mark_cell(8,OR,5);
    //3. CREATE/MAKE state machine
    mark_cell(0,MAKE,13);
    mark_cell(13,TABLE,14);
    mark_cell(14,SYMBOL,15);
    mark_cell(0,CREATE,13);
    mark_cell(15,FIELDS,16);
    mark_cell(16,SYMBOL,16);
    //4. INSERT state machine
    mark_cell(0,INSERT,17);
    mark_cell(17,INTO,18);
    mark_cell(18,SYMBOL,19);
    mark_cell(19,INVALUES,20);
    mark_cell(20,SYMBOL,20);

}
//PRE: print
void Parser::print_table(){
    for(int i = 0; i<PARSER_COLUMNS+1; i++){
        if(i == 0)
            cout <<"        ";
        else
       cout << setw(4) << left <<  "col " << setw(2)<< left << i-1 <<"|";
    }
       cout << endl;
    for(int row = 0; row < PARSER_ROWS; row++){
        cout << "row " << setw(3) << row ;
        for(int col = 0; col < PARSER_COLUMNS; col++ ){
            cout << "|" << setw(6) << left <<  table[row][col] ;
        }
        cout << endl;
    }
}
//PRE: take in a row that you want to mark as a success
void Parser::mark_success(int state){
    table[state][0] = 1;
}
//PRE: take in a row that u wnat to make final.
void Parser::mark_fail( int state){
    table[state][0] = 0;
}
//PRE: Mark a cell to notify the next row to move to
void Parser::mark_cell(int row, int column, int state){
    table[row][column] = state;
}

MMap<string,string>& Parser::sm_translator(bool &success){
    int state = 0,next_row = 0,state_col = 0,where = 0;
    bool debug = false;

    //1. Go through the vector one by one and check each key
    for(unsigned int i = 0; i < commands.size(); i++){
        if(debug)cout << "command[i]-->" << commands[i] << endl;

        //2.If the command is a key then check state and next row
        if(keywords.containss(commands[i])){
            //2. Getting the info from the state machine
            state_col = keywords.get(commands[i]);
            next_row = table[next_row][state_col];
            state = state_checker(next_row);
            //3. If you find keyword put it under appropriate key
            if(keywords[commands[i]] == SELECT || keywords[commands[i]] == INSERT
               ||keywords[commands[i]] == MAKE || keywords[commands[i]] == CREATE)
                parse_tree["Commands"] += commands[i];
            else if(keywords[commands[i]] == WHERE)
                where = i+1;
        }
        //4.If its not in keywords insert into parse_tree under appropriate key
        else{
            //5. Checking commands to put into parse_tree.
             if(next_row == FROM || next_row == TABLE || next_row == INTO)
                 parse_tree["Table name"] += commands[i];
            else if(next_row == 20 || next_row == 19)// || next_row == AND) next_row == GT ||
                parse_tree["Values"] += commands[i];
             else if(next_row == SELECT || next_row == 2)
                 parse_tree["Select fields"] += commands[i];
            else //next_row == fields if you want to clean
                parse_tree["Field_name"] += commands[i];

            //6. Updating state machine
            next_row = table[next_row][SYMBOL];
            state = state_checker(next_row);
        }

        //7.If next row is -1 then command is invalid
        if(next_row == -1){
            success = 0;
            return parse_tree;
        }
    }
        //8. Ughhh If its a success and the vector had where commands in it
        // Put in own part of parse tree
        if(state && where != 0)
            for(unsigned int i = where;i < commands.size(); i++)
                  parse_tree["Expression"] += commands[i];

        success = state;
     return parse_tree;
}

int Parser::state_checker(int next_row){
    return table[next_row][0];
}
void Parser::print_keywords(){
    cout << keywords << endl;
}
void Parser::print_parse_tree(){
    cout << parse_tree << endl;
}

