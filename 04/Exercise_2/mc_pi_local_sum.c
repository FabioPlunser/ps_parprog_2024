#include <omp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define RND_MAX 0x7FFFFFFF

typedef uint32_t count_t;

int main(int argc, char* argv[]) {
	if(argc != 2) {
		fprintf(stderr, "Usage: %s [<thread_count>]\n", argv[0]);
		return EXIT_FAILURE;
	}

	int num_threads = atoi(argv[1]);
	if(num_threads <= 0) {
		fprintf(stderr, "Number of threads must be a positive integer\n");
		return EXIT_FAILURE;
	}

	const count_t num_points = ((count_t)700) * 1000 * 1000;
	count_t points_inside = 0;
	count_t points_inside_local;
	double x, y;

	// Prepare timing measurement
	double start_time, end_time;

	// Set number of OpenMP threads
	omp_set_num_threads(num_threads);

	// Record start time
	start_time = omp_get_wtime();

// Calculation
#pragma omp parallel private(x, y, points_inside_local)
	{
		unsigned int seed = omp_get_thread_num();
		points_inside_local = 0;

#pragma omp for
		for(count_t i = 0; i < num_points; i++) {
			x = (double)rand_r(&seed) / RND_MAX;
			y = (double)rand_r(&seed) / RND_MAX;

			if(x * x + y * y <= 1.0) {
				points_inside_local++;
			}
		}

#pragma omp atomic
		points_inside += points_inside_local;
	}

	double pi_approximation = 4.0 * points_inside / num_points;

	// Record end time
	end_time = omp_get_wtime();

	double elapsed_time = end_time - start_time;

	printf("Approximation of PI took %.3f seconds with %u threads - value: %.10f\n", elapsed_time,
	       num_threads, pi_approximation);

	printf("#Benchmark | %s | %u | %.3f\n", argv[0], num_threads, elapsed_time);

	return EXIT_SUCCESS;
}