#include <iostream>
#include <math.h>
#include <ctime>
using namespace std;

//Kernel function - a function that GPU can Run
//initialized using the __global__ keyword
__global__
void add(int N, float *x, float *y)
{
  for(int i = 0; i < N; i++)
  {
    y[i] = x[i] + y[i];
  }
}

int main(void)
{
  clock_t begin_time = clock(); //set begin time

  int N = 1<<20; // 1 Million elements

  float *x, float *y;

  // Allocate Unified Memory – accessible from CPU or GPU
  // Uses unified memory accessible from CPU and GPU
  cudaMallocManaged(&x, N*sizeof(float));
  cudaMallocManaged(&y, N*sizeof(float));

  //initialize these arrays with values
  for(int i = 0; i < N; i++)
  {
    x[i] = 1.0f;
    y[i] = 2.0f;
  }

  // Run kernel on 1M elements on the GPU
  // Launched 1 GPU thread
  add<<<1, 1>>>(N, x, y);


  // Wait for GPU to finish before accessing on host
  // needs to be done as CPU does not wait for GPU
  // processing to be complete

  cudaDeviceSynchronize();

  //Free memory
  cudaFree(x);
  cudaFree(y);

  clock_t end_time = clock();
  float diff ((float)end_time - (float)begin_time);
  float seconds = diff/CLOCKS_PER_SEC;
  cout << "time taken" <<endl;
  cout << end_time;
  cout << seconds << endl;
  return 0;

}
