
#include <iostream>
#include <thread>
#include <condition_variable>
#include <string>
#include <chrono>
#include "queue.h"

/*
#if __cplusplus < 201412
  #error Expecting C++17 standard
#endif
*/

using namespace std;

Queue<int> q(2);

void Write_f(int value)
{

  // cout << "Value to Write: "<< value << endl; 
  q.Push(value);
  cout << "Lits size:" << q.Count() << endl;


}

void Read_f()
{
  int value_r;
  
  value_r = q.Pop();

  cout << "Value Poped: "<< value_r << endl; 
  cout << "Lits size:" << q.Count() << endl;

}
void Read_timeout_f()
{
  int value_r;
  
  cout << "Popint value, watting 5 sec." << endl; 
  value_r = q.PoPWithtimeout(5000);

  cout << "Value Poped: "<< value_r << endl; 
  cout << "Lits size:" << q.Count() << endl;

}



int main() 
{

  // execution as requested by exercise script
  thread t_write_1(Write_f, 1);
  t_write_1.join();
    
  thread t_read_1(Read_f);
  t_read_1.join();
  
  thread t_write_2(Write_f, 2);
  t_write_2.join();
  thread t_write_3(Write_f, 3);
  t_write_3.join();
  thread t_write_4(Write_f, 4);
  t_write_4.join();

  thread t_read_2(Read_f);
  t_read_2.join();
  thread t_read_3(Read_f);
  t_read_3.join();

  thread t_read_4(Read_f);
  thread t_write_5(Write_f, 5);
  
  t_read_4.join();
  t_write_5.join();

  
  // thread t_read_timeout(Read_timeout_f);
  // t_read_timeout.join();


  return 0;

}




