#include <iostream>
#include <omp.h>

#define N 5 // Number of philosophers
#define M 10 // Number of steps until termination

using namespace std;

int main() {
	int id;
	int l, r;
	bool waiting = true;
	bool fork[N] = {true};
	int bites[N] = {0};

	omp_lock_t eat_lock, print_lock;

	omp_init_lock(&eat_lock);
	omp_init_lock(&print_lock);

	omp_set_num_threads(N);

	#pragma omp parallel shared(fork, bites, eat_lock, print_lock) private(id, l, r, waiting)
	{
		id = omp_get_thread_num();
		l = id;
		r = (id + 1) % N;

		while (bites[id] < M) {
			omp_set_lock(&eat_lock);
			if (fork[l] && fork[r]) waiting = fork[l] = fork[r] = false;
			omp_unset_lock(&eat_lock);

			if (!waiting) {
				bites[id]++;
				waiting = fork[l] = fork[r] = true;
			}

			omp_set_lock(&print_lock);
			cout << "Philosopher " << id + 1 << " bite #" << bites[id] << endl;
			omp_unset_lock(&print_lock);
		}

		omp_set_lock(&print_lock);
		cout << "Philosopher " << id + 1 << " finished eating" << endl;
		omp_unset_lock(&print_lock);
	}

	omp_destroy_lock(&eat_lock);
	omp_destroy_lock(&print_lock);
}
