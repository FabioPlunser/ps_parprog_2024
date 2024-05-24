#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

long long int delannoy(long long int** D, size_t m, size_t n);

int main(int argc, char** argv) {
	if(argc != 2) {
		fprintf(stderr, "Error: usage: %s <n>\n", argv[0]);
		return EXIT_FAILURE;
	}

	size_t n = atoi(argv[1]);

	// Set number of OpenMP threads
	omp_set_num_threads(1);

	// Setup Matrix D
	long long int** D = malloc((n + 1) * sizeof(long long int*));
	for(size_t i = 0; i <= n; i++) {
		D[i] = malloc((n + 1) * sizeof(long long int));
	}

	// Prepare timing measurement
	double start_time, end_time, elapsed_time;

	start_time = omp_get_wtime();

	// Code to test
	long long int result = delannoy(D, n, n);

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
	printf("#Benchmark | %s | %lu | %.3f\n", argv[0], n, elapsed_time);

	return EXIT_SUCCESS;
}

long long int delannoy(long long int** D, size_t m, size_t n) {
	if(n == 0 || m == 0) {
		return 1;
	}
	return delannoy(D, m - 1, n) + delannoy(D, m - 1, n - 1) + delannoy(D, m, n - 1);
}