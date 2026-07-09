

#include <iostream>
#include <chrono>

#include "priorityQueue.h"

using namespace std;

int main(int argc, char** argv) {

  if(argc < 2) {
    cerr << "Usage: " << argv[0] << " <cantidad de elementos>" << endl;
    exit(1);
  }
  int n = atoi(argv[1]);


  int *valores = new int[n];
  for(int i=0; i < n; i++)
    valores[i] = rand() % 1000;







  auto start = chrono::high_resolution_clock::now();




  priorityQueue pq;
  for(int i=0; i < n; i++)
    pq.insert(valores[i]);


  for(int i=0; i < n; i++)
    valores[i] = pq.extractPriority();


  auto end = chrono::high_resolution_clock::now();


  double running_time = chrono::duration_cast<chrono::nanoseconds>(end -
								   start).count();

    running_time *= 1e-9;


    cout << argv[0] << ";" << n << ";" << running_time << endl;





  return 0;
}
