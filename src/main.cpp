/*
 * Author: Sebastian Enciso
 * Project: Database.
 * Purpose: Build a database with your existing projects
 * Notes: Everything was implemented and all tests have been passed
 *
 */
#include <iostream>
//#include "test_functions.h"
#include "sql.h"
using namespace std;

//TODO: add remove feature so you can remove stuff from a table
//     Merge both tables together so you can have a student employee table I guess??
int main()
{
    sql s;
    //s.run("cs8.txt");
    s.run();
    s.remove_files();
    cout << "End" << endl;
    return 0;
}

