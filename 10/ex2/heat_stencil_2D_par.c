#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESOLUTION_WIDTH 50
#define RESOLUTION_HEIGHT 50

#define PERROR fprintf(stderr, "%s:%d: error: %s\n", __FILE__, __LINE__, strerror(errno))
#define PERROR_GOTO(label) \
	do { \
		PERROR; \
		goto label; \
	} while(0)

// -- vector utilities --

#define IND(y, x) ((y) * (N) + (x))

void printTemperature(double* m, int N, int M);

// -- simulation code ---

int main(int argc, char** argv) {
	if(argc != 3) {
		fprintf(stderr, "Error: usage: %s <number_of_threads> <size>\n", argv[0]);
		return EXIT_FAILURE;
	}

	// Set number of OpenMP threads
	int num_threads = atoi(argv[1]);
	omp_set_num_threads(num_threads);

	// prepare success flag for verification
	int success = 1;

	// 'parsing' optional input parameter = problem size
	int N = atoi(argv[2]);
	int T = N * 10;
	printf("Computing heat-distribution for room size %dX%d for T=%d timesteps\n", N, N, T);

	// ---------- setup ----------

	// create a buffer for storing temperature fields
	double* A = malloc(sizeof(double) * N * N);

	if(!A) PERROR_GOTO(error_a);

	// set up initial conditions in A
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			A[IND(i, j)] = 273; // temperature is 0° C everywhere (273 K)
		}
	}

	// and there is a heat source
	int source_x = N / 4;
	int source_y = N / 4;
	A[IND(source_x, source_y)] = 273 + 60;

	printf("Initial:\n");
	printTemperature(A, N, N);
	printf("\n");

	// ---------- compute ----------
	// Prepare timing measurement
	double start_time, end_time, elapsed_time;

	start_time = omp_get_wtime();

	// create a second buffer for the computation
	double* B = malloc(sizeof(double) * N * N);
	if(!B) PERROR_GOTO(error_b);
	// for each time step ..
	for(int t = 0; t < T; t++) {
#pragma omp parallel for collapse(2)
		for(int x = 0; x < N; x++) {
			for(int y = 0; y < N; y++) {
				if(x == source_x && y == source_y) {
					B[IND(x, y)] = A[IND(x, y)];
				} else {
					double up = (x == 0) ? A[IND(x, y)] : A[IND(x - 1, y)];
					double down = (x == N - 1) ? A[IND(x, y)] : A[IND(x + 1, y)];
					double left = (y == 0) ? A[IND(x, y)] : A[IND(x, y - 1)];
					double right = (y == N - 1) ? A[IND(x, y)] : A[IND(x, y + 1)];

					B[IND(x, y)] = 0.25 * (up + down + left + right);
				}
			}
		}

		// swap the buffers
		double* temp = A;
		A = B;
		B = temp;

		// every 1000 steps show intermediate step
		if(!(t % 1000)) {
			printf("Step t=%d\n", t);
			printTemperature(A, N, N);
			printf("\n");
		}
	}

	end_time = omp_get_wtime();
	elapsed_time = end_time - start_time;

	// ---------- check ----------

	printf("Final:\n");
	printTemperature(A, N, N);
	printf("\n");

	// simple verification if nowhere the heat is more then the heat source
	for(long long i = 0; i < N; i++) {
		for(long long j = 0; j < N; j++) {
			double temp = A[IND(i, j)];
			if(273 <= temp && temp <= 273 + 60) continue;
			success = 0;
			break;
		}
	}

	printf("Verification: %s\n", (success) ? "OK" : "FAILED");

	// Generate benchmark result output
	printf("#Benchmark | %s-%d | %u | %.3f\n", argv[0], N, num_threads, elapsed_time);

// todo ---------- cleanup ----------
error_b:
	free(B);
error_a:
	free(A);
	return (success) ? EXIT_SUCCESS : EXIT_FAILURE;
}

void printTemperature(double* m, int N, int M) {
	const char* colors = " .-:=+*^X#%@";
	const int numColors = 12;

	// boundaries for temperature (for simplicity hard-coded)
	const double max = 273 + 30;
	const double min = 273 + 0;

	// set the 'render' resolution
	int W = RESOLUTION_WIDTH;
	int H = RESOLUTION_HEIGHT;

	// step size in each dimension
	int sW = N / W;
	int sH = M / H;

	// upper wall
	printf("\t");
	for(int u = 0; u < W + 2; u++) {
		printf("X");
	}
	printf("\n");
	// room
	for(int i = 0; i < H; i++) {
		// left wall
		printf("\tX");
		// actual room
		for(int j = 0; j < W; j++) {
			// get max temperature in this tile
			double max_t = 0;
			for(int x = sH * i; x < sH * i + sH; x++) {
				for(int y = sW * j; y < sW * j + sW; y++) {
					max_t = (max_t < m[IND(x, y)]) ? m[IND(x, y)] : max_t;
				}
			}
			double temp = max_t;

			// pick the 'color'
			int c = ((temp - min) / (max - min)) * numColors;
			c = (c >= numColors) ? numColors - 1 : ((c < 0) ? 0 : c);

			// print the average temperature
			printf("%c", colors[c]);
		}
		// right wall
		printf("X\n");
	}
	// lower wall
	printf("\t");
	for(int l = 0; l < W + 2; l++) {
		printf("X");
	}
	printf("\n");
}
