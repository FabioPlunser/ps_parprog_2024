#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

double sqrt(double num);

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

	double x[n], y[n], z[n];
	double a = 1, f;
	double k = 1;

	for(int i = 0; i < n; i++) {
		x[i] = 2;
		y[i] = 2;
	}

	start_time = omp_get_wtime();

	for(int i = 0; i < n; i++) {
		a = (x[i] + y[i]) / (i + 1);
		z[i] = a;
	}

	f = sqrt(a + k);

	end_time = omp_get_wtime();
	elapsed_time = end_time - start_time;

	double sum = 0;
	for(int i = 0; i < n; i++) {
		sum += z[i];
	}

	// Generate benchmark result output
	printf("#Benchmark | %s | %u | %.3f\n", argv[0], num_threads, elapsed_time);
	printf("Sum: %f, f: %f\n", sum, f);

	return EXIT_SUCCESS;
}

// GitHub-Copilot
double sqrt(double num) {
	double error = 1e-15; // define the precision of your result
	double s = num;

	while((s - num / s) > error) {
		s = (s + num / s) / 2;
	}

	return s;
}