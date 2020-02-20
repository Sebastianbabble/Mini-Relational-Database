#include "table.h"

//PRE:Takes in a string
//POST: Opens table based on string name
table::table(){
    name = "";
    record_count = 0;
}
table::table(const string &table_name){
    name = table_name;
    record_count = 0;
}
//PRE:Takes in a table name and a vector of fields
//POST: Creates table based on pre info
table::table(const string &table_name,const vector<string> &fields){
    //1. Copy name
    name = table_name;
    //2. Copy fields
    list_of_fields = fields;
    record_count = 0;
    //3. Create file for RW and write out to files as well as initilize
    // list of indices with field names
    create();
}
//PRE: create files based on table names and add values to output file
void table::create(){
    fstream f;
    //1.Initilize files
    open();
    //2. Open file for writing
    open_fileRW(f,(name + ".txt").c_str());
    //3. Intilize map with field keywords and write keywords out to txt file
    for(unsigned int i = 0; i < list_of_fields.size(); i++){
        //4. Write fields out to .txt file for saving
        f << list_of_fields[i] << endl;
        //5. Initilize the list with field names and default mmap
        list_of_indices[list_of_fields[i]] = MMap<string,long>();
        //Make a map of corresponding fields to values
        fields.insert(list_of_fields[i],i);
    }
    //4. Close file
    f.close();
}
//PRE: Create files bases on the table name
void table::open(){
    fstream f;
    //1. Open .txt files
    open_fileRW(f,(name +".txt").c_str());
    f.close();
    //2. Open .bin files
    open_fileRW(f,(name + ".bin").c_str());
    f.close();
}

void table::insert_into( vector<string> fields){
    long temp;
    //1. Initilize record object with the vector fields
    record r(fields);
    fstream f;
    //2.Open file for RW
    open_fileRW(f,(name+ ".bin").c_str());
    //3.Write the fields out to a file and get the index(temp)
    temp = r.write(f);
    //4.Add the fields now to your table with correct indices(temp)
    for(unsigned int i = 0; i < fields.size(); i++){
        //1. string,string += long
        list_of_indices[list_of_fields[i]][fields[i]] += temp;
    }
    record_count++;
    //5. Close file
    f.close();
}
void table::load_insert(vector<string> fields,long index){
    //4.Add the fields now to your table with correct indices(temp)
    for(unsigned int i = 0; i < fields.size(); i++){
        //1. string,string += long
        list_of_indices[list_of_fields[i]][fields[i]] += index;
    }
    record_count++;

}
table table::select(const vector<string> &field_name){
    record s;
    fstream f,fout;
    int i = 0;
    string s_filename;
    vector<string> temp;

    //1.Create table name for write
     build_filename(s_filename,field_name);
     command_bin += s_filename;

    //2.Open table to read from and also create a table to write to
    open_fileRW(f,(name + ".bin").c_str());   

    //3. Create a temp table of conditions selected
    table one(s_filename,field_name);
    s.set_stop(field_name.size());

    //2.Read from file to record
    while(!f.eof()){
        //3.Get record
        s.read(f,i);
        if(f.eof())break;

        //5. Go through selected fields names and extract them from record
        for(unsigned int j = 0; j < field_name.size();j++)        
            if(fields.containss(field_name[j])){
                temp.push_back(s.get_col(fields[field_name[j]]) );
            }

        //6.Insert values into temp table
        one.insert_into(temp);
        temp.clear();
        i++;
    }
    f.close();
    return one;
}

table table::select_expression_shuntingyard(vector<string> expression,vector<string> s_fields){
    Stack<string> relational;
    vector<string> command;


    for(unsigned int i = 0; i < expression.size(); i++){
        if(expression[i] == "and" || expression[i] == "or"){
            while(!relational.empty_stack()){
                if(relational.top() == "or")
                    break;
                command.push_back(relational.pop());
            }
            relational.push(expression[i]);
        }
        else if(expression[i] == "=" || expression[i] == "<"
           || expression[i] == ">" || expression[i] == ">="
           || expression[i] == "<="){
            //1. Push into queue the relationshal operator
            relational.push(expression[i]);
        }
        else
           command.push_back(expression[i]);
    }
    while(!relational.empty_stack()){
        command.push_back(relational.pop());
    }
    return shuntingyard_helper(command,s_fields);
}

