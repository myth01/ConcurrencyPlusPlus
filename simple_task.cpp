#include <iostream>
#include <vector>
#include <future>
using namespace std;


int sum(int x) {
  cout << "Inside the task " << x << endl;
  return x;
}


int main() {
  vector<future<int>> sum_tasks;
  int accum = 0;
  int N = 30;
  for (int  i =1; i<=N; i++) {
    sum_tasks.push_back( async(&sum, i));
  }
  for (int  i =0; i<N; i++) {
    cout << "Get the future value " << i << endl;
    accum += sum_tasks[i].get();
  }
  cout << "accum " << accum << endl;
  return 0;
}