#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define GRAVITATIONAL_CONSTANT 1
#define X_MAX 101
#define Y_MAX 101
#define Z_MAX 101
#define X_MIN -1
#define Y_MIN -1
#define Z_MIN -1
#define MARGIN 20
#define MASS_MIN 1
#define MASS_MAX 20
#define VELOCITY_MIN 0
#define VELOCITY_MAX 0

typedef struct particle {
	double position[3]; // x, y, z
	double velocity[3]; // vx, vy, vz
	double mass;
} particle;

double** compute_force(particle* particles, double** forces, size_t number_of_particles);
void apply_force(particle* particles, double** forces, size_t number_of_particles);

int main(int argc, char** argv) {
	if(argc != 5) {
		fprintf(stderr, "Error: usage: %s <number of threads> <n> <dt> <benchmark-flag>\n",
		        argv[0]);
		return EXIT_FAILURE;
	}

	int number_of_threads = atoi(argv[1]);
	size_t number_of_particles = atoi(argv[2]);
	size_t number_of_time_steps = atoi(argv[3]);
	size_t benchmark_flag = atoi(argv[4]);
	// Allocate memory for particles
	particle* particles = (particle*)malloc(number_of_particles * sizeof(particle));

	// Initialize particles
	for(size_t i = 0; i < number_of_particles; i++) {
		particles[i].position[0] = rand() % (X_MAX - X_MIN + 1 - 2 * MARGIN) + X_MIN + MARGIN;
		particles[i].position[1] = rand() % (Y_MAX - Y_MIN + 1 - 2 * MARGIN) + Y_MIN + MARGIN;
		particles[i].position[2] = rand() % (Z_MAX - Z_MIN + 1 - 2 * MARGIN) + Z_MIN + MARGIN;
		particles[i].velocity[0] = rand() % (VELOCITY_MAX - VELOCITY_MIN + 1) + VELOCITY_MIN;
		particles[i].velocity[1] = rand() % (VELOCITY_MAX - VELOCITY_MIN + 1) + VELOCITY_MIN;
		particles[i].velocity[2] = rand() % (VELOCITY_MAX - VELOCITY_MIN + 1) + VELOCITY_MIN;
		particles[i].mass = rand() % (MASS_MAX - MASS_MIN + 1) + MASS_MIN;
	}

	double** forces = malloc(number_of_particles * sizeof(double*));
	for(size_t i = 0; i < number_of_particles; i++) {
		forces[i] = malloc(3 * sizeof(double));
	}

	// Prepare timing measurement
	omp_set_num_threads(number_of_threads);
	double start_time, end_time, elapsed_time;
	start_time = omp_get_wtime();

	// N-body simulation
	for(size_t t = 1; t < number_of_time_steps; t++) {
		// Compute forces
		forces = compute_force(particles, forces, number_of_particles);

		// Apply forces
		apply_force(particles, forces, number_of_particles);

		if(benchmark_flag == 0) {
			FILE* fptr = fopen("data.dat", "a");
			if(fptr == NULL) {
				return 1;
			}
			for(size_t i = 0; i < number_of_particles; ++i) {
				fprintf(fptr, "%f %f %f\n", particles[i].position[0], particles[i].position[1],
				        particles[i].position[2]);
			}
			fprintf(fptr, "\n\n");
			fclose(fptr);
		}
	}

	// Stop timing measurement
	end_time = omp_get_wtime();
	elapsed_time = end_time - start_time;

	// Free memory
	for(size_t i = 0; i < number_of_particles; i++) {
		free(forces[i]);
	}
	free(forces);
	free(particles);

	if(benchmark_flag == 1) {
		// Generate benchmark result output
		printf("#Benchmark | %s | %lu | %lu | %.3f\n", argv[0], number_of_particles,
		       number_of_time_steps, elapsed_time);
	}

	return EXIT_SUCCESS;
}

double** compute_force(particle* particles, double** forces, size_t number_of_particles) {
#pragma omp parallel for
	for(size_t i = 0; i < number_of_particles; i++) {
		double force[3] = { 0 };
		for(size_t j = 0; j < number_of_particles; j++) {
			if(i != j) {
				double distance[3] = { particles[j].position[0] - particles[i].position[0],
					                   particles[j].position[1] - particles[i].position[1],
					                   particles[j].position[2] - particles[i].position[2] };
				double r = sqrtl(distance[0] * distance[0] + distance[1] * distance[1] +
				                 distance[2] * distance[2]);
				if(r == 0) {
					r = 0.001;
				}
				double f = GRAVITATIONAL_CONSTANT * particles[i].mass * particles[j].mass / (r * r);
				force[0] += f * distance[0] / r;
				force[1] += f * distance[1] / r;
				force[2] += f * distance[2] / r;
			}
			forces[i][0] = force[0];
			forces[i][1] = force[1];
			forces[i][2] = force[2];
		}
	}
	return forces;
}

void apply_force(particle* particles, double** forces, size_t number_of_particles) {
#pragma omp parallel for
	for(size_t i = 0; i < number_of_particles; i++) {
		double new_velocity[3] = { particles[i].velocity[0] + (forces[i][0] / particles[i].mass),
			                       particles[i].velocity[1] + (forces[i][1] / particles[i].mass),
			                       particles[i].velocity[2] + (forces[i][2] / particles[i].mass) };
		particles[i].velocity[0] = new_velocity[0];
		particles[i].velocity[1] = new_velocity[1];
		particles[i].velocity[2] = new_velocity[2];
		particles[i].position[0] += new_velocity[0];
		particles[i].position[1] += new_velocity[1];
		particles[i].position[2] += new_velocity[2];
	}
}