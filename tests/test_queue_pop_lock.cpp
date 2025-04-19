
#include <iostream>
#include <thread>
#include <condition_variable>
#include <string>
#include <chrono>
#include "../src/queue.h"


using namespace std;

Queue<int> q(2);
int value_poped;

void Write_f(int value)
{

  cout << "Value to Write: "<< value << endl; 
  q.Push(value);
  cout << "Lits size:" << q.Count() << endl;


}

void Read_f()
{
  int value_r;
  
  cout << "Doing Pop: " << endl; 
  value_r = q.Pop();
  value_poped = value_r;

  cout << "Value Poped: "<< value_r << endl; 
  cout << "Lits size:" << q.Count() << endl;

}



int main() 
{
  value_poped=0;

  thread t_read_1(Read_f);

  if (value_poped!=0)
    throw invalid_argument("1:Invalid value poded!!\n");

  thread t_write_1(Write_f, 5);
  t_write_1.join();
  t_read_1.join();

  if (value_poped!=5)
    throw invalid_argument("2:Invalid value poded!!\n");


  return 0;

}




