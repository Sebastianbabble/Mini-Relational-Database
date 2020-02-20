#ifndef BTREE_LOWLEVEL_FUNCTIONS_H
#define BTREE_LOWLEVEL_FUNCTIONS_H
#include <iostream>
#include <vector>
using namespace std;

//FUNCTION PROTOTYPES
/****************************************************************************/

template <class T>
T maximal(const T& a, const T& b);
//return the larger of the two items

template <class T>
void swaps(T& a, T& b);  //swap the two items

template <class T>
int index_of_maximal(T data[ ], int n);
//return index of the largest item in data

template <class T>
void ordered_insert(T data[ ], int& n,const T &entry);
//insert entry into the sorted array
//data with length n

template <class T>
int first_ge(const T data[ ], int n, const T& entry);
//return the first element in data that is
//not less than entry

template <class T>
void attach_item(T data[ ], int& n, const T& entry);
//append entry to the right of data

template <class T>
void insert_item(T data[ ], int i, int& n, T entry);
//insert entry at index i in data

template <class T>
void detach_item(T data[ ], int& n, T& entry);
//remove the last element in data and place
//it in entry

template <class T>
void delete_item(T data[ ], int i, int& n, T& entry);
//delete item at index i and place it in entry

template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2);
//append data2 to the right of data1

template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2);
//move n/2 elements from the right of data1
//and move to data2

template <class T>
void copy_array(T dest[], const T src[],
                int& dest_size, int src_size);
//copy src[] into dest[]

template <class T>
void print_array(const T data[], int n, int pos = -1);
//print array data

template <class T>
bool is_gt(const T data[], int n, const T& item);
//item > all data[i]

template <class T>
bool is_le(const T data[], int n, const T& item);
//item <= all data[i]
template <class T>
void insertion_sort(T a[], unsigned int size);

//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list); //print vector list

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme); //list.push_back addme

template <typename T>
vector<T>& operator +=(vector<T>& list, vector<T>& other); //list.push_back addme


//FUNCTION DEFINITIONS
/****************************************************************************/
template <class T>
void insertion_sort(T a[], unsigned int size){
    unsigned int last_index;
    T temp;
    for(unsigned int i = 0; i < size; i++){
        temp = a[i];
        last_index = i;

        while(last_index > 0 && temp < a[last_index -1]){
            a[last_index] = a[last_index -1];
            last_index = last_index - 1;
        }
        a[last_index] = temp;
    }
}
template <class T>
T maximal(const T& a, const T& b){
    if(a > b)
        return a;
    else
        return b;
}
template <class T>
void swaps(T& a, T& b){
    T temp;
    temp = a;
    a = b;
    b = temp;
}
//return index of the largest item in data
template <class T>
int index_of_maximal(T data[ ], int n){
    T largest;
    int large_index = 0;
    largest = data[0];
    for(int i = 1; i < n; i++){
        if(data[i] > largest){
            largest = data[i];
            large_index = i;
        }
    }
    return large_index;
}
//insert entry into the sorted array
//data with length n
template <class T>
void ordered_insert(T data[ ], int& n, const T &entry){
    int temp_index;
    T holder;
    holder = entry;
    temp_index = first_ge(data,n,entry);

    for(int i = temp_index; i < n; i++)
        swaps(data[i],holder);

    data[n] = holder;
    n++;

}
//return the first element in data that is
//not less than entry
template <class T>
int first_ge(const T data[ ], int n, const T& entry){
    for(int i = 0; i < n; i++){
        if(!(data[i] < entry))
            return i;
    }
    return n;
}
//append entry to the right of data
template <class T>
void attach_item(T data[ ], int& n, const T& entry){
    data[n] = entry;
    n++;
}
//insert entry at index i in data
template <class T>
void insert_item(T data[ ], int i, int& n, T entry){
    int hold = n;
    while(hold != i){
        swaps(data[hold-1],data[hold]);
        hold--;
    }
    data[hold] = entry;
    n++;
}
//remove the last element in data and place
//it in entry
template <class T>
void detach_item(T data[ ], int& n, T& entry){
    T temp;
    temp = data[n-1];
    entry = temp;
    n--;
}
//delete item at index i and place it in entry
template <class T>
void delete_item(T data[ ], int i, int& n, T& entry){

    if(i < n){
      entry = data[i];
        while(i < n-1){
            swaps(data[i],data[i+1]);
            i++;
        }
        n--;
    }
}
//append data2 to the right of data1
template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2){
    for(int i = 0; i < n2; i++){
        data1[n1] = data2[i];
        n1++;
    }
    n2 = 0;
}
//move n/2 elements from the right of data1
//and move to data2
template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2){
    T item;
    int mid  = n1/2;
    for(int i = 0; i < mid; i++){
        detach_item(data1,n1,item);
        insert_item(data2,0,n2,item);
    }
}
//copy src[] into dest[]
template <class T>
void copy_array(T dest[], const T src[],
                int& dest_size, int src_size){
    for(int i = 0; i < src_size; i++){
        dest[i] = src[i];
    }
    dest_size = src_size;
}
//print array data
template <class T>
void print_array(const T data[], int n, int pos){
    for(int i = 0; i < n; i++)
        cout << data[i] << ",";
}
//item > all data[i]
//True if item is greater than all data false otherwise
template <class T>
bool is_gt(const T data[], int n, const T& item){
    for(int i = 0; i < n; i++){
        if(data[i] > item){
            return false;
        }
    }
    return true;
}
//item <= all data[i]
//True if item is less than all data false otherwise
template <class T>
bool is_le(const T data[], int n, const T& item){
    for(int i = 0; i < n; i++){
        if(data[i] < item){
            return false;
        }
    }
    return true;
}

//-------------- Vector Extra operators: ---------------------
//print vector list
template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list){
    for(int i = 0; i < list.size(); i++){
        outs << list[i];
        if(i < list.size() -1)
            outs << ",";
    }
    return outs;
}
template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme){
    list.push_back(addme);
    return list;
}
template <typename T>
vector<T>& operator +=(vector<T>& list, vector<T>& other){
    for(int i = 0; i < other.size(); i++)
        list += other[i];
    return list;
}
#endif // BTREE_LOWLEVEL_FUNCTIONS_H
