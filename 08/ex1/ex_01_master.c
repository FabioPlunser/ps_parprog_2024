#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	if(argc != 3) {
		fprintf(stderr, "Error: usage: %s <number_of_threads> <n>\n", argv[0]);
		return EXIT_FAILURE;
	}

	int num_threads = atoi(argv[1]);
	unsigned n = atol(argv[2]);

	// Set number of OpenMP threads
	omp_set_num_threads(6);

	// Prepare timing measurement
	double start_time, end_time, elapsed_time;
	int sum = 0;
	start_time = omp_get_wtime();
#pragma omp parallel proc_bind(master)
	{
#pragma omp for
		for(size_t i = 0; i < n; i++) {
#pragma omp atomic
			sum++;
		}
	}

	end_time = omp_get_wtime();
	elapsed_time = end_time - start_time;

	// Generate benchmark result output
	printf("#Benchmark | %s | %u | %.3f\n", argv[0], num_threads, elapsed_time);
	printf("Sum: %d\n", sum);

	return EXIT_SUCCESS;
}