#ifndef BPLUSTREE_CLASS_H
#define BPLUSTREE_CLASS_H
#include<iostream>
#include "bTree_lowlevel_functions.h"
#include<iomanip>
#include<assert.h>
using namespace std;
template <class T>
class BPlusTree
{
public:
    class Iterator{
        public:
            friend class BPlusTree;
            Iterator(BPlusTree<T>* _it=NULL, int _key_ptr = 0):it(_it), key_ptr(_key_ptr){}

            T operator *(){
                assert(key_ptr<it->data_count);
                return it->data[key_ptr];
            }

            Iterator operator++(int un_used){
                Iterator temp(this->it,this->key_ptr);

                if(key_ptr+1 == it->data_count){
                    it = it->next;
                    key_ptr = 0;
                }
                else{
                    key_ptr++;
                }
                return temp;
            }

            Iterator operator++(){
                if(key_ptr+1 == it->data_count){
                    it = it->next;
                    key_ptr = 0;
                }
                else{
                    key_ptr++;
                }

                return *this;
            }

            friend bool operator ==(const Iterator& lhs, const Iterator& rhs){
                return(lhs.it == rhs.it && lhs.key_ptr == rhs.key_ptr);
            }

            friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
                return(lhs.it != rhs.it || lhs.key_ptr != rhs.key_ptr);
            }
            bool is_null(){return !it;}
        private:
            BPlusTree<T>* it;
            int key_ptr;
        };

    BPlusTree(bool dups = false);
    BPlusTree(const BPlusTree<T>& other);
    ~BPlusTree();
    BPlusTree<T>& operator =(const BPlusTree<T>& RHS);
    void insert(const T& entry);                                        //insert entry into the tree
    void remove(const T& entry);                                        //remove entry from the tree
    void clear_tree();                                                  //clear this object (delete all nodes etc.)
    void copy_tree(const BPlusTree<T>& other);                          //copy other into this object
    void copy_tree(const BPlusTree<T>& other,BPlusTree<T>* &temp_ptr);  //copy other into this object
    bool contains(const T& entry) const;                                //true if entry can be found in the array
    T const& get(const T& entry)const;
    T& get(const T& entry);                                             //return a reference to entry in the tree
    T* find(const T& entry);
    T& get_existing(const T& entry);                                    //return a pointer to this key. NULL if not there.
    int size()  ;                                                       //count the number of elements in the tree
    bool empty() const;                                                 //true if the tree is empty
    void print_tree(int level = 0, ostream &outs=cout) const;           //print a readable version of the tree
    friend ostream& operator<<(ostream& outs, const BPlusTree<T>& print_me){
        print_me.print_tree(0, outs);
        return outs;
    }
//private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok;                                                       //true if duplicate keys may be inserted
    int data_count;                                                     //number of data elements
    T data[MAXIMUM + 1];                                                //holds the keys
    int child_count;                                                    //number of children
    BPlusTree* subset[MAXIMUM + 2];                                     //suBPlusTrees
    BPlusTree* next;
    int total_count;
    bool is_leaf() const {return child_count==0;}                       //true if this is a leaf node
    void loose_insert(const T& entry);                                  //allows MAXIMUM+1 data elements in the root
    void fix_excess(int i);                                             //fix excess of data elements in child i
    void loose_remove(const T& entry);                                  //allows MINIMUM-1 data elements in the root
    void fix_shortage(int i);                                           //fix shortage of data elements in child i
    void remove_biggest(T& entry);                                      //remove the biggest child of this tree->entry
    void rotate_left(int i);                                            //transfer one element LEFT from child i
    void rotate_right(int i);                                           //transfer one element RIGHT from child i
    void merge_with_next_subset(int i);                                 //merge subset i with subset i+1
    bool is_valid();
    bool Between(T data[], int data_count,int min, int max);
    Iterator begin();
    Iterator end();
    BPlusTree<T>* get_smallest_node();
    void get_smallest(T& entry);                                        //entry := leftmost leaf
    void get_biggest(T& entry);                                         //entry := rightmost leaf
    void transfer_left(int i);                                          //transfer one element LEFT from child i
    void transfer_right(int i);                                         //transfer one element RIGHT from child i

};

