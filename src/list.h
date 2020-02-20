#ifndef LIST_H
#define LIST_H
#include "linkedlistfunc.h"

template<class T>
class list{
public:
    list();                                 // Constructor
    ~list();                                // Destructor
    list(const list<T> &copy);              //Copy constructor
    list<T>& operator=(list<T> &other);     //Copy assignment operator
    void insert(T insert);
    void insert(node<T>* &node_ptr, T item);
    node<T>* find();                        // Finding the memeory adress or value?????
    T count();
    void print() const;
    T top_delete();
    T print_top();
    bool empty_list();

private:
    node<T>* headptr;
};
//Constructor
template<class T>
list<T>::list(){
    init_head(headptr);
}
//Destructor
template<class T>
list<T>::~list(){
    delete_all(headptr);
}
//Copy constructor
template<class T>
list<T>::list(const list<T> &copy){
    init_head(headptr);
    copy_list(copy.headptr,headptr);

}
//Copy assignment operator
template<class T>
list<T>& list<T>::operator=(list<T> &other){
    if(this != &other){
        copy_list(other.headptr,headptr);
    }
    return *this;
}
template<class T>
void list<T>::insert(T item){
    insert_head(headptr,item);
}
template<class T>
void list<T>::insert(node<T>* &node_ptr, T item){
    insert_after(headptr,node_ptr, item);
}
template<class T>
node<T>* list<T>::find(){

}
template<class T>
T list<T>::count(){

}
template<class T>
void list<T>::print() const{
    print_list(headptr);
}
template<class T>
T list<T>::top_delete(){
    return delete_head(headptr);
}
template<class T>
T list<T>::print_top(){
    return headptr->_item;
}
template<class T>
bool list<T>::empty_list(){
    if(empty(headptr))
        return true;
    else
        return false;
}
#endif // LIST_H
