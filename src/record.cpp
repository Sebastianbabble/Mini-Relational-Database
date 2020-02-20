#include "record.h"

record::record(){
    //1.Initilize 2d array to NULL using memset
    memset(f_record,NULL,sizeof (f_record));
    //2. Set recno to -1??
    recno = -1;
    rec_count = 0;
}
record::record(vector<string>& str){
    //1.Copy vector to a 2d char array
    for(unsigned int i = 0; i < str.size(); i++){
        strcpy(f_record[i],str[i].c_str());
    }
    recno = -1;
}
long record::write(fstream &outs){

     //1.Sets the position of the next character to be outputted
     outs.seekg(0,ios_base::end);
     //2. Get the current position in the outputstream. Current position/size
     long pos = outs.tellp()/sizeof (f_record);
     recno = pos;
     //3. Write out to file from f_record
     outs.write(reinterpret_cast<char *>(f_record), sizeof (f_record));
     //4. Return the position
    return pos;
}

long record::read(fstream &ins, long recno){
    //1.Get the pos to start reading from
    long pos = recno * sizeof (f_record);
    //2. Sets the position of the next character to be extracted from input
    ins.seekg(pos,ios_base::beg);
    //3. Read in from file to f_record
   ins.read(reinterpret_cast<char *>(f_record),sizeof (f_record));
    //4. Returns the number of characters in input stream
    return ins.gcount();

}

void record::print_record(const int &stop){
    // Need to change the for loop paramter left it for testing
    for(int i = 0; i < stop; i++){
        cout << f_record[i] << endl;
    }
    cout << "*************************************" << endl;
}

string record::get_col(const int &row){
    return f_record[row];
}

void record::set_stop(int i){
    stop = i;
}

void record::get_values(int size,vector<string>& temp){
    for(int i = 0; i < size; i++)
        temp.push_back(f_record[i]);
}

