#include <algorithm>
#include <iostream>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

int separate(vector<int> &x, int l, int r)
{
    int pivot = x[l], last = l;
    swap(x[l], x[r]);
    for (int i = l; i < r; i++)
    {
        if (x[i] <= pivot)
        {
            swap(x[last], x[i]);
            last += 1;
        }
    }
    swap(x[last], x[r]);
    return last;
}

void qs_util(vector<int> &a, int l, int r)
{
    if (l < r)
    {
        int pivot = separate(a, l, r);
#pragma omp task default(none) shared(a) firstprivate(l, pivot)
        qs_util(a, l, pivot - 1);
#pragma omp task default(none) shared(a) firstprivate(r, pivot)
        qs_util(a, pivot + 1, r);
    }
}

void qs(vector<int> &a, int l, int r)
{
#pragma omp        parallel default(none) shared(a, l, r)
#pragma omp single nowait
    qs_util(a, l, r);
}

int main(void)
{
    int         n = 100;
    vector<int> w(n);

#pragma omp parallel for shared(n, w)
    for (int i = 0; i < n; i++)
        w[i] = rand() % 100;

    qs(w, 0, n - 1);

    for (int i = 0; i < n; i++)
        printf("%d\n", w[i]);
    return 0;
}
