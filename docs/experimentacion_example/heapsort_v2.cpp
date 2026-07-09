



#include <iostream>
#include <chrono>

using namespace std;




void heapify(int *arr, int N, int i)
{


    int largest = i;


    int l = 2 * i + 1;


    int r = 2 * i + 2;


    if (l < N && arr[l] > arr[largest])
        largest = l;



    if (r < N && arr[r] > arr[largest])
        largest = r;


    if (largest != i) {
        swap(arr[i], arr[largest]);



        heapify(arr, N, largest);
    }
}


void heapSort(int *arr, int N)
{


    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(arr, N, i);



    for (int i = N - 1; i > 0; i--) {


        swap(arr[0], arr[i]);


        heapify(arr, i, 0);
    }
}

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


  heapSort(valores, n);


  auto end = chrono::high_resolution_clock::now();


  double running_time = chrono::duration_cast<chrono::nanoseconds>(end -
								   start).count();

    running_time *= 1e-9;


    cout << argv[0] << ";" << n << ";" << running_time << endl;





    return 1;
}
