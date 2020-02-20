#ifndef LINKEDLISTFUNC_H
#define LINKEDLISTFUNC_H
#include<iostream>
#include<assert.h>
using namespace std;

template <class T>
struct node{
    T _item;
    node<T>* _next;
    node(const T& item = T(), node<T>* next = NULL):_item(item), _next(next){}

    friend ostream& operator << (ostream& outs, const node<T>& print_me){
        outs<<"["<<print_me._item<<"]->";
        return outs;
    }
};

//initializes head to NULL
template <class T>
node<T>* init_head(node<T>* &head);
//deletes all the nodes in the list
template<class T>
void delete_all(node<T>*&head);
//true if head is NULL, false otherwise.
template <class T>
bool empty(const node<T>* head);
//makes a copy of the list, returns a pointer to the last node:
template <class T>
node<T>* copy_list(const node<T>* head, node<T>* & cpy);
//insert at the beginning of the list:
template <class T>
node<T>* insert_head(node<T>* &head, T item);
//insert_after: if after is NULL, inserts at head
template <class T>
node<T>* insert_after(node<T>* &head, node<T>* after, const T& item);
//delete the node at the head of the list, reuturn the item:
template <class T>
T delete_head(node<T>*&head);
//print the list and return outs
template<class T>
ostream& print_list(const node<T>* head, ostream& outs=cout);

//initializes head to NULL
template <class T>
node<T>* init_head(node<T>* &head){
    head = nullptr;
}
//deletes all the nodes in the list
template<class T>
void delete_all(node<T>*&head){
    while(head!=NULL){
        delete_head(head);
    }
}
//true if head is NULL, false otherwise.
template <class T>
bool empty(const node<T>* head){
    if(head == nullptr)
        return true;
    else
        return false;
}
//makes a copy of the list, returns a pointer to the last node:
template <class T>
node<T>* copy_list(const node<T>* head, node<T>* & cpy){
    const node<T>* walker;
    node<T>* temp;
    walker = head;
    temp = cpy;
    while(walker != NULL){
         temp = insert_after(cpy,temp,walker->_item);
         walker = walker->_next;
    }
    return temp;
}
//insert at the beginning of the list:
template <class T>
node<T>* insert_head(node<T>* &head, T item){
    node<T>*  temp_ptr;
    temp_ptr = new node<T>;
    temp_ptr->_item = item;
    temp_ptr->_next = head;
    head = temp_ptr;
    return temp_ptr;

}
//insert_after: if after is NULL, inserts at head
template <class T>
node<T>* insert_after(node<T>* &head, node<T>* after, const T& item){
    node<T> *temp_ptr;
    node<T> *result;
    temp_ptr = new node<T>;

    if(!(empty(after))){
        if(!empty(head)){
            temp_ptr->_item = item;
            temp_ptr->_next = after->_next;
            after->_next = temp_ptr;
            result = temp_ptr;
        }
        else
            result = insert_head(head, item);
    }
    else{
       result = insert_head(head, item);
    }
    return result;
}
//delete the node at the head of the list, reuturn the item:
template <class T>
T delete_head(node<T>* &head){
    assert(head!=NULL);

    if(head != NULL){
        node<T>* temp_ptr = head;
        T item;
        head = head->_next;
        item = temp_ptr->_item;
        delete temp_ptr;
        return item;
    }

}
//print the list and return outs
template<class T>
ostream& print_list(const node<T>* head, ostream& outs){
  for(; head != NULL; head = head->_next)
       outs << *head;
  outs << "|||";
  outs << endl;
  return outs;
}
#endif // LINKEDLISTFUNC_H



