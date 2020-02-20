#include "sql.h"

sql::sql(){
    if(table_checker()){
        load();
    }
}

sql::~sql(){
    save();
}

void sql::run(string text_file){
    Parser parse;
    ifstream f;
    string temp;
    MMap<string,string> prompt;
    bool success;
    char  point[350];
    string commands ="Commands";
    ofstream fout;
    int i = 0;
    f.open(text_file);

    fout.open("output.txt",ios::app);

    //1.While not end of file
    while(!f.eof()){
       //2. Get first line of file
       f.getline(point,350);
       //3. Add to parser
       Parser other(point);
       //4. Returns a mmap
       prompt = other.sm_translator(success);
       if(success){
           cout <<"["<< i << "] " << point << endl;
           fout <<"[" << i << "] " <<  point << endl;
           execute(prompt);
           cout << endl << endl << "SQL:Done" << endl;
           fout << endl << endl << "SQL:Done" << endl;
           i++;
       }
       else if(point[0] == '/'){
           cout << point << endl;
           fout << point << endl;
       }
    }
    f.close();
}

void sql::run(){
    Parser parse;
    string temp;
    char input[350];
    int i = 1;
    MMap<string,string> prompt;
    bool success = true;
    ofstream f;
    f.open("output.txt",ios::app);

    do{
        cout << "Enter a command" << endl;
        cin.getline(input,350);
        //3. Add to parser
        f << input << endl;
        Parser other(input);
        //4. Returns a mmap
       prompt = other.sm_translator(success);
       if(success){
           cout <<"[" << i <<"] " <<  input << endl;
           f << "[" << i << "]" <<". " <<  input << endl;
           i++;
           execute(prompt);
           cout << endl << endl << "SQL:Done" << endl;

       }
    }while(input[0] != '0');
}

void sql::load(){
    fstream fin,tin;
    string name;
    record r;
    int count;
    vector<string> field_names,field_values;
    long i = 0;
    fin.open("table_names.txt");
    while(!fin.eof()){
        //1. Get table names
        getline(fin,name);
        //2. Get the bin files associated with table names
        tin.open(name +".bin");
        //3. read file contents into everything
        table_names.push_back(name);
        count = get_fields(name,field_names);
        table one(name,field_names);
        everything.insert(name,one);

        //4. Read in all the values from bin
        while(!tin.eof()){
            r.read(tin,i);
            if(tin.eof())break;
            //4.Get field values in vector form
             r.get_values(count,field_values);
            //5. Input them into table map;
            everything[name].load_insert(field_values,i);
            field_values.clear();
            i++;
        }

        field_values.clear();
        field_names.clear();
        i = 0;
        tin.close();
        tin.clear();
    }
}

void sql::save(){
    fstream fout;
    open_fileW(fout,"table_names.txt");
    for(unsigned int i = 0; i < table_names.size(); i++)
        fout << table_names[i] << endl;

    fout.close();
}

int& sql::get_fields(string file_name,vector<string> &fields){
    fstream f;
    string temp;
    int count = 0;

    f.open(file_name + ".txt");
    while(!f.eof()){
        getline(f,temp);
        if(temp.size() != 0){
            fields.push_back(temp);
            count++;
        }
    }
    f.close();
    return count;

}

void sql::execute(MMap<string, string>& prompt){
    string temp;
    vector<string> hold,select_fields;
    table value;
    ofstream fout;
    fout.open("output.txt",ios::app);

    if(prompt["Commands"][0] == "select"){
        //1. If nothing in expression then its not a where command
        if(!(prompt["Expression"].empty())){
            //1. Get table name
            temp = prompt["Table name"][0];
            //2. Get vector of where conditions
            hold += prompt["Expression"];
            select_fields = prompt["Select fields"];
            //3. add to conditions
            if(everything.containss(prompt["Table name"][0])){
               value= everything[temp].select_expression_shuntingyard(hold,select_fields);
               cout << value << endl;
               fout << value << endl;
            }
        }
        //2. Else its just select fields/all
        else{
            //3.Get table name
            temp = prompt["Table name"][0];
            //4.For select alll
            if(prompt["Select fields"][0] == "*"){
                value = everything[temp].select_all();
                cout << value << endl;
                fout << value << endl;
            }
            //5.For select fields
            else{
                hold = prompt["Select fields"];
                value = everything[temp].select(hold);
                cout << value << endl;
                fout<< value << endl;
            }
        }
    }
    else if(prompt["Commands"][0] == "insert"){
        //1. Get table name
        temp = prompt["Table name"][0];
        //2. Get the values;
        hold = prompt["Values"];
        //3. insert values into table
        everything[temp].insert_into(hold);
        cout << "SQL::run: inserted." << endl;
        fout << "SQL::run: inserted." << endl;

    }
    else if(prompt["Commands"][0] == "make" || prompt["Commands"][0] == "create"){
        //1. Get table name
        temp = prompt["Table name"][0];
        table_names.push_back(temp);
        //2. Get vector of fields
        hold = prompt["Field_name"];
        //3.Create table object
        table other(temp,hold);
        //4. Inser table object into member mmap
        everything.insert(temp,other);
        cout << "SQL::run_command: " << prompt["Commands"][0] << " table: " <<
                    hold << endl;
        cout << "SQL::" << prompt["Commands"][0] << "_table(" << temp << ", " <<
                                                  hold << ")" <<  endl;
        cout << "Table " << temp << " created. cols: " << hold << endl;
        fout << "SQL::run_command: " << prompt["Commands"][0] << " table: " <<
                    hold << endl;
        fout << "SQL::" << prompt["Commands"][0] << "_table(" << temp << ", " <<
                                                  hold << ")" <<  endl;
        fout << "Table " << temp << " created. cols: " << hold << endl;
    }

    fout.close();
}

bool sql::table_checker(){
    return file_exists("table_names.txt");

}

void sql::remove_files(){
   for(unsigned int i = 0; i < table_names.size(); i++){
       everything[table_names[i]].remove_bin();
   }
}

