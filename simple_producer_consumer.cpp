#include <iostream>
#include <queue>
#include <thread>
#include <condition_variable>
#include <mutex>
using namespace std;

#define BUFFER_SIZE 10

int main() {
  queue<int> goods;
  int c = 0;
  mutex m;
  condition_variable cond_var;

  thread producer([&](){
    unique_lock<mutex> lock(m);
    while(true) {
      //wait for signal from consumer
      cond_var.wait(lock, [&](){
        return c!=BUFFER_SIZE-1;});
      
      goods.push(1);
      c++;
      cout << "produce " << c<<endl;
      //signal consumer
      m.unlock();
      cond_var.notify_all();
      m.unlock();
    }
  });

  thread consumer([&](){
    unique_lock<mutex> lock(m);
    while(true) {
      if (c==0) {
        //wait for signal from producer
      }
      cond_var.wait(lock, [&](){
          return c!=0;});
      goods.pop();
      c--;
      cout << "consume " << c<<endl;
      //signal producer
      m.unlock();
      cond_var.notify_all();
    }
  });
  
  producer.join();
  consumer.join();
  return 0;
}