table table::shuntingyard_helper(vector<string> expression, vector<string> s_fields){
    string field_name,value,op,file_name;
    vector<string> triple;
    vector<vector<long>> record_list;
    vector<long> combined,temp;
    fstream fin,fout;
    table others;

    //2.Open file to read in from to get records then write out results
    open_fileRW(fin,(name + ".bin").c_str());

    //2. Read until expression vector is empty
   while(!expression.empty()){
        if(expression[0] == "and" || expression[0] == "or"){
            if(expression[0] == "and")            
                set_intersection(record_list[record_list.size() -2].begin(),record_list[record_list.size() -2].end(),record_list[record_list.size()-1].begin(),
                        record_list[record_list.size()-1].end(),back_inserter(combined));            
            else if(expression[0] == "or")         
                set_union(record_list[record_list.size()-2].begin(),record_list[record_list.size()-2].end(),record_list[record_list.size() - 1].begin(),
                        record_list[record_list.size() -1 ].end(),back_inserter(combined));

            expression.erase(expression.begin());

            record_list.pop_back();
            record_list.pop_back();

            record_list.push_back(combined);
            combined.clear();
        }
        else{
            //1. Push first 3 into vector
            for(int i = 0; i < 3; i++){
                triple.push_back(expression[0]);
                expression.erase(expression.begin());
            }

           temp = expression_records(triple);
           sort(temp.begin(),temp.end());

            //2. Push the record to the record list
               record_list.push_back(temp);
               triple.clear();
               temp.clear();
        }
    }
    others = num_to_rec(fin,record_list[0],s_fields);
   //create table in num to rec
   fin.close();
   fout.close();
   return others;

}
//Takes in a vector of size 3 (lname = f) and returns a vector
vector<long> table::expression_records(const vector<string> &expression){
        int i = 0;
        long something;
        vector<long> record_nums;
        string field_name,operate,value,logical;
        MMap<string,long> temp;
        MPair<string,long> hold;

        field_name = expression[i];
        operate = expression[i+2];
        value = expression[i+1];
        temp = list_of_indices[field_name];
        hold.key = value;

        if(operate == "="){
            for(MMap<string,long>::Iterator it = temp.begin(); it != temp.end();it++)
                if(hold == *it)                
                    for(unsigned int j = 0; j < (*it).value_list.size(); j++)
                        record_nums.push_back((*it).value_list[j]);
        }
        else if(operate == "<"){
            for(MMap<string,long>::Iterator it = temp.begin(); it != temp.lower_bound(value);it++)
                    for(unsigned int j = 0; j < (*it).value_list.size(); j++)
                        record_nums.push_back((*it).value_list[j]);
        }
        else if(operate == ">"){
            for(MMap<string,long>::Iterator it = temp.upper_bound(value); it != temp.end();it++)
                    for(unsigned int j = 0; j < (*it).value_list.size(); j++)
                        record_nums.push_back((*it).value_list[j]);
        }
        else if (operate == "<="){
            for(MMap<string,long>::Iterator it = temp.begin(); it != temp.upper_bound(value);it++)
                for(unsigned int j = 0; j < (*it).value_list.size(); j++)
                    record_nums.push_back((*it).value_list[j]);
        }
        else if(operate == ">="){
            for(MMap<string,long>::Iterator it = temp.lower_bound(value); it != temp.end();it++)
                for(unsigned int j = 0; j < (*it).value_list.size(); j++)
                    record_nums.push_back((*it).value_list[j]);
        }

    return record_nums;
}

table table::select_all(){
    record s;
    string s_filename;
    fstream f,fout;
    vector<string> temp;
    build_filename(s_filename);

    int i = 0;
    //1.Open file for RW
    open_fileRW(f,(name+ ".bin").c_str());
    command_bin += s_filename;

    s.set_stop(list_of_fields.size());
    //2. Create a temp table
    table one(s_filename,list_of_fields);

    //2.Read and print records until end of file
    while(!f.eof()){
        s.read(f,i);
        if(f.eof())
            break;
        s.get_values(list_of_fields.size(),temp);
        one.insert_into(temp);
        i++;
        temp.clear();
    }

    return one;
}

void table::remove_bin(){
    for(unsigned int i = 0; i < command_bin.size(); i++){
        remove((command_bin[i] +".bin").c_str());
        remove((command_bin[i] +".txt").c_str());

    }
}

void table::build_filename(string &temp, const vector<string> &field_name){
    string s_filename = name +"_sel_fld_";
    for(unsigned int i = 0; i < field_name.size(); i++)
        s_filename += field_name[i].front();
        s_filename += ".bin";

        temp = s_filename;
}

void table::build_filename(string &temp){
     int r = rand()%(1000-1+1)+1;
     string num = to_string(r);
     string s_filename = (name + "*"+ num);
     temp = s_filename;
}
void table::build_filename_condition(string &temp){
     int r = rand()%(1000-1+1)+1;
     string num = to_string(r);
     string s_filename = (name + "_sel_cond_"+ num +".bin");
     temp = s_filename;
}
table table::num_to_rec(fstream &fin, const vector<long> &rec_nums, vector<string> s_fields){
    record r;
    fstream fout;
    string file_name;
    vector<string> temp;

    build_filename_condition(file_name);
    command_bin += file_name;
    if(s_fields[0] == "*"){
        r.set_stop(list_of_fields.size());

        table one(file_name,list_of_fields);

        for(unsigned int i = 0; i < rec_nums.size();i++){
            r.read(fin,rec_nums[i]);
            r.get_values(list_of_fields.size(),temp);
            one.insert_into(temp);
            temp.clear();
        }
        return one;
    }
    else{
        table two(file_name,s_fields);
        r.set_stop(s_fields.size());
        for(unsigned int i = 0; i < rec_nums.size(); i++){
            r.read(fin,rec_nums[i]);

            for(unsigned int i = 0; i < s_fields.size(); i++){
                if(fields.containss(s_fields[i])){
                    temp.push_back(r.get_col(fields[s_fields[i]]) );
                }
            }
            two.insert_into(temp);
            temp.clear();
        }
        return two;
    }
}
void table::print(ostream &out) const{
    fstream f;
    record r;
    int i = 0;

    open_fileRW(f,(name+ ".bin").c_str());
    r.set_stop(list_of_fields.size());

    out << "Table name: " << name << ", records: " << record_count << endl;

    out << setw(15) << right << "record";

    for(unsigned int i = 0; i < list_of_fields.size(); i++)
        out << setw(15) << right << list_of_fields[i];
    out << endl << endl;
    while(f.good()){
        r.read(f,i);

        if(f.eof()) break;

        out << setw(15) << right << i << ".";
        out << r << endl;
        i++;

    }
    f.close();

}


