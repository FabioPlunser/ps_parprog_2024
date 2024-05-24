#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

long long int delannoy(long long int** D, size_t m, size_t n);

int main(int argc, char** argv) {
	if(argc != 3) {
		fprintf(stderr, "Error: usage: %s <number_of_threads> <n>\n", argv[0]);
		return EXIT_FAILURE;
	}

	int num_threads = atoi(argv[1]);
	size_t n = atoi(argv[2]);

	// Set number of OpenMP threads
	omp_set_num_threads(num_threads);

	// Setup Matrix D
	long long int** D = malloc((n + 1) * sizeof(long long int*));
	for(size_t i = 0; i <= n; i++) {
		D[i] = malloc((n + 1) * sizeof(long long int));
	}

	// Prepare timing measurement
	double start_time, end_time, elapsed_time;

	start_time = omp_get_wtime();
	long long int result;

	// Code to test
#pragma omp parallel
#pragma omp single
	result = delannoy(D, n, n);

	// Timing measurement
	end_time = omp_get_wtime();

	elapsed_time = end_time - start_time;

	// Verification
	printf("Checksum: %lld\n", result);

	// Free Time
	for(size_t i = 0; i <= n; i++) {
		free(D[i]);
	}
	free(D);
	// Generate benchmark result output
	printf("#Benchmark | %s (n_threads=%u) | %lu | %.3f\n", argv[0], num_threads, n, elapsed_time);

	return EXIT_SUCCESS;
}

long long int delannoy(long long int** D, size_t m, size_t n) {
	if(n == 0 || m == 0) {
		return 1;
	}
	long long int sum;

#pragma omp task shared(sum, D) firstprivate(m, n)
	sum = delannoy(D, m - 1, n) + delannoy(D, m - 1, n - 1) + delannoy(D, m, n - 1);

#pragma omp taskwait
	return sum;
}
