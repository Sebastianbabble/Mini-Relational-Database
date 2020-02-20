#ifndef RECORD_H
#define RECORD_H
#include <iostream>
#include <fstream>
#include <string>
#include "constants.h"
#include <vector>
#include <iomanip>
using namespace std;

class record{
public:
    record();
    record(vector<string>& str);
    long write(fstream& outs);
    long read(fstream& ins,long recno);
    void print_record(const int& stop);
    string get_col(const int &row);
    void set_stop(int i);
    void get_values(int size,vector<string>& temp);

    friend ostream& operator << (ostream& outs, const record& r){
        for(int i = 0; i < r.stop; i++)
            outs << setw(15) << right << r.f_record[i];
        return outs;
    }

private:
    int stop;
    int recno;
    int rec_count;
    char f_record[MAX][MAX];

};

#endif // RECORD_H
