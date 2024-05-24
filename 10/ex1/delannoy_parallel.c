#include <omp.h>
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

	// Setup Matrix D
	long long int** D = malloc((n + 1) * sizeof(long long int*));
	for(size_t i = 0; i <= n; i++) {
		D[i] = malloc((n + 1) * sizeof(long long int));
	}

	// Prepare timing measurement
	double start_time, end_time, elapsed_time;

	start_time = omp_get_wtime();

	// Code to test
	for(size_t i = 0; i <= n; i++) {
		for(size_t j = 0; j <= n; j++) {
			if(i == 0 || j == 0) {
				D[i][j] = 1;
			} else {
				D[i][j] = D[i - 1][j] + D[i - 1][j - 1] + D[i][j - 1];
			}
		}
	}

	// Timing measurement
	end_time = omp_get_wtime();

	elapsed_time = end_time - start_time;

	// Verification
	printf("Checksum: %lld\n", D[n][n]);

	// Free Time
	for(size_t i = 0; i <= n; i++) {
		free(D[i]);
	}
	// Generate benchmark result output
	printf("#Benchmark | %s | %u | %.3f\n", argv[0], num_threads, elapsed_time);

	return EXIT_SUCCESS;
}