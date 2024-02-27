#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include "../../includes/airport/simulation.h"
#include "../../includes/queue/MyQueue.h"
#include "../../includes/stack/MyStack.h"

using namespace std;

/*-------------------  LINKED LIST ---------------------*/
bool test_stub(bool debug = false){
  if (debug){
    cout << "testB:: test-sub() entering test_sub" << endl;
  }
  return true;
}

bool test_insert_head(bool debug = false){
  if(debug){
    cout << "-----------------------------------------------------------" << endl;
    cout << "LINKED_LIST_FUNCTIONS: test_insert_head()" << endl;
      node<int>* headptr = nullptr;
      for(int i = 0; i < 5; i++){
        _insert_head<int>(headptr, i + 1);
      }
      _print_list<int>(headptr);
  }
  cout << endl;
  return true;
}

bool test_search_list(bool debug = false){
  if(debug){
    cout << "-----------------------------------------------------------" << endl;
    cout << "LINKED_LIST_FUNCTIONS: test_search_list()" << endl;

      node<int>* headptr = nullptr;
      for(int i = 0; i < 5; i++){
        _insert_head<int>(headptr, i + 1);
      }
      _print_list<int>(headptr);
  
    for(int i = 1; i <= 5; i++){
      cout << "searching for " << i << "..." << endl;
      cout << "\tfound: " << *(_search_list(headptr, i)) << endl;
    }

  }
  cout << endl;
  return true;
}

bool test_insert_after(bool debug = false){
  if(debug){
    cout << "-----------------------------------------------------------" << endl;
    cout << "LINKED_LIST_FUNCTIONS: test_insert_after()" << endl;

      node<int>* headptr = nullptr;
      for(int i = 0; i < 5; i++){
        _insert_head<int>(headptr, i + 1);
      }
      _print_list<int>(headptr);

      node<int>* walker = headptr;
      for(int i = 1; i <= 5; i++){
        cout << "\ninserting " << i * 10 << " after " << *walker << endl;
        _insert_after(headptr, walker, i * 10);
        _print_list(headptr);
        walker = walker->_next->_next;
      }

      _clear_list(headptr);
      cout << "\ntesting insert_after() on an empty list..." << endl;
      _insert_after(headptr, headptr, 99);
      _print_list(headptr);
  }
  cout << endl;
  return true;
}

bool test_insert_before(bool debug = false){
  if(debug){
    cout << "-----------------------------------------------------------" << endl;
    cout << "LINKED_LIST_FUNCTIONS: test_insert_before()" << endl;

      node<int>* headptr = nullptr;
      for(int i = 0; i < 5; i++){
        _insert_head<int>(headptr, i + 1);
      }
      _print_list<int>(headptr);

      node<int>* walker = headptr;
      for(int i = 1; i <= 5; i++){
        cout << "\ninserting " << i * 10 << " before " << *walker << endl;
        _insert_before(headptr, walker, i * 10);
        _print_list(headptr);
        walker = walker->_next;
      }
  }
  cout << endl;
  return true;
}

bool test_delete_node(bool debug = false){
  if(debug){
    cout << "-----------------------------------------------------------" << endl;
    cout << "LINKED_LIST_FUNCTIONS: test_delete_node()" << endl;

      node<int>* headptr = nullptr;
      for(int i = 0; i < 10; i++){
        _insert_head<int>(headptr, i + 1);
      }
      _print_list<int>(headptr);
      cout << endl;

      node<int>* walker = headptr;
      for(int i = 10; i >= 3; i--){
        cout << "deleting " << i << endl;
        _delete_node(headptr, walker);
        _print_list(headptr);
        cout << endl;
        walker = headptr;
      }

      cout << "deleting 1" << endl;
      _delete_node(headptr, 1);
      _print_list(headptr);
      cout << endl;

      cout << "deleting last element" << endl;
      _delete_node(headptr, 2);
      _print_list(headptr);
      cout << endl;
  }
  cout << endl;
  return true;
}

bool test_clear_list(bool debug = false){
  if(debug){
    cout << "-----------------------------------------------------------" << endl;
    cout << "LINKED_LIST_FUNCTIONS: test_clear_list()" << endl;

      node<int>* headptr = nullptr;
      for(int i = 0; i < 10; i++){
        _insert_head<int>(headptr, i + 1);
      }
      _print_list<int>(headptr);
      cout << endl;

      cout << "clearing list..." << endl;
      _clear_list(headptr);
      _print_list(headptr);
  }
  cout << endl;
  return true;
}

bool test_at(bool debug = false){
  if(debug){
    cout << "-----------------------------------------------------------" << endl;
    cout << "LINKED_LIST_FUNCTIONS: test_at()" << endl;

      node<int>* headptr = nullptr;
      for(int i = 0; i < 10; i++){
        _insert_head<int>(headptr, i + 1);
      }
      _print_list<int>(headptr);
      cout << endl;

      cout << "finding first item" << endl;
      cout << "\titem at 0 is... " << _at(headptr, 0) << endl;

      cout << "finding index 4" << endl;
      cout << "\titem at 4 is... " << _at(headptr, 4) << endl;

      cout << "finding last index" << endl;
      cout << "\titem at 9 is... " << _at(headptr, 9) << endl;

  }
  cout << endl;
  return true;
}

