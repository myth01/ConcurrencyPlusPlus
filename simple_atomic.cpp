#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <unistd.h>
#include <atomic>
using namespace std;


void square(int x, atomic<int> &accum) {
  cout << "Inside square thread " << x << endl;
  int val = 0;
  sleep(x*0.1);
  val += x;
  accum += val;
}

int main() {
  vector<thread> th_square;
  atomic<int> accum = 0;
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