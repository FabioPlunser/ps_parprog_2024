#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	if(argc != 3) {
		fprintf(stderr, "Error: usage: %s <N> <apply tranformation>\n", argv[0]);
		return EXIT_FAILURE;
	}

	int N = atoi(argv[1]);
	// ensure that N is odd
	if(N % 2 == 0) {
		N += 1;
	}
	int apply = atoi(argv[2]);

	int* a = (int*)malloc(N * sizeof(int));
	int* b = (int*)malloc(N * sizeof(int));

	for(int i = 0; i < N; i++) {
		a[i] = 0;
		b[i] = rand() % 1000;
	}

	// original
	if(apply == 0) {
		for(int i = 0; i < N - 1; ++i) {
			a[i] = b[i] + b[i + 1];
		}
	}
	// transformed code
	else {
		for(int i = 0; i < N - 1; i += 2) {
			a[i] = b[i] + b[i + 1];
			a[i + 1] = b[i + 1] + b[i + 2];
		}
	}

	free(a);
	free(b);

	return EXIT_SUCCESS;
}