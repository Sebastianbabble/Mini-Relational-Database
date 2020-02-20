#ifndef MAP_CLASS_H
#define MAP_CLASS_H
#include "pair_struct.h"
#include "bplustree_class.h"
template<class K, class V>
class Map
{
public:
    typedef BPlusTree<Pair<K, V> > map_base;
    class Iterator{
    public:
        friend class Map;
        Iterator(typename map_base::Iterator it = NULL){
            _it = it;
        }
        Iterator operator ++(int unused){
            return _it++;
        }
        Iterator operator ++(){
            return _it++;
        }
        Pair<K, V> operator *(){
            return *(_it);
        }
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs){
            return(lhs.it ==  rhs.it);
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
            return(lhs._it != rhs._it);
        }
    private:
        typename map_base::Iterator _it;
    };

    Map();
    ~Map();
    Iterator begin();
    Iterator end();
    Iterator find(const K& key);
    Iterator lower_bound(const K& key);
    Iterator upper_bound(const K& key);
    int size() ;
    bool empty() const;
    V& operator[](const K& key);
    V& at(const K& key);
    const V& at(const K& key) const;
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();
    V get(const K& key);
    bool containss(const Pair<K, V>& target) const;
    bool is_valid(){return map.is_valid();}

    friend ostream& operator<<(ostream& outs, const Map<K, V>& print_me){
        outs<<print_me.map<<endl;
        return outs;
    }
private:
    int key_count;
    BPlusTree<Pair<K, V> > map;
};

//PRE:Constructor
template<class K, class V>
Map<K,V>::Map(){
    key_count = 0;
}
//PRE:Destructor
template<class K, class V>
Map<K,V>::~Map(){
    map.clear_tree();
    key_count = 0;
}

//PRE: Gets the starting point for iterator
//POST: Returns an iterator
template<class K, class V>
typename Map<K,V>::Iterator Map<K,V>::begin(){
    return map.begin();
}
//PRE: Gets the end point for iterator
//POST: returns an iterator
template<class K, class V>
typename Map<K,V>::Iterator Map<K,V>::end(){
    return map.end();
}
//POST: returns size of the all the keys(the linked leafs)
template<class K, class V>
int Map<K,V>::size(){
    key_count = map.size();
    return key_count;
}
//POST: Returns true if the tree is not empty
template<class K, class V>
bool Map<K,V>::empty() const{
    if(key_count == 0)
        return false;
    else
        return true;
}
//PRE:Takes in a key
//POST: Returns the value or assigns to value
template<class K, class V>
V &Map<K,V>::operator[](const K &key){
    return map.get(Pair<K,V>(key,V())).value;
}
//PRE: Takes in a key
//POST: returns the value at key and assigns
template<class K, class V>
V &Map<K,V>::at(const K &key){
    return map.get(Pair<K,V>(key,V())).value;
}
//PRE: Takes in a key
//POST: returns a value but not being called
template<class K, class V>
const V &Map<K,V>::at(const K &key) const{
    return map.get(Pair<K,V>(key,V())).value;
}
//PRE: Takes in a type to be inserted into map
//POST: Inserts into map
template<class K, class V>
void Map<K,V>::insert(const K &k, const V &v){
    Pair<K,V> temp;
    temp.key =k;
    temp.value = v;
    map.insert(temp);
    key_count++;
}
//PRE:takes in a key to be erased
//POST: erases key
template<class K, class V>
void Map<K,V>::erase(const K &key){
    Pair<K,V> temp;
    temp.key = key;
    map.remove(temp);
}
//PRE: Clear map
template<class K, class V>
void Map<K,V>::clear(){
    map.clear_tree();
}
//PRE: Takes in a key
//POST: returns a value from get
template<class K, class V>
V Map<K,V>::get(const K &key){
    return map.get(Pair<K,V>(key,V())).value;
}
//PRE: takes in a key to find in Iterator
//POST:Returns the iterator to the found key
template<class K, class V>
typename Map<K,V>::Iterator Map<K,V>::find(const K &key){
    for(Map<K,V>::Iterator it = begin();it != end(); it++)
        if(*it == key)
            return it;
}
template<class K, class V>
typename Map<K,V>::Iterator Map<K,V>::lower_bound(const K &key){
    if(map.contains(key))
        return find(key);
    else
        return begin();
}

template<class K, class V>
typename Map<K,V>::Iterator Map<K,V>::upper_bound(const K &key){
    if(map.contains(key))
        return find(key);
     else
        return end();
}
//PRE: Takes in a target to check for in map
//POST: returns true if the item is in map
template<class K, class V>
bool Map<K,V>::containss(const Pair<K, V> &target) const{
    return map.contains(target);
}

#endif // MAP_CLASS_H
