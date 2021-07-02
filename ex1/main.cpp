#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <vector>

using namespace std;

const int N = 3;
vector<vector<double>> A;

void normaliza()
{
  printf("A[0][0] = %d \n", A[0][0]);
  int i, j;
  double suma = 0.0, suma2 = 0.0, factor;
#pragma omp parallel for private(i, suma2) reduction(+ \
                                                     : suma)
  for (i = 0; i < N; i++)
  {
#pragma omp parallel for private(j) reduction(+ \
                                              : suma2)
    for (j = 0; j < N; j++)
    {
      suma2 += (A[i][j] * A[i][j]);
      printf("i = %d, j= %d, threadId = %d, suma2 = %d a = %d \n",
             i, j, omp_get_thread_num(), suma2, A[i][j]);
    }
    suma += suma2;
  }

  printf("suma=%d\n", suma);
  factor = 1.0 / sqrt(suma);

#pragma omp parallel for
  for (i = 0; i < N; i++)
  {
#pragma omp parallel for
    for (j = 0; j < N; j++)
    {
      A[i][j] = factor * A[i][j];
    }
  }
}

int main(void)
{
  int i, j;
  A.resize(N, vector<double>(N));

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      A[i][j] = i + j;
    }
  }

  printf("N = %d, A[0][0] = %d \n", N, A[0][0]);
  normaliza();

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      printf("%d ", A[i][j]);
    }
    printf("\n");
  }

  return 0;
}
