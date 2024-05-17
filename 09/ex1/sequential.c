#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define DATATYPE float
#define MAX_VAL 2.0f

int main(int argc, char** argv) {
	// Parse arguments
	if(argc != 2) {
		fprintf(stderr, "Error: usage: %s <size>\n", argv[0]);
		return EXIT_FAILURE;
	}

	size_t size = atoi(argv[1]);

	// Data preparation
	const size_t num_repetitions = 1000000;
	DATATYPE* a = malloc(size * sizeof(DATATYPE));
	DATATYPE* b = malloc(size * sizeof(DATATYPE));
	DATATYPE* c = malloc(size * sizeof(DATATYPE));
	srand(42);
	for(size_t i = 0; i < size; i++) {
		a[i] = 0.0f;
		b[i] = ((DATATYPE)rand() / (DATATYPE)RAND_MAX) * MAX_VAL;
		c[i] = ((DATATYPE)rand() / (DATATYPE)RAND_MAX) * MAX_VAL;
	}

	// Prepare timing measurement
	double start_time, end_time, elapsed_time;

	start_time = omp_get_wtime();

	// Code to benchmark
	for(size_t run = 0; run < num_repetitions; ++run) {
		for(size_t i = 0; i < size; ++i) {
			a[i] += b[i] * c[i];
		}
	}

	end_time = omp_get_wtime();
	elapsed_time = end_time - start_time;

	// Generate checksum
	float checksum = 0.0f;
	for(size_t i = 0; i < size; ++i) {
		checksum += a[i];
	}
	printf("Checksum: %.4f\n", checksum);

	// Generate benchmark result output
	printf("#Benchmark | %s | %zu | %.3f\n", argv[0], size, elapsed_time);

	// Data cleanup
	free(a);
	free(b);
	free(c);

	return EXIT_SUCCESS;
}