/*------------------------ STACK -------------------------*/
bool test_stack_push(bool debug = false){
  if(debug){
    cout << "-----------------------------------------------------------" << endl;
    cout << "STACK: test_stack_push()" << endl;

    Stack<int> s;
    for(int i = 1; i <= 5; i++){
      s.push(i);
      cout << "stack: " << s << endl;
    }
  }
  cout << endl;
  return true;
}

bool test_stack_iterator(bool debug = false){
  if(debug){
    cout << "-----------------------------------------------------------" << endl;
    cout << "STACK: test_stack_iterator()" << endl;

    Stack<int> s;
    for(int i = 1; i <= 5; i++){
      s.push(i);
      cout << "stack: " << s << endl;
    }

    Stack<int>::Iterator it = s.begin();
    cout << "it was at " << *it << endl;
    it++;
    cout << "iterated using post-fix..." << endl;
    cout << "\tit is now " << *it << endl;

    cout << "\nit was at " << *it << endl;
    ++it;
    cout << "iterated using pre-fix..." << endl;
    cout << "\tit is now " << *it << endl;
  }
  cout << endl;
  return true;
}

/*------------------------ QUEUE -------------------------*/
bool test_queue_push(bool debug = false){
  if(debug){
    cout << "-----------------------------------------------------------" << endl;
    cout << "QUEUE: test_queue_push()" << endl;

    Queue<int> q;
    for(int i = 1; i <= 5; i++){
      q.push(i);
      cout << "queue: " << q << endl;
    }

    Queue<int> q2;
    cout << "\nmade an empty queue..." << endl;
    q2.push(88);
    cout << "pushed 88 into the queue" << endl;
    q2.print_pointers();
  }
  cout << endl;
  return true;
}

bool test_queue_pop(bool debug = false){
  if(debug){
    cout << "-----------------------------------------------------------" << endl;
    cout << "QUEUE: test_queue_pop()" << endl;

    Queue<int> q;
    for(int i = 1; i <= 5; i++){
      q.push(i);
      cout << "queue: " << q << endl;
    }

    
  
  }
  cout << endl;
  return true;
}

bool test_queue_iterator(bool debug = false){
  if(debug){
    cout << "-----------------------------------------------------------" << endl;
    cout << "QUEUE: test_queue_iterator()" << endl;

    Queue<int> q;
    for(int i = 1; i <= 5; i++){
      q.push(i);
      cout << "queue: " << q << endl;
    }

    Queue<int>::Iterator it = q.begin();
    cout << "it was at " << *it << endl;
    it++;
    cout << "iterated using post-fix...(friend operator)" << endl;
    cout << "\tit is now " << *it << endl;

    cout << "\nit was at " << *it << endl;
    ++it;
    cout << "iterated using pre-fix...(member operator)" << endl;
    cout << "\tit is now " << *it << endl;

    for(it; it != q.end(); it++){
      cout << "it: " << *it << endl;
    }

    // it--;
    // cout << "deiterated using post-fix...(friend operator)" << endl;
    // cout << "\tit is now " << *it << endl;

    // cout << "\nit was at " << *it << endl;
    // --it;
    // cout << "deiterated using pre-fix...(member operator)" << endl;
    // cout << "\tit is now " << *it << endl;

    // cout << "GOING BACKWARDS" << endl;
    // for(it; it != q.end(); --it){
    //   cout << "it: " << *it << endl;
    // }
  }
  cout << endl;
  return true;
}

/*---------------------  LINKED LIST ---------------------*/
TEST(TEST_STUB, TestStub) {
  EXPECT_EQ(1, test_stub(false));
}

TEST(TEST_INSERT_HEAD, TestInsertHead){
  EXPECT_EQ(1, test_insert_head(true));
}

TEST(TEST_SEARCH_LIST, TestSearchList){
  EXPECT_EQ(1, test_search_list(true));
}

TEST(TEST_INSERT_AFTER, TestInsertAfter){
  EXPECT_EQ(1, test_insert_after(true));
}

TEST(TEST_INSERT_BEFORE, TestInsertBefore){
  EXPECT_EQ(1, test_insert_before(true));
}

TEST(TEST_DELETE_NODE, TestDeleteNode){
  EXPECT_EQ(1, test_delete_node(true));
}

TEST(TEST_CLEAR_LIST, TestClearList){
  EXPECT_EQ(1, test_clear_list(true)); 
}

TEST(TEST_AT, TestAt){
  EXPECT_EQ(1, test_at(true));
}

/*------------------------ STACK -------------------------*/
TEST(TEST_STACK_PUSH, TestStackPush){
  EXPECT_EQ(1, test_stack_push(true));
}

TEST(TEST_STACK_ITERATOR, TestStackIterator){
  EXPECT_EQ(1, test_stack_iterator(true));
}

/*------------------------ QUEUE -------------------------*/
TEST(TEST_QUEUE_PUSH, TestQueuePush){
  EXPECT_EQ(1, test_queue_push(true));
}

TEST(TEST_QUEUE_POP, TestQueuePop){
  EXPECT_EQ(1, test_queue_pop(true));
}

TEST(TEST_QUEUE_ITERATOR, TestQueueIterator){
  EXPECT_EQ(1, test_queue_iterator(true));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

