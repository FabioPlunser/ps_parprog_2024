#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

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
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				for(int k = 0; k < N; ++k) {
					c[i][j] = a[i][k] * b[k][j];
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