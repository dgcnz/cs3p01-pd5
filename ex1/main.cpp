#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <vector>

using namespace std;

const int N = 3;
vector<vector<double>> A;

void normaliza()
{
  double suma = 0.0, factor = 0.0;
#pragma omp parallel for reduction(+ \
                                   : suma)
  for (int i = 0; i < N; i++)
  {
    double suma2 = 0.0;
    for (int j = 0; j < N; j++)
    {
      suma2 += (A[i][j] * A[i][j]);
    }
    suma += suma2;
  }

  factor = 1.0 / sqrt(suma);
  printf("suma = %f, factor = %f \n", suma, factor);

#pragma omp parallel for
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      A[i][j] = factor * A[i][j];
    }
  }
}

void normaliza2()
{
  double suma = 0.0, factor = 0.0;

#pragma omp parallel
  {
#pragma omp for reduction(+ \
                          : suma)
    for (int i = 0; i < N; i++)
    {
      double suma2 = 0.0;
      for (int j = 0; j < N; j++)
      {
        suma2 += (A[i][j] * A[i][j]);
      }
      suma += suma2;
    }

#pragma omp single
    {
      factor = 1.0 / sqrt(suma);
      printf("suma = %f, factor = %f \n", suma, factor);
    }

#pragma omp for
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
      {
        A[i][j] = factor * A[i][j];
      }
    }
  }
}

int main(void)
{
  A.resize(N, vector<double>(N));

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      A[i][j] = i + j + 1;
      printf("%d %d %f \n", i, j, A[i][j]);
    }
  }

  normaliza2();

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      printf("%d %d %f \n", i, j, A[i][j]);
    }
  }

  return 0;
}
