#ifndef PAIR_STRUCT_H
#define PAIR_STRUCT_H
#include <iostream>
#include <vector>
#include "btree_lowlevel_functions.h"
using namespace std;
template <typename K, typename V>
struct Pair{
    K key;
    V value;

    Pair(const K& k=K(), const V& v=V()){
        key = k;
        value = v;
    }
    friend ostream& operator <<(ostream& outs, const Pair<K, V>& print_me){
        outs << "[" << print_me.key <<"| " <<  print_me.value << "]";
        return outs;
    }
    friend bool operator ==(const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return (lhs.key == rhs.key);
    }
    friend bool operator < (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return (lhs.key < rhs.key);
    }
    friend bool operator > (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return (lhs.key > rhs.key);
    }
    friend bool operator <= (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return (lhs <= rhs);
    }
    Pair<K,V>& operator += ( const Pair<K, V>& rhs){
       value = rhs.value;
       return *this;
    }
    friend Pair<K, V> operator + (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return lhs;
    }
};
template <typename K, typename V>
struct MPair{
    K key;
    vector<V> value_list;
    MPair(const K& k=K()){
        key = k;
    }
    MPair(const K& k, const V& v = V()){
        key = k;
    }
    MPair(const K& k, const vector<V>& vlist){
        key = k;
        value_list.erase(value_list.begin(),value_list.back());
        for(int i = 0; i < vlist.size(); i++)
            value_list.push_back(vlist[i]);
    }
    friend ostream& operator <<(ostream& outs, const MPair<K, V>& print_me){
        outs << "[" << print_me.key <<"| ";
        outs << print_me.value_list << "]";
        return outs;
    }
    MPair<K,V>& operator += ( const MPair<K, V>& rhs){
        for(int i = 0; i <rhs.value_list.size(); i++)
        value_list += rhs.value_list[i];
        return *this;
    }
    friend bool operator ==(const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return (lhs.key == rhs.key);
    }
    friend bool operator < (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return (lhs.key < rhs.key);
    }
    friend bool operator <= (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return (lhs.key <= rhs.key);
    }
    friend bool operator >= (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return (lhs.key >= rhs.key);
    }
    friend bool operator > (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return (lhs.key > rhs.key);
    }
    friend MPair<K, V> operator + (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return lhs;
    }
};
#endif // PAIR_STRUCT_H
