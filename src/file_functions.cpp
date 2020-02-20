#include "file_functions.h"
//PRE: Checks to see if file exists then closes file
bool file_exists(const char filename[]){
    const bool debug = false;
    fstream ff;
    ff.open (filename,
        std::fstream::in | std::fstream::binary );
    if (ff.fail()){
        if (debug) cout<<"file_exists(): File does NOT exist: "<<filename<<endl;
        return false;
    }
    if (debug) cout<<"file_exists(): File DOES exist: "<<filename<<endl;
    ff.close();
    return true;
}
//PRE: Opens file for read and write. If cant find input file it creates a
// new file by opening an output.
void open_fileRW(fstream& f, const char filename[]) throw(char*){
    const bool debug = false;

    //1. If file does not exist create by opening output file
    if (!file_exists(filename)){
        f.open(filename, std::fstream::out|std::fstream::binary);
        //2.If fails while opening prompt the user
        if (f.fail()){
            cout<<"file open (RW) failed: with out|"<<filename<<"]"<<endl;
            throw("file RW failed  ");
        }
        else{
            if (debug) cout<<"open_fileRW: file created successfully: "<<filename<<endl;
        }
    }
    //3. If the file does exist open it up for input AND output
    else{
        f.open (filename,
            std::fstream::in | std::fstream::out| std::fstream::binary );
        //4. If fails while opening prompt the user
        if (f.fail()){
            cout<<"file open (RW) failed. ["<<filename<<"]"<<endl;
            throw("file failed to open.");
        }
    }
}
//PRE: This just opens output file to write but no input
void open_fileW(fstream& f, const char filename[]){
    f.open (filename,
            std::fstream::out| std::fstream::binary );
    if (f.fail()){
        cout<<"file open failed: "<<filename<<endl;
        throw("file failed to open.");
    }
}
//PRE: Takes in array of records and the size(count)
void save_list(record list[], int count){
    fstream f;
    open_fileW(f, "record_list.bin");
    for (int i= 0; i<count; i++){
        list[i].write(f);
    }
    f.close();
}
