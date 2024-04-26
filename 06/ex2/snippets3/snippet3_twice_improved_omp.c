#include <errno.h>
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
	if(argc != 3) {
		fprintf(stderr, "Error: usage: %s <n>\n", argv[0]);
		return EXIT_FAILURE;
	}

	int num_threads = atoi(argv[1]);
	if(num_threads <= 0) {
		fprintf(stderr, "Number of threads must be a positive integer\n");
		return EXIT_FAILURE;
	}

	errno = 0;
	char* str = argv[2];
	char* endptr;
	long n = strtol(str, &endptr, 0);
	if(errno != 0) {
		perror("strtol");
		return EXIT_FAILURE;
	}
	if(endptr == str) {
		fprintf(stderr, "Error: no digits were found!\n");
		return EXIT_FAILURE;
	}
	if(n < 0) {
		fprintf(stderr, "Error: matrix size must not be negative!\n");
		return EXIT_FAILURE;
	}

	// allocate memory
	int* x = malloc(sizeof(x) * n);
	int* y = malloc(sizeof(y) * n);

	srand(7);
	for(long i = 0; i < n; i++) {
		x[i] = rand();
		y[i] = rand();
	}

		omp_set_num_threads(num_threads);
	// Prepare timing measurement
	double start_time, end_time, elapsed_time;
	int twice = 1;
	start_time = omp_get_wtime();

#pragma omp parallel
	{
#pragma omp for
		for(int i = 0; i < n; i++) {
			x[i] = x[i] + 5 * y[i]; // s2
		}

		if(twice) {
#pragma omp for
			for(int i = 1; i < n; i++) {
				x[i - 1] = 2 * x[i - 1]; // s3
			}
		}
	}
	end_time = omp_get_wtime();
	elapsed_time = end_time - start_time;

	double res = 0;
	for(int i = 1; i < n; i++) {
		res += x[i] + y[i];
	}
	// Generate benchmark result output
	printf("#Benchmark | %s | %u | %.3f\n", argv[0], num_threads, elapsed_time);
	printf("res: %lf, time: %2.2f seconds\n", res, end_time - start_time);

	free(x);
	free(y);
}
