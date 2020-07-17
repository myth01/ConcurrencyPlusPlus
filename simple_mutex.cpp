#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <unistd.h>
#include <mutex>
using namespace std;

mutex accum_mutex;

void square(int x, int &accum) {
  cout << "Inside square thread " << x << endl;
  int val = 0;
  sleep(x*0.1);
  val += x;
  accum_mutex.lock();
  accum += val;
  accum_mutex.unlock();
}

int main() {
  vector<thread> th_square;
  int accum = 0;
  int N = 30;
  for (int  i =1; i<=N; i++) {
    th_square.push_back(thread (&square, i, ref(accum)));
  }
  for (int  i =0; i<N; i++) {
    cout << "Joining square thread " << i << endl;
    th_square[i].join();
  }
  cout << "accum " << accum << endl;
  return 0;
}