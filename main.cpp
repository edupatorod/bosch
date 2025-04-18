
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

Queue<int> q(3);

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
  int i;

  // thread t_read_1(Read_f);
  // thread t_read_2(Read_f);
  // thread t_read_3(Read_f);

  /*
  thread t_write_1(Write_f, 20);
  this_thread::sleep_for(chrono::milliseconds(1000));

  thread t_write_2(Write_f, 21);
  this_thread::sleep_for(chrono::milliseconds(1000));

  thread t_write_3(Write_f, 22);
  this_thread::sleep_for(chrono::milliseconds(1000));

  thread t_write_4(Write_f, 23);
  this_thread::sleep_for(chrono::milliseconds(1000));

  thread t_read_1(Read_f);
  this_thread::sleep_for(chrono::milliseconds(1000));
  thread t_read_2(Read_f);
  this_thread::sleep_for(chrono::milliseconds(1000));
  thread t_read_3(Read_f);

  thread t_read_3(Read_f);
  */
  thread t_read_timeout(Read_timeout_f);


  /*
  t_read_1.join();
  t_read_2.join();
  t_read_3.join();
  t_write_1.join();
  t_write_2.join();
  t_write_3.join();
  t_write_4.join();
  */
  t_read_timeout.join();


  return 0;

}




