#ifndef MMAP_CLASS_H
#define MMAP_CLASS_H
#include "pair_struct.h"
#include "bplustree_class.h"
template <typename K, typename V>
class MMap
{
public:
    typedef BPlusTree<MPair<K, V> > map_base;
    class Iterator{
    public:
        friend class MMap;
        Iterator(typename map_base::Iterator it = NULL){
            _it = it;
        }
        Iterator operator ++(int unused){
            return _it++;
        }
        Iterator operator ++(){
          return ++_it;
        }
        MPair<K, V> operator *(){
            return *_it;
        }

        friend bool operator ==(const Iterator& lhs, const Iterator& rhs){
            return(lhs._it == rhs._it);
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
            return(lhs._it != rhs._it);
        }

    private:
        typename map_base::Iterator _it;
    };

    MMap();
    ~MMap();
    Iterator begin();
    Iterator end();
    Iterator find(const K& key);
    Iterator lower_bound(const K& key);
    Iterator upper_bound(const K& key);
    int size() ;
    bool empty() const;
    const vector<V>& operator[](const K& key) const;
    vector<V>& operator[](const K& key);
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();
    bool contains(const K& key) const;
    vector<V> &get(const K& key);
    int count(const K& key);
    bool is_valid();

    friend ostream& operator<<(ostream& outs, const MMap<K, V>& print_me){
        outs<<print_me.mmap<<endl;
        return outs;
    }

private:
    int keysss;
    BPlusTree<MPair<K, V> > mmap;
};
//PRE: Constructor
template<typename K, typename V>
MMap<K,V>::MMap(){
    keysss = 0;
}
//PRE: Destructor
template<typename K, typename V>
MMap<K,V>::~MMap(){
    keysss = 0;
    mmap.clear_tree();
}

//POST: returns starting point for iterator
template<typename K, typename V>
typename MMap<K,V>::Iterator MMap<K,V>::begin(){
    return mmap.begin();
}
//POST: returns the end point for iterator
template<typename K, typename V>
typename MMap<K,V>::Iterator MMap<K,V>::end(){
    return mmap.end();
}
//POST: returns an int to the size of they keys in map(linked leafs)
template<typename K, typename V>
int MMap<K,V>::size(){
    keysss = mmap.size();
    return keysss;
}
//POST: returns true if its empty
template<typename K, typename V>
bool MMap<K,V>::empty() const{
    if(keysss == 0)
        return true;
    else
        return false;
}
//PRE: takes in a key to find
//POST: returns the value list associated with key
template<typename K, typename V>
const vector<V> &MMap<K,V>::operator[](const K &key) const{
    return mmap.get(MPair<K,V>(key,V())).value_list;
}
//PRE: takes in a key to find
//POST return the value list associated with key and also assigns
template<typename K, typename V>
vector<V> &MMap<K,V>::operator[](const K &key){
    return mmap.get(MPair<K,V>(key,V())).value_list;
}
//PRE: Takes in an value to be inserted
template<typename K, typename V>
void MMap<K,V>::insert(const K &k, const V &v){
    mmap.insert(MPair<K,V>(k,v));
    keysss++;
}
//PRE: takes in a key to be erased
template<typename K, typename V>
void MMap<K,V>::erase(const K &key){
    mmap.remove(key);
}
//POST: Clears tree
template<typename K, typename V>
void MMap<K,V>::clear(){
    mmap.clear_tree();
}
//POST: Returns true if the key is in map
template<typename K, typename V>
bool MMap<K,V>::contains(const K &key) const{
    //changed this
    MPair<K,V> temp;
    temp.key = key;
    return mmap.contains(temp);}
//POST: takes in a key
// POST: gets the value list associated with key
template<typename K, typename V>
vector<V> &MMap<K,V>::get(const K &key){
    return mmap.get(MPair<K,V>(key,V())).value_list;
}
//PRE: takes in a key to find in Iterator
//POST: returns an iterator to the key
template<typename K, typename V>
typename MMap<K,V>::Iterator MMap<K,V>::find(const K &key){
    MPair<K,V> temp;
    temp.key = key;
    for(MMap<K,V>::Iterator it = begin();it != end(); it++)
        if(*it == temp){
            return it;
        }
}
template<typename K, typename V>
typename MMap<K,V>::Iterator MMap<K,V>::lower_bound(const K &key){
    MPair<K,V> temp;
    temp.key = key;
    if(contains(key))
        return find(key);
    else
        for(MMap<K,V>::Iterator it = begin();it != end(); it++){
            if(*it > temp)
                return it;
        }
}
template<typename K, typename V>
typename MMap<K,V>::Iterator MMap<K,V>::upper_bound(const K &key){
    MPair<K,V> temp;
    temp.key = key;
    if(contains(key)){
        for(MMap<K,V>::Iterator it = begin();it != end(); it++)
            if(*it == temp){
                it++;
                return it;
            }
    }
    else
        for(MMap<K,V>::Iterator it = begin();it != end(); it++)
            if(*it > temp){
                return it;
            }
}
//PRE: takes in a key
//POST: returns the size of the keys value list;
template<typename K, typename V>
int MMap<K,V>::count(const K &key){
    return mmap.get(MPair<K,V>(key,V())).value_list.size();
}

#endif // MMAP_CLASS_H
