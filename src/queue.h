
#include <iostream>
#include <condition_variable>
#include <mutex>
#include <stdexcept>
#include <cstring>

#ifndef QUEUE_H
#define QUEUE_H

/**
 * @brief 
  Queue implementation as a bi-directional linked list
  pointers:
  - first list element
  - last list element

  list element: 
  - pointer to next list element
  - pointer to previues list element

*/
#define MAX_SIZE 64 // can be defined any max value to avoid over memonry usage

using namespace std;

/**
 * @brief 
  List element
 * 
 * @tparam T_element 
 */
template <typename T_element>
struct list_element_t {  
  T_element element;
  struct list_element_t<T_element> *next_list_element;
  struct list_element_t<T_element> *prv_list_element;
};


/**
 * @brief 
  Class to manage the list
  List elements are created dynamically as requested by users until max list elements reached.
  List element are desctroyed as user pop them out saving memory.

 * 
 * @tparam T_element 
 */
template <typename T_element> class Queue {

  list_element_t<T_element> *first_list_element_ptr;
  list_element_t<T_element> *last_list_element_ptr;
  int list_size;
  int used_amount;
  
  mutex mtx;
  condition_variable cv;

  T_element Do_thePop(); // atomic pop

  bool List_is_not_Empty();

  public:
    Queue(int size);
    ~Queue();
    void Push(T_element element);
    T_element Pop();
    T_element PoPWithtimeout(int msec);
    int Count();
    int Size();

};


/** 

*/
template <typename T_element> Queue<T_element>::Queue(int size)
{
  
  // check max size for list
  if (size > MAX_SIZE)
    throw invalid_argument("List size too big");
  
  first_list_element_ptr = nullptr;
  last_list_element_ptr = nullptr;

  list_size = size;
  used_amount = 0;
}

template <typename T_element> Queue<T_element>::~Queue()
{
  
}

/**
 * @brief 
  Using condition_variable + mutex to avoid race condition and thread sync

 * 
 * @tparam T_element 
 * @param element 
 */
template <typename T_element> void Queue<T_element>::Push(T_element element)
{
  list_element_t<T_element>* list_ptr_tmp;
  
  // cout << "Doing Push..." << element << endl;

  list_ptr_tmp = new list_element_t<T_element>;
  memcpy(&list_ptr_tmp->element, &element, sizeof(element));
  list_ptr_tmp->next_list_element = nullptr;

  lock_guard<mutex> lock(mtx);
  // list is empty
  if (last_list_element_ptr==nullptr)
  {
    last_list_element_ptr = list_ptr_tmp;
    first_list_element_ptr = last_list_element_ptr;
    first_list_element_ptr->prv_list_element = nullptr;
  }
  else // list is not empty
  {
    last_list_element_ptr->next_list_element = list_ptr_tmp;
    list_ptr_tmp->prv_list_element = last_list_element_ptr;
    last_list_element_ptr = list_ptr_tmp;
  }

  used_amount++;  
  // here we remove the first element if we reach the max list size.
  if(used_amount>list_size) 
  {
    used_amount--;
    first_list_element_ptr = first_list_element_ptr->next_list_element;
    first_list_element_ptr->prv_list_element = nullptr;
  }
  cv.notify_one();

}

/**
 * @brief 
  Using condition_variable + mutex to avoid race condition and thread sync

 * 
 * @tparam T_element 
 * @return T_element 
 */
template <typename T_element> T_element Queue<T_element>::Pop()
{
  // cout << "Calling Pop()..." << endl;
  
  unique_lock<mutex> lock(mtx);
  cout << "Pop(): waitting for data..." << endl;  
  // lock here forever until list is not empty
  cv.wait(lock, [this]{return List_is_not_Empty();});
  cout << "Pop(): unlooked..." << endl;
  
  return Do_thePop();
}

/**
 * @brief 
  Function to to the pop and with timeout.
  Throw Exception aftertimeout reached.
 * 
 * @tparam T_element 
 * @param msec 
 * @return T_element 
 */

template <typename T_element> T_element Queue<T_element>::PoPWithtimeout(int msec)
{

  // cout << "Doing PopWithTimeout()..." << endl;

  unique_lock<mutex> lock(mtx);
  // lock here until timeout "msec"
  if (cv.wait_for(lock, chrono::milliseconds(msec), [this]{return List_is_not_Empty();}))
    return Do_thePop();
  else
    throw invalid_argument("Timeout...list is empty trying to pop");
  

}

/**
 * @brief 
  function to remove the first element from list.
  Used by both normal Pop and PopWithTiemout

 * 
 * @tparam T_element 
 * @return T_element 
 */
template <typename T_element> T_element Queue<T_element>::Do_thePop()
{

  T_element element;

  memcpy(&element, &first_list_element_ptr->element, sizeof(first_list_element_ptr->element));
  if(first_list_element_ptr != last_list_element_ptr)
  {  
    first_list_element_ptr = first_list_element_ptr->next_list_element;
    delete(first_list_element_ptr->prv_list_element);
  }    
  else
  {
    delete(first_list_element_ptr);
    first_list_element_ptr = nullptr;
    last_list_element_ptr = nullptr;
  }
  used_amount--;

  return element;
}

/**
 * @brief 
  Return number the list size.
 * 
 * @tparam T_element 
 * @return int 
 */
template <typename T_element> int Queue<T_element>::Count()
{
  return (used_amount);
}


/**
 * @brief 
 Return MAX list size allowed.
 
 * 
 * @tparam T_element 
 * @return int 
 */
template <typename T_element> int Queue<T_element>::Size()
{
  return (list_size);
}

/**
 * @brief 
 Funciton to check When list is not empty.
 Return true when list has at least one element.

 * 
 * @tparam T_element 
 * @return true 
 * @return false 
 */
template <typename T_element> bool Queue<T_element>::List_is_not_Empty()
{
  return (used_amount>0);
}

  
#endif

  