//**************************************FUNCTIONS*******************************
template<class T>
BPlusTree<T>::BPlusTree(bool dups ){
    dups_ok = dups;
    child_count = 0;
    data_count = 0;
    next = NULL;
}

template<class T>
BPlusTree<T>::BPlusTree(const BPlusTree<T> &other){
    data_count = 0;
    child_count = 0;
    copy_tree(other);
}

template<class T>
BPlusTree<T>::~BPlusTree(){
    clear_tree();
    data_count = 0;
    child_count = 0;
}

template<class T>
BPlusTree<T> &BPlusTree<T>::operator =(const BPlusTree<T> &RHS){
    if(this != &RHS){
        copy_tree(RHS);
    }
    return *this;
}
//PRE: Takes in a data type to be inserted
//POST: Inserts Item into tree
template<class T>
void BPlusTree<T>::insert(const T &entry){
    loose_insert(entry);
    if(data_count >= MAXIMUM+1){
        BPlusTree<T> *temp = new BPlusTree<T>;
        int t = 0;
        copy_array(temp->data,data,temp->data_count,data_count);
        copy_array(temp->subset,subset,temp->child_count,child_count);
        data_count = 0;
        child_count = 1;
        subset[0] = temp;
        fix_excess(t);
    }
}
//PRE: Takes in a data type to be
//POST: Removes entry from tree
template<class T>
void BPlusTree<T>::loose_insert(const T &entry){
     int index = first_ge(data,data_count, entry);
     bool found = (index < data_count && data[index] == entry);

     //1. Entry is already in tree
     if(found){
        //2. Entry is a leaf
         if(is_leaf()){
              if(dups_ok)
                data[index] = entry;
              else
                  data[index] += entry;
              total_count++;
         }
         //3. Entry is not a leaf
         else{
             subset[index+1]->loose_insert(entry);

          //4. If node is at its maximum we need to restructure tree
         if(subset[index+1]->data_count > MAXIMUM)
             fix_excess(index+1);
         }
     }
     //5. Entry is not in tree
     else{
         //6. If at a leaf then insert
         if(is_leaf())
             ordered_insert(data,data_count,entry);
         else{
            subset[index]->loose_insert(entry);
            //7. If node is at its maximum we need to restructure tree
             if(subset[index]->data_count > MAXIMUM){
                 fix_excess(index);
             }
         }
     }
}
//PRE:Takes in an index
//POST: Fixes the excess at index by splitting
template<class T>
void BPlusTree<T>::fix_excess(int i){
    BPlusTree<T> *temp2 = new BPlusTree<T>;
    int size = i+1;
    T hold =T();

    //1. insert temp pointer into subsets
    insert_item(subset,size,child_count,temp2);
    //2. Split subsets[i] data
    split(subset[i]->data,subset[i]->data_count,subset[i+1]->data,subset[i+1]->data_count);
    //3. Split subsets[i] subsets
    split(subset[i]->subset,subset[i]->child_count,subset[i+1]->subset,subset[i+1]->child_count);
    //4. Detach item from subset[i]
    detach_item(subset[i]->data,subset[i]->data_count, hold);
    //5.Insert detached item into data
    ordered_insert(data,data_count,hold);
    //6. Also insert detached item into subset[i+1]
    if(subset[i+1]->is_leaf()){
       subset[i+1]->insert(hold);
       subset[i+1]->next = subset[i]->next;
       subset[i]->next = subset[i+1];
    }
}
//PRE: Takes in entry
//POST: Works with remove to remove entry
template<class T>
void BPlusTree<T>::loose_remove(const T &entry){
    T temp = entry;
    T holder,smallest,next_smallest,junk;
    int index = first_ge(data,data_count, entry);
    bool found = (index < data_count && data[index] == entry);

    //1.If it is a leaf
    if(is_leaf()){
        //2. If its a leaf and found then simply delete
        if(found)
            delete_item(data,index,data_count,holder);
    }
    else{
        //3. Not a leaf but found
        if(found){
            //4. Get smallest item from subset[index+1] (its pointer)
            subset[index+1]->get_smallest(smallest);
            //5. Now go find that smallest item in the next subset and remove
            subset[index+1]->loose_remove(smallest);
            //6. Get the next smallest item in subset[index+1]
            if(data_count != 0){
                subset[index+1]->get_smallest(next_smallest);
                //7. Replace data[0] with the new smallest item;
                delete_item(data,index,data_count,junk);
                //8. Insert item into data;
                insert_item(data,index,data_count,next_smallest);
            }
            //9. if subsets data_count is 0 fix shortage
           if(subset[index+1]->data_count < MINIMUM){
              fix_shortage(index+1);
              if(contains(entry)){
                  subset[index+1]->get_smallest(smallest);
                  data[index] = smallest;
              }
           }
        }
        //10. Not a leaf and not found
         else{
             subset[index]->loose_remove(entry);
            if(subset[index]->data_count == MINIMUM -1)
                fix_shortage(index);
        }
    }
}
//PRE:Takes in an index
//POST: fixes shortage at index
template<class T>
void BPlusTree<T>::fix_shortage(int i){
    if(i+1 < child_count && subset[i+1]->data_count > MINIMUM ){
        transfer_left(i);
    }
    else if(i > 0 && subset[i-1]->data_count > MINIMUM){
        transfer_right(i);
    }
    else if(i+1 < child_count && subset[i+1]->data_count != 0){
        merge_with_next_subset(i);
    }
    else{
        merge_with_next_subset(i-1);
    }

}
//PRE: Takes in a entry
//POST: removes the biggest item. NOT USED
template<class T>
void BPlusTree<T>::remove_biggest(T &entry){
    int index = first_ge(data,data_count,entry);
    T temp;
    if(is_leaf()){
        entry = data[data_count -1];
        data_count--;
    }
    else{
        subset[child_count -1]->remove_biggest(entry);
       if(subset[child_count - 1]->data_count <= MINIMUM -1 )
         fix_shortage(child_count -1 );
    }

}
//PRE: Takes in a index
//POST: Rotates left at index
template<class T>
void BPlusTree<T>::rotate_left(int i){
    if(i < child_count && subset[i+1]->data_count > MINIMUM){
        T sub_temp;
        BPlusTree<T> *subset_temp;
        T data_temp = data[i];
        int hold = i+1;

        delete_item(subset[i+1]->data,0,subset[i+1]->data_count,sub_temp);
        ordered_insert(data,i,sub_temp);
        insert_item(subset[i-1]->data,0,subset[i-1]->data_count,data_temp);

        if(!subset[i]->is_leaf()){
            delete_item(subset[i]->subset,0,subset[i]->child_count,subset_temp);
            attach_item(subset[i-1]->subset,subset[i-1]->child_count,subset_temp);
        }
    }
}
//PRE: Takes in a index
//POST: Rotates right at index
template<class T>
void BPlusTree<T>::rotate_right(int i){

    if(i < child_count && subset[i-1]->data_count > MINIMUM){
        T sub_temp;
        T data_temp = data[i-1];
        int hold = i-1;
        BPlusTree<T> *subset_temp = NULL;
        int zero = 0;

        detach_item(subset[i-1]->data,subset[i-1]->data_count,sub_temp);
        ordered_insert(data,hold,sub_temp);
        insert_item(subset[i]->data,0,subset[i]->data_count,data_temp);

         if(!subset[i-1]->is_leaf()){
             detach_item(subset[i-1]->subset,subset[i-1]->child_count,subset_temp);
             insert_item(subset[i]->subset,0,subset[i]->child_count,subset_temp);
         }
    }
}
//PRE: Takes in a index
//POST: merges subset i with i+1
template<class T>
void BPlusTree<T>::merge_with_next_subset(int i){
        T temp;
        BPlusTree<T> *temp_ptr = NULL ;

        //1.If not a leaf do same merge as B tree
        if(!(subset[i]->is_leaf())){
            //1. remove data[i] from this object
            delete_item(data,i,data_count,temp);
            //2. append it to child[i]->data
            ordered_insert(subset[i]->data,subset[i]->data_count,temp);
            //3. Move all data items from subset[i+1]->data to subset[i]->data
             merge(subset[i]->data,subset[i]->data_count,subset[i+1]->data,subset[i+1]->data_count);
            //4. Move all subset pointers from subset[i+1]->subset to subset[i]->subset
             merge(subset[i]->subset,subset[i]->child_count,subset[i+1]->subset,subset[i+1]->child_count);
            //5. delete subset[i+1] (store in a temp ptr)
            delete_item(subset,i+1,child_count,temp_ptr);
           //6. delete temp ptr
        }
        else{
            //1. remove data[i] from this object
            delete_item(data,i,data_count,temp);
            //3. Move all data items from subset[i+1]->data to subset[i]->data
             merge(subset[i]->data,subset[i]->data_count,subset[i+1]->data,subset[i+1]->data_count);
            //4. Move all subset pointers from subset[i+1]->subset to subset[i]->subset
             merge(subset[i]->subset,subset[i]->child_count,subset[i+1]->subset,subset[i+1]->child_count);
            //5. delete subset[i+1] (store in a temp ptr)
            delete_item(subset,i+1,child_count,temp_ptr);
           //6. delete temp ptr

        }
        //7. Link the linkers
        if (subset[i]->is_leaf())
                subset[i]->next = temp_ptr->next;

        delete temp_ptr;
        temp_ptr = NULL;

}
//PRE:Takes in a entry
//POST: removes the entry from the tree
template<class T>
void BPlusTree<T>::remove(const T &entry){
    loose_remove(entry);
    if(data_count < MINIMUM && child_count != 0){
        BPlusTree<T> *temp_ptr = NULL;
        temp_ptr = subset[0];
        copy_array(data,temp_ptr->data,data_count,temp_ptr->data_count);
        copy_array(subset,temp_ptr->subset,child_count,temp_ptr->child_count);
        temp_ptr->child_count = 0;
       delete temp_ptr;

    }
}
//POST: clears treee
template<class T>
void BPlusTree<T>::clear_tree(){
    if(is_leaf()){
        data_count = 0;
    }
    for(int i = child_count-1; i >= 0; i--){
         subset[i]->clear_tree();
    }
    for(int i = child_count-1; i >= 0; i--){
         delete subset[i];
        subset[i] = NULL;
    }
    data_count = 0;
    child_count = 0;
}
//PRE: Takes in a btree object
//POST: creates pointer and calls other copy
template<class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T> &other){
    BPlusTree<T> *ptr = nullptr;
    copy_tree(other,ptr);
}
//PRE: Takes in a bplustree objext and pointer
//POST: copys tree
template<class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T> &other,BPlusTree<T>* &temp_ptr){
    //0. Clear current tree so its an empty tree when you copy
    this->clear_tree();

    //1.Copy array
    copy_array(data,other.data,data_count,other.data_count);
    child_count =  other.child_count;

    //2. Create new BPluss tree object and do recursion on it
    for(int i = other.child_count-1; i >= 0; i--){
        BPlusTree<T> *temp = new BPlusTree<T>;
        subset[i] = temp;
        subset[i]->copy_tree(*other.subset[i],temp_ptr);

    }
    //3. Copying the leafs links
    if(is_leaf()){
        this->next = temp_ptr;
        temp_ptr = this;
    }

}
//PRE:Takes in a entry
//POST: returns a boolean if entry is in tree
template<class T>
bool BPlusTree<T>::contains(const T &entry) const{
    int index;
    bool found;
    index = first_ge(data,data_count,entry);
    found = (index < data_count  && entry == data[index]);
    if(found){
        return true;
    }
    else{
        if(is_leaf()){
            return false;
        }
        else
           return subset[index]->contains(entry);
    }
}
//PRE: Takes in a entry
//POST: calls get existing or inserts
template<class T>
T &BPlusTree<T>::get(const T &entry){
    if(!contains(entry))
        insert(entry);
    return get_existing(entry);
}
//PRE:Takes in a entry
//POST: gets the entry
template<class T>
T &BPlusTree<T>::get_existing(const T &entry){
    int index;
    bool found = true;
    index = first_ge(data,data_count,entry);
    found = (index < data_count && entry == data[index]);
    //1. If leaf
    if(is_leaf()){
        //2. If leaf and found
        if(found)
            return data[index];
    }
    //2. Not a leaf
    else{
        //3. Not a leaf but found
        if(found)
            return subset[index+1]->get_existing(entry);
        //4. Not a leaf and not found
        else
            return subset[index]->get_existing(entry);
    }

}
//PRE: takes in a entry to be found
//POST:return a pointer to this key. NULL if not there.
template<class T>
T *BPlusTree<T>::find(const T &entry){
    int index;
    bool found = true;
    T *temp;
    index = first_ge(data,data_count,entry);
    found = (index < data_count && entry == data[index]);

    if(found){
        temp = &data[index];
        return temp;
    }
    else{
        if(is_leaf())
            return NULL;
        else
            return subset[index]->find(entry);
    }
}
//POST: Gets the size of the linked leafs
template<class T>
int BPlusTree<T>::size(){
    int count = 0;
    for(BPlusTree<T>::Iterator it = begin(); it != this->end(); it++){
        ++count;
    }
    return count;
}
//POST: returns a boolean if empty
template<class T>
bool BPlusTree<T>::empty() const{
    return (data_count == 0);
}
//PRE: takes in level and ostreamm outs
//POST: Prints tree
template<class T>
void BPlusTree<T>::print_tree(int level, ostream &outs) const{

      if(is_leaf())
          for(int i = data_count-1; i >= 0; i--)
              outs << setw(level*8) << "" << data[i] << endl;
      else{
         for(int i = child_count-1; i >= 0; i--){
             if(i != MAXIMUM && i != data_count)
                 outs << setw(level*8)<< "" << data[i] << endl;

               subset[i]->print_tree(level+1,outs);
         }
      }
}
//POST: returns true if tree is valid
template<typename T>
bool BPlusTree<T>::is_valid(){
    T smallest;
    bool valid;

    if(is_leaf())
        return true;
    if(data[data_count -1] > subset[child_count-1]->data[0])
        return false;
    for(int i = 0; i < data_count; i++){
        if(data[i] < subset[i]->data[0])
            return false;
        subset[i+1]->get_smallest(smallest);
        if(data[i] != smallest)
            return false;
    }
    for(int i = child_count-1; i >= 0; i--){
         valid = subset[i]->is_valid();
    }
    return valid;
}

