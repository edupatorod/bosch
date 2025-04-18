
#include <iostream>
#include <condition_variable>
#include <mutex>
#include <stdexcept>
#include <cstring>

#ifndef QUEUE_H
#define QUEUE_H

#define MAX_SIZE 64

using namespace std;

template <typename T_element>
struct list_element_t {  
  T_element element;
  struct list_element_t<T_element> *next_list_element;
  struct list_element_t<T_element> *prv_list_element;
};


template <typename T_element> class Queue {

  list_element_t<T_element> *first_list_element_ptr;
  list_element_t<T_element> *last_list_element_ptr;
  int list_size;
  int used_amount;
  
  mutex mtx;
  condition_variable cv;

  T_element Do_thePop();
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


template <typename T_element> void Queue<T_element>::Push(T_element element)
{
  list_element_t<T_element>* list_ptr_tmp;
  
  cout << "Doing Push..." << element << endl;

  list_ptr_tmp = new list_element_t<T_element>;
  memcpy(&list_ptr_tmp->element, &element, sizeof(element));
  list_ptr_tmp->next_list_element = nullptr;

  lock_guard<mutex> lock(mtx);
  if (last_list_element_ptr==nullptr)
  {
    last_list_element_ptr = list_ptr_tmp;
    first_list_element_ptr = last_list_element_ptr;
    first_list_element_ptr->prv_list_element = nullptr;
  }
  else
  {
    last_list_element_ptr->next_list_element = list_ptr_tmp;
    list_ptr_tmp->prv_list_element = last_list_element_ptr;
    last_list_element_ptr = list_ptr_tmp;
  }

  used_amount++;  
  if(used_amount>list_size)
  {
    used_amount--;
    first_list_element_ptr = first_list_element_ptr->next_list_element;
    first_list_element_ptr->prv_list_element = nullptr;
  }
  cv.notify_one();

}


template <typename T_element> T_element Queue<T_element>::Pop()
{
  cout << "Calling Pop()..." << endl;
  
  unique_lock<mutex> lock(mtx);
  cout << "Pop(): waitting for data..." << endl;  
  cv.wait(lock, [this]{return List_is_not_Empty();});
  cout << "Pop(): unlooked..." << endl;
  
  return Do_thePop();
}

template <typename T_element> T_element Queue<T_element>::PoPWithtimeout(int msec)
{

  cout << "Doing PopWithTimeout()..." << endl;

  unique_lock<mutex> lock(mtx);
  if (cv.wait_for(lock, chrono::milliseconds(msec), [this]{return List_is_not_Empty();}))
    return Do_thePop();
  else
    throw invalid_argument("Timeout...list is empty trying to pop");

}

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


template <typename T_element> int Queue<T_element>::Count()
{
  return (used_amount);
}


template <typename T_element> int Queue<T_element>::Size()
{
  return (list_size);
}

template <typename T_element> bool Queue<T_element>::List_is_not_Empty()
{
  return (used_amount>0);
}

  
#endif

  