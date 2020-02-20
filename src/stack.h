#ifndef STACK_H
#define STACK_H
#include"list.h"


template<class T>
class Stack{
public:
    Stack();
    void push(T item);
    T pop();
    T top();
    bool empty_stack();
    friend ostream& operator << (ostream& outs, const Stack<T>& s){
         s.snake.print();
         return  outs;
    }
private:
    list<T> snake;
};
template<class T>
Stack<T>::Stack(){
}
template<class T>
void Stack<T>::push(T item){
    snake.insert(item);
}
template<class T>
T Stack<T>::pop(){
     return snake.top_delete();
}
template<class T>
T Stack<T>::top(){
    return snake.print_top();
}
template<class T>
bool Stack<T>::empty_stack(){
    if(snake.empty_list())
        return true;
    else
        return false;
}
#endif // STACK_H
