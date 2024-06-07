#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 64 / sizeof(double)

int min(int a, int b) {
	return a < b ? a : b;
}

int main(int argc, char** argv) {
	if(argc != 3) {
		fprintf(stderr, "Error: usage: %s <N> <apply tranformation>\n", argv[0]);
		return EXIT_FAILURE;
	}

	int N = atoi(argv[1]);
	if(N > 3000) {
		N = 3000;
		printf("Reduced N to %d\n", N);
	}
	int apply = atoi(argv[2]);

	double** a = (double**)malloc(N * sizeof(double*));
	double** b = (double**)malloc(N * sizeof(double*));
	double** c = (double**)malloc(N * sizeof(double*));
	for(int i = 0; i < N; ++i) {
		a[i] = (double*)malloc(N * sizeof(double));
		b[i] = (double*)malloc(N * sizeof(double));
		c[i] = (double*)malloc(N * sizeof(double));
	}

	srand(apply);
	for(int i = 0; i < N; ++i) {
		for(int j = 0; j < N; ++j) {
			a[i][j] = ((double)rand() / (double)RAND_MAX) * 100.0;
			b[i][j] = ((double)rand() / (double)RAND_MAX) * 100.0;
			c[i][j] = 0.0;
		}
	}

	// original
	if(apply == 0) {
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				for(int k = 0; k < N; ++k) {
					c[i][j] = a[i][k] * b[k][j];
				}
			}
		}
	}
	// transformed code
	else {
		for(int ic = 1; ic < N; ic += BLOCK_SIZE) {
			for(int jc = 1; jc < N; jc += BLOCK_SIZE) {
				for(int kc = 1; kc < N; kc += BLOCK_SIZE) {
					for(int i = ic; i < min(N, ic + BLOCK_SIZE - 1); ++i) {
						for(int j = jc; j < min(N, jc + BLOCK_SIZE - 1); ++j) {
							for(int k = kc; k < min(N, kc + BLOCK_SIZE - 1); ++k) {
								c[i][j] = a[i][k] * b[k][j];
							}
						}
					}
				}
			}
		}
	}

	for(int i = 0; i < N; ++i) {
		free(a[i]);
		free(b[i]);
		free(c[i]);
	}

	free(a);
	free(b);
	free(c);

	return EXIT_SUCCESS;
}