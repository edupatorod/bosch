
#include <iostream>
#include <thread>
#include <condition_variable>
#include <string>
#include <chrono>
#include <bits/stdc++.h>
#include "../src/queue.h"


using namespace std;

Queue<int> q(2);
int value_poped;

void Read_timeout_f()
{
  int value_r;
  
  cout << "Popint value, watting 5 sec." << endl; 
  try
  {
    value_r = q.PoPWithtimeout(5000);
  }
  catch (invalid_argument const& e)
  {
    return ;
  }
  value_poped = value_r;

  cout << "Value Poped: "<< value_r << endl; 
  cout << "Lits size:" << q.Count() << endl;

}



int main() 
{
  value_poped=0;

  thread t_read_timeout(Read_timeout_f);
  t_read_timeout.join();

  if (value_poped!=0)
    throw invalid_argument("Invalid value poded!!\n");


  return 0;

}




