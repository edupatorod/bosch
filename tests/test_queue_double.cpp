
#include <iostream>
#include <thread>
#include <condition_variable>
#include <string>
#include <chrono>
#include "../src/queue.h"

/*
#if __cplusplus < 201412
  #error Expecting C++17 standard
#endif
*/

using namespace std;

Queue<double> q(2);
double value_poped;

void Write_f(double value)
{

  cout << "Value to Write: "<< value << endl; 
  q.Push(value);
  cout << "Lits size:" << q.Count() << endl;


}

void Read_f()
{
  double value_r;
  
  cout << "Doing Pop: " << endl; 
  value_r = q.Pop();
  value_poped = value_r;

  cout << "Value Poped: "<< value_r << endl; 
  cout << "Lits size:" << q.Count() << endl;

}



int main() 
{
  value_poped = 0.0;

  thread t_write_1(Write_f, 1.4);
  t_write_1.join();

  thread t_read_1(Read_f);
  t_read_1.join();
  
  if (value_poped < 1.4)
    throw invalid_argument("Invalid value poded!!\n");


  return 0;

}