//POST: returns smallest node
template<class T>
BPlusTree<T> *BPlusTree<T>::get_smallest_node(){
    if(!is_leaf())
        return subset[0]->get_smallest_node();
    else
        return this;
}
//POST: returns smallest
template<class T>
void BPlusTree<T>::get_smallest(T &entry){
    if(is_leaf())
        entry = data[0];
    else
        subset[0]->get_smallest(entry);
}
//POST: returns biggest
template<class T>
void BPlusTree<T>::get_biggest(T &entry){
    if(is_leaf())
        entry = data[data_count -1];
    else
        subset[child_count -1]->get_biggest(entry);
}
//PRE: takes in a index
//POST: transfers items tot the left of index
template<class T>
void BPlusTree<T>::transfer_left(int i){
    T junk;
    if(subset[i+1]->is_leaf()){
        rotate_left(i);
        delete_item(data,0,data_count,junk);
        ordered_insert(data,data_count,subset[i+1]->data[0]);
    }
    else
        rotate_left(i);
}
//PRE: takes in a index
//POST: transfers items right of index
template<class T>
void BPlusTree<T>::transfer_right(int i){
    T junk;
    if(subset[i]->is_leaf()){
        rotate_right(i);
        subset[i]->data[0] = data[i-1];
    }
    else
        rotate_right(i);

}
//POST: Starting point for iterator
template <typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::begin(){
    return Iterator(get_smallest_node());
}
//POST: Ending point for iterator
template <typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::end(){
    return Iterator(NULL);
}

#endif // BPLUSTREE_CLASS_H
