#ifndef MYSTACK_H
#define MYSTACK_H
#include "../linked_list_functions/linkedlistfunctionsTemplated.h"
#include "assert.h"

// bool debugStack = false;

template <typename ITEM_TYPE>
class Stack{
public:
    class Iterator{
    public:
        friend class Stack; // give access to list to access _ptr

        Iterator(){_ptr = NULL; } //default ctor
        Iterator(node<ITEM_TYPE>* p): _ptr(p){} // point Iterator to where p is pointing to

        ITEM_TYPE& operator *(){ //dereference operator
            assert(_ptr && "attempted to dereference nullptr");
            return _ptr->_item; 
        }

        bool is_null(){return _ptr == NULL;} //true if _ptr is NULL

        friend bool operator !=(const Iterator& left, const Iterator& right)  //true if left != right
        {return left._ptr != right._ptr; }

        friend bool operator ==(const Iterator& left, const Iterator& right)  //true if left == right
        {return left._ptr == right._ptr; }


        Iterator& operator++(){ //member operator: ++it or ++it = new_value
            assert(_ptr != nullptr && "cannot iterate a NULL ptr");
            _ptr = _ptr->_next;
            return *this;
        }

        friend Iterator operator++(Iterator& it, int unused){ //friend operator: it++
            assert(it._ptr != nullptr && "cannot iterate a NULL ptr");
            Iterator hold;
            hold = it;
            it._ptr = it._ptr ->_next;
            // ++it;
            return hold;
        }

    private:
        node<ITEM_TYPE>* _ptr;    //pointer being encapsulated
    }; // end of Iterator class

    Stack(); // default CTOR
    Stack(const Stack<ITEM_TYPE>& copyMe); // copy ctor
    ~Stack(); // destructor
    Stack<ITEM_TYPE>& operator=(const Stack<ITEM_TYPE>& RHS); // assignment operator

    void push(ITEM_TYPE item); // push new node with value item
    ITEM_TYPE pop(); // returns value of _top

    ITEM_TYPE top(){ return _top->_item; } // returns item at top
    bool empty(){return _top == nullptr; } // true if _top is NULL, false otherwise

    Iterator begin() const { return Iterator(_top); } //Iterator to the head node
    Iterator end() const {return Iterator(); } //Iterator to NULL

    int size() const { return _size; }
    
    void print() const;

    template<typename T>
    friend ostream& operator<<(ostream& outs, const Stack<T>& printMe){
        printMe.print();
        return outs;
    }
private:
    node<ITEM_TYPE>* _top;
    int _size;
}; // end of Stack class

/*------------------------------------------------------------------*/
/*--------------------------OUT OF CLASSES--------------------------*/
/*------------------------------------------------------------------*/

template <typename T>
Stack<T>::Stack(){ // default CTOR
    _top = nullptr;
    _size = 0;
}

//-------------------------------BIG 3-------------------------------//
template <typename T>
Stack<T>::Stack(const Stack<T>& copyMe){ // copy CTOR
    _top = _copy_list<T>(copyMe._top); // returns the end of dest
    _size =  copyMe._size;
    // if(debugStack){
    //     cout << "STACK CONSTRUCTOR RAN..." << endl;
    // }
}

template <typename T>
Stack<T>::~Stack(){ // destructor
    _clear_list(_top);
    _top = nullptr;
    _size = 0;
    // if(debugStack){
    //     cout << "STACK DESTRUCTOR RAN..." << endl;
    // }
}

template<typename T>
Stack<T>& Stack<T>::operator =(const Stack<T>& RHS){ // assignment operator
    // if(debugStack){
    //     cout << "STACK ASSIGNMENT OPERATOR RAN..." << endl;
    // }

    if(this != &RHS){
        _clear_list<T>(_top);
        _top = _copy_list<T>(RHS._top);
        _size = RHS._size;
    }

    return *this;
}

//-----------------------------FUNCTIONS-----------------------------//
template <typename T>
void Stack<T>::print() const {
    node<T>* walker = _top;
    cout << "Head -> ";
    while(walker != nullptr){
        cout << "<-[" << (walker -> _item) << "]-> ";
        walker = walker -> _next;
    }
    cout << "|||" << endl;
}

template <typename T>
void Stack<T>::push(T item){ // push new node with value item
    _insert_head<T>(_top, item); // _top moves
    _size++;
}

template <typename T>
T Stack<T>::pop(){ // returns value of _top
    assert(_top && "cannot pop empty stack");
    T deleted = _delete_head<T>(_top); // _top moves
    _size--;
    return deleted;
}

#endif /* MYSTACK_H */
