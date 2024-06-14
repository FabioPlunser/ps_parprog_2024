#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define GRAVITATIONAL_CONSTANT 1.0;
#define X_MAX 101
#define Y_MAX 101
#define Z_MAX 101
#define X_MIN -1
#define Y_MIN -1
#define Z_MIN -1
#define MARGIN 20
#define MASS_MIN 1
#define MASS_MAX 10
#define VELOCITY_MIN -2
#define VELOCITY_MAX 2

typedef struct particle {
	double position[3]; // x, y, z
	double velocity;
	double mass;
} particle;

int main(int argc, char** argv) {
	if(argc != 3) {
		fprintf(stderr, "Error: usage: %s <n> <dt>\n", argv[0]);
		return EXIT_FAILURE;
	}

	size_t number_of_particles = atoi(argv[1]);
	size_t number_of_time_steps = atoi(argv[2]);
	// Allocate memory for particles
	particle* particles = (particle*)malloc(number_of_particles * sizeof(particle));

	// Initialize particles
	for(size_t i = 0; i < number_of_particles; i++) {
		particles[i].position[0] = rand() % (X_MAX - X_MIN + 1) + X_MIN - MARGIN;
		particles[i].position[1] = rand() % (Y_MAX - Y_MIN + 1) + Y_MIN - MARGIN;
		particles[i].position[2] = rand() % (Z_MAX - Z_MIN + 1) + Z_MIN - MARGIN;
		particles[i].velocity = rand() % (VELOCITY_MAX - VELOCITY_MIN + 1) + VELOCITY_MIN;
		particles[i].mass = rand() % (MASS_MAX - MASS_MIN + 1) + MASS_MIN;
	}

	// Prepare timing measurement
	double start_time, end_time, elapsed_time;

	start_time = omp_get_wtime();

	// N-body simulation

	// Stop timing measurement
	end_time = omp_get_wtime();

	elapsed_time = end_time - start_time;

	// Free memory
	free(particles);

	// Generate benchmark result output
	printf("#Benchmark | %s | %lu | %lu | %.3f\n", argv[0], number_of_particles,
	       number_of_time_steps, elapsed_time);

	return EXIT_SUCCESS;
}