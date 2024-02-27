#ifndef MYQUEUE_H
#define MYQUEUE_H
#include "../linked_list_functions/linkedlistfunctionsTemplated.h"
#include "assert.h"

// bool debugQueue = true;

template <typename ITEM_TYPE>
class Queue
{
public:
    class Iterator{
    public:
        friend class Queue; //give access to list to access _ptr
        Iterator(){_ptr = NULL;} //default ctor

        Iterator(node<ITEM_TYPE>* p): _ptr(p){}  //Point Iterator to where p is pointing to
        
        ITEM_TYPE& operator *(){ //dereference operator
            assert(_ptr && "attempted to dereference nullptr");
            return _ptr->_item;
        }

        bool is_null(){ return _ptr == NULL; } //true if _ptr is NULL

        friend bool operator !=(const Iterator& left, const Iterator& right)  //true if left != right
        {return left._ptr != right._ptr; }

        friend bool operator ==(const Iterator& left, const Iterator& right)  //true if left == right
        {return left._ptr == right._ptr; }


        Iterator& operator ++(){ //member operator: ++it 
            assert(_ptr && "cannot iterate a NULL ptr");
            _ptr = _ptr->_next;
            return *this;
        }

        Iterator& operator --(){
            assert(_ptr && "cannot deiterate a NULL ptr");
            _ptr = _ptr->_prev;
            return *this;
        }

        friend Iterator operator++(Iterator& it, int unused){ //friend operator: it++
            assert(it._ptr != nullptr && "cannot iterate a NULL ptr");
            Iterator hold;
            hold = it;
            it._ptr = it._ptr->_next;
            return it._ptr;
        }

        friend Iterator operator --(Iterator& it, int unused){
            assert(it._ptr != nullptr && "cannot deiterate a NULL ptr");
            Iterator hold;
            hold = it;
            it._ptr = it._ptr->_prev;
            return hold;  
        }

    private:
        node<ITEM_TYPE>* _ptr; //pointer being encapsulated
    }; // end of Iterator class

    Queue();

    Queue(const Queue<ITEM_TYPE>& copyMe);
    ~Queue();
    Queue& operator=(const Queue<ITEM_TYPE>& RHS);

    ITEM_TYPE front(){return _front->_item; }
    ITEM_TYPE back(){return _rear->_item; }

    void push(ITEM_TYPE item);
    ITEM_TYPE pop();

    bool empty(){
        if(_front == nullptr){
            assert(_rear == nullptr && "if _top is null, rear should also be null");
            return true;
        }
        return false;
    }

    Iterator begin() const {return Iterator(_front); } //Iterator to the head node
    Iterator end() const {return Iterator(); } //Iterator to NULL
    void print_pointers() const;

    int size() const { return _size; }

    template <typename T>
    friend ostream& operator << (ostream& outs, const Queue<T>& printMe){
        printMe.print_pointers();
        return outs;
    }

private:
    node<ITEM_TYPE>* _front;
    node<ITEM_TYPE>* _rear;
    int _size;
}; // end of Queue class

/*------------------------------------------------------------------*/
/*--------------------------OUT OF CLASSES--------------------------*/
/*------------------------------------------------------------------*/
template <typename T>
Queue<T>::Queue(){
    _front = nullptr;
    _rear = nullptr;
    _size = 0;
}

//-------------------------------BIG 3-------------------------------//

template <typename T>
Queue<T>::Queue(const Queue<T>& copyMe){
    _front = _copy_list<T>(copyMe._front); // returns the headptr of lsit
    _rear = _copy_list<T>(_front, copyMe._front); // returns pointer to the last node of dest
    _size = copyMe._size;
    // if(debugQueue){
    //     cout << "QUEUE COPY CONSTRUCTOR RAN..." << endl;
    // }
}

template <typename T>
Queue<T>::~Queue(){
    _clear_list<T>(_front); // _front becomes null
    _front = nullptr;
    _rear = nullptr;
    _size = 0;
    // if(debugQueue){
    //     cout << "QUEUE DESTRUCTOR RAN..." << endl;
    // }
}

template <typename T>
Queue<T>& Queue<T>::operator =(const Queue<T>& RHS){
    // if(debugQueue){
    //     cout << "QUEUE ASSIGNMENT OPERATOR RAN..." << endl;
    // }

    if(this != &RHS){
        _clear_list<T>(_front);  
        _front = _copy_list<T>(RHS._front);
        _rear = _copy_list<T>(_front, RHS._front);
        _size = RHS._size;
    }

    return *this;
}

//-----------------------------FUNCTIONS-----------------------------//
template <typename T>
void Queue<T>::print_pointers() const {
    node<T>* walker = _front;
    cout << "Head -> ";
    while(walker){
        cout << "<-[" << (walker -> _item) << "]-> ";
        walker = walker -> _next;
    }
    cout << "|||" << endl;
}

template <typename T>
void Queue<T>::push(T item){
    node<T>* inserted = nullptr;
    if(empty()) // checks if front and rear match at nullptr
        inserted = _insert_head<T>(_front, item);
    else
        inserted = _insert_after<T>(_front, _rear, item);

    // node<T>* inserted = _insert_after(_front, _rear, item); // checks if the list is empty
    _rear = inserted; // back of queue is what was just added
    _size++;
}

template <typename T>
T Queue<T>::pop(){
    assert(_front != nullptr && "cannot pop when _front is NULL");
    // assert(((_size != 0) && !_front) && "size cannot be 0 while _front is not NULL");
    T deleted =  _delete_head<T>(_front);
    if(_front == nullptr) // just popped last item, list is now empty (size == 0)
        _rear = nullptr;
    if(_front == _rear)
        _rear = nullptr;

    _size--;
    return deleted;
}

#endif /* MYQUEUE_H */
