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

	double x[n], y[n];
	double a = 1;
	double b = 2;

	for(int i = 0; i < n; i++) {
		x[i] = 2;
		y[i] = 2;
	}

	start_time = omp_get_wtime();

#pragma omp parallel for
	for(int i = 0; i < n; i++) {
		x[i] = y[i] * 2 + b * i;
		y[i] = x[i] + a / (i + 1);
	}

	end_time = omp_get_wtime();
	elapsed_time = end_time - start_time;

	double sum = 0;
	for(int i = 0; i < n; i++) {
		sum += y[i];
	}

	// Generate benchmark result output
	printf("#Benchmark | %s | %u | %.3f\n", argv[0], num_threads, elapsed_time);
	printf("Sum: %f,\n", sum);

	return EXIT_SUCCESS;
}