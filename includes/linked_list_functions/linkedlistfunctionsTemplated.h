#ifndef LINKEDLISTFUNCTIONSTEMPLATED_H
#define LINKEDLISTFUNCTIONSTEMPLATED_H

#include "../node/node.h"
#include "assert.h"

/*------------------------------------------------------------------*/
/*---------------------------DECLARATIONS---------------------------*/
/*------------------------------------------------------------------*/

//Linked List General Functions:
template <typename T>
void _print_list(node<T>* head);

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head);

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head, T key);

template <typename T>
node<T>* _insert_head(node<T> *&head, T insert_this);

//insert after ptr: insert head if marker null
template <typename T>
node<T>* _insert_after(node<T>*& head, node<T> *after_this, T insert_this);

//insert before ptr: insert head if marker null
template <typename T>
node<T>* _insert_before(node<T>*& head,  node<T>* before_this, T insert_this);

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* prev_to_this);

//delete head, return item
template <typename T>
T _delete_head(node<T>*& head);

//delete
template<typename T>
void _delete_node(node<T>*& head, T delete_this);

//delete, return item
template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this);

//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head);

//duplicate the list...
template <typename T>
node<T>* _copy_list(node<T>* head);

//duplicate the list, return pointer to last node in dest... 
//     use this function in your queue big three 
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src);

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos);

/*------------------------------------------------------------------*/
/*----------------------------DEFINITIONS---------------------------*/
/*------------------------------------------------------------------*/

template <typename T>
void _print_list(node<T>* head){
    node<T>* walker = head;
    cout << "Head-> ";
    while(walker != nullptr){
        cout << "<-[" << walker->_item << "]-> ";
        walker = walker->_next;
    }
    cout << "|||" << endl;        
}

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head){

}

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head, T key){
    assert(head != nullptr && "cannot search an empty list");

    node<T>* walker = nullptr;

    for(walker = head; walker; walker = walker ->_next){ //goes through whole list
        if(walker->_item == key){ //checks object with key
            return walker; //returns the walker at the address where key has been found
        }
    }

    return walker;
}

template <typename T>
node<T>* _insert_head(node<T> *&head, T insert_this){ // returns the new node
    node<T>* newNode = new node<T>(insert_this, head);
    if(head != nullptr)
        head->_prev = newNode; // now second node's previous points to new node
    head = newNode; // headptr points to the new head
    return head;
}
 
//insert after ptr: insert head if marker null
template <typename T>
node<T>* _insert_after(node<T>*& head, node<T> *after_this, T insert_this){
    // assert(after_this != nullptr && (after_this != head) && "cannot insert after nullptr when head is not also nullptr");

    if(!head || !after_this) // headptr is null (list is empty)
        return _insert_head(head, insert_this);

    node<T>* newNode = new node<T>(insert_this, after_this->_next, after_this); // next points to node after after_this, previous is after_this
    after_this->_next = newNode; // current pos points to new node

    if(newNode->_next != nullptr) // node after after_this is NOT null
        (newNode->_next)->_prev = newNode;
    return newNode;
}

//insert before ptr: insert head if marker null
template <typename T>
node<T>* _insert_before(node<T>*& head,  node<T>* before_this, T insert_this){
    // assert((head != before_this) && (head == nullptr) && "headptr and ptr to adding do not match when head is null");

    if(head == nullptr || before_this == nullptr || head == before_this){
        return _insert_head(head, insert_this);
        // return head;
    }
    node<T>* newNode = new node<T>(insert_this, before_this, before_this->_prev); // next points to before_this, previous points node before to before_this
    newNode->_prev->_next = newNode; // previous to what was inserted points to new node
    before_this->_prev = newNode; // current pos prev points to new node
    return newNode;
}

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* prev_to_this){
    assert(prev_to_this != nullptr && "cannot check previous of nullptr");
    assert(prev_to_this->_prev != nullptr && "cannot find node that has a prev as null");
    return prev_to_this->_prev;
}

//delete head, return item
template <typename T>
T _delete_head(node<T>*& head){
    assert(head != nullptr && "cannot delete head pointing to NULL");

    T item = head->_item; // stores item being deleted
    node<T>* temp = head;
    if(head->_next != nullptr){
        head = head->_next;
        head->_prev = nullptr;
    }else{
        head = nullptr;
    }

    delete temp; // temp _next, _prev, _item
    return item;
}

template<typename T>
void _delete_node(node<T>*& head, T delete_this){
    if(head->_item == delete_this)
        _delete_head(head);

    if(head != nullptr && head->_next != nullptr){
        node<T>* deleting = _search_list(head, delete_this);
        _delete_node(head, deleting);
    }
}

//delete, return item
template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this){
    if(head == delete_this)
        return _delete_head(head);

    T item = delete_this->_item; // stores item being deleted
    node<T>* previous = delete_this->_prev; // points to node before what is being deleted
    node<T>* ahead = delete_this->_next; // points at the node after what is being deleted
    delete delete_this; // deletes mark

    previous->_next = ahead; // node before deleted node points to the ahead of deletion
    if(ahead != nullptr)
        ahead->_prev = previous; // node ahead of deletion prev points to the node before the deletion
    return item;
}

//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head){
    // assert(head != nullptr && "cannot delete clear an empty list");
    
    // while(head != nullptr){ // headptr keeps going "forward" while temp stores and deletes
    //     node<T>* temp = head; // stores
    //     head = head ->_next; // goes down headptr
    //     delete temp; // deletes where headptr was
    // }
    while(head != nullptr){
        _delete_head(head);
    }
}

//duplicate the list...
template <typename T>
node<T>* _copy_list(node<T>* head){
    // assert(head != nullptr && "cannot copy an empty list");
    if(head == nullptr)
        return nullptr;

    node<T>* dest = nullptr;
    node<T>* front = dest;
    dest = _copy_list(dest, head);
    return front;
}

//duplicate the list, return pointer to last node in dest... 
//     use this function in your queue big three 
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src){
    // assert(src != nullptr && "cannot copy an empty list");
    if(src == nullptr)
        return nullptr;

    _clear_list(dest);

    node<T>* src_walker = src;
    node<T>* dest_walker = dest;

    while(src_walker != nullptr){
        dest_walker = _insert_after(dest, dest_walker, src_walker->_item); // dest(head), inserting after dest_walker, inserting src's item
        src_walker = src_walker->_next;
        // dest_walker = dest_walker->_next;
    }
    return dest_walker; // returns pointer to last node of dest
}

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos){
    node<T>* walker = head;

    for(int i = 0; i <= pos; i++){
        if(i == pos)
            return walker->_item;
        walker = walker->_next;
    }
    return walker->_item;
}

#endif /* LINKEDLISTFUNCTIONSTEMPLATED_H */