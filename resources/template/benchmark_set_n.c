#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	if(argc != 3) {
		fprintf(stderr, "Error: usage: %s <number_of_threads> <n>\n", argv[0]);
		return EXIT_FAILURE;
	}

	int num_threads = atoi(argv[1]);
	int n = atoi(argv[2]);

	// Set number of OpenMP threads
	omp_set_num_threads(num_threads);

	// Prepare timing measurement
	double start_time, end_time, elapsed_time;

	start_time = omp_get_wtime();

    // Your code 

	

	end_time = omp_get_wtime();
	elapsed_time = end_time - start_time;

	// Generate benchmark result output
	printf("#Benchmark | %s | %u | %.3f\n", argv[0], num_threads, elapsed_time);

	return EXIT_SUCCESS;
}