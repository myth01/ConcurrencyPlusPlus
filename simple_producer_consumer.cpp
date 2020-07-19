#include <iostream>
#include <queue>
#include <thread>
#include <condition_variable>
#include <mutex>
using namespace std;

#define BUFFER_SIZE 10

int main() {
  queue<int> goods;
  mutex m;
  condition_variable cond_var;

  thread producer([&](){
    unique_lock<mutex> lock(m);
    while(true) {
      // Wait on the lock for signal from consumer 
      // when goods is full
      cond_var.wait(lock, [&](){
        return goods.size()!=BUFFER_SIZE-1;});
      
      goods.push(1);
      cout << "produce " << goods.size()<<endl;

      //signal consumer that goods is not empty
      m.unlock();
      cond_var.notify_all();
    }
  });

  thread consumer([&](){
    unique_lock<mutex> lock(m);
    while(true) {
      // Wait on the lock for signal from producer 
      // when goods is empty
      cond_var.wait(lock, [&](){
          return !goods.empty();});
      goods.pop();
      cout << "consume " << goods.size()<<endl;

      //signal producer that goods is not full
      m.unlock();
      cond_var.notify_all();
    }
  });
  
  producer.join();
  consumer.join();
  return 0;
}
