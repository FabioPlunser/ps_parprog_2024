#include <omp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	if(argc != 3) {
		fprintf(stderr, "Error: usage: %s <number_of_threads> <n>\n", argv[0]);
		return EXIT_FAILURE;
	}

	int num_threads = atoi(argv[1]);
	size_t n = atoi(argv[2]);

	// Set number of OpenMP threads
	omp_set_num_threads(num_threads);

	// Setup arrays for algorithm test
	int_fast8_t a[n][n];
	int_fast8_t b[n][n];
	int_fast8_t c[n][n];

#pragma omp parallel for collapse(2)
	for(size_t i = 0; i < n; i++) {
		for(size_t j = 0; j < n; j++) {
			a[i][j] = (int_fast8_t)(i % 4);
			b[i][j] = (int_fast8_t)(j % 4);
		}
	}

	// Prepare timing measurement
	double start_time, end_time, elapsed_time;

	start_time = omp_get_wtime();

// Code to test
#pragma omp parallel for schedule(guided)
	for(size_t i = 0; i < n; ++i) {
		for(size_t j = 0; j < n; ++j) {
			c[i][j] = a[i][j] * b[i][j];
		}
	}

	end_time = omp_get_wtime();
	elapsed_time = end_time - start_time;

	// Verification
	int32_t result = 0;
#pragma omp parallel for collapse(2) reduction(+ : result)
	for(size_t i = 0; i < n; ++i) {
		for(size_t j = 0; j < n; ++j) {
			result += c[i][j];
		}
	}
	printf("Checksum: %d\n", result);

	// Generate benchmark result output
	printf("#Benchmark | %s | %u | %.3f\n", argv[0], num_threads, elapsed_time);

	return EXIT_SUCCESS;
}