#ifndef SQL_H
#define SQL_H
#include "parser.h"
#include "mmap_class.h"
#include "table.h"

class sql{
public:
    sql();
    ~sql();
    void run(string txt_file);
    void run();
    void load();
    void save();
    int& get_fields(string file_name,vector <string> &fields);
    void execute(MMap<string,string> &prompt);
    bool table_checker();
    void remove_files();
private:
    Map<string,table> everything;
    vector<string> table_names;

};

#endif // SQL_H
