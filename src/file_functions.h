#ifndef FILE_FUNCTIONS_H
#define FILE_FUNCTIONS_H
#include "record.h"
#include <iostream>
using namespace std;
bool file_exists(const char filename[]);
void open_fileRW(fstream& f, const char filename[])throw(char*);
void open_fileW(fstream& f, const char filename[]);
void save_list(record list[], int count);

#endif // FILE_FUNCTIONS_H
