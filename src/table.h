#ifndef TABLE_H
#define TABLE_H
#include "record.h"
#include <algorithm>
#include "mmap_class.h"
#include "map_class.h"
#include "file_functions.h"
#include "stack.h"
#include "queue.h"
#include <time.h>

class table{
public:
    table();
    table(const string &table_name);
    table(const string &table_name,const vector<string> &fields); //open table
    void create(); //Creates table with keys from vector and writes to file txt .
    void open(); // Open just opens .txt and .bin files for RW
    void insert_into( vector<string> fields); //Insert fields into MapofMMap
    void load_insert(vector<string> fields,long index);
    table select(const vector<string> &field_name);// Find the field name and ?????
    vector<long> expression_records(const vector<string> &expression); // anything after where
    table select_expression_shuntingyard(vector<string> expression,vector<string> s_fields);
    table shuntingyard_helper(vector<string> expression,vector<string> s_fields);
    table select_all();
    void remove_bin();
    friend ostream& operator<<(ostream& out,const table& print_me){
        print_me.print(out);
        return out;
    }
private:
    void print(ostream& out) const;
private:
    void build_filename(string &temp,const vector<string>& field_name);
    void build_filename(string &temp);
    void build_filename_condition(string &temp);
    table num_to_rec(fstream &fin,const vector<long>& rec_nums,vector<string> s_fields);
    int record_count;
    string name;                                    //Table name
    vector<string> list_of_fields;                  // Fields under table name
    vector<string> command_bin;
    Map<string,MMap<string,long> >list_of_indices;  // Everything
    Map<string,int> fields;

};


#endif // TABLE_H
