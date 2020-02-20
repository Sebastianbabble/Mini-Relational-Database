
#ifndef QUEUE_H
#define QUEUE_H
#include "linkedlistfunc.h"

template <class T>
class Queue{
public:
    Queue():_head(NULL), _tail(NULL){}
    ~Queue();
    Queue(const Queue<T>& other);
    Queue<T> &operator =(const Queue& rhs);
    void push(T item);
    T pop();
    bool empty_queue();
    T front();
    friend ostream& operator <<(ostream& outs, const Queue& q){
        return print_list(q._head, outs);
    }
private:
    node<T>* _head;
    node<T>* _tail;
};
template<class T>
Queue<T>::~Queue(){
    delete_all(_head);
}
template<class T>
Queue<T>::Queue(const Queue<T>& other){
    _head = NULL;
    _tail = copy_list(other._head,_head);
}
template<class T>
Queue<T>& Queue<T>::operator=(const Queue& rhs){
    if(this != &rhs){
        delete_all(_head);
        _head = NULL;
        _tail = NULL;
        _tail = copy_list(rhs._head,_head);
    }
    return *this;
}
template<class T>
void Queue<T>::push(T item){
    _tail = insert_after(_head,_tail,item);
}
template<class T>
T Queue<T>::pop(){
    const bool debug = true;
    return delete_head(_head);
}
template<class T>
bool Queue<T>::empty_queue(){
    return empty(_head);
}
template<class T>
T Queue<T>::front(){
    return _head->_item;
}
#endif // QUEUE_H
