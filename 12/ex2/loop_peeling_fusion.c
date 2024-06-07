#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	if(argc != 3) {
		fprintf(stderr, "Error: usage: %s <N> <apply tranformation>\n", argv[0]);
		return EXIT_FAILURE;
	}

	int N = atoi(argv[1]);
	int apply = atoi(argv[2]);

	int* a = (int*)malloc(N * sizeof(int));
	unsigned long int sum = 0;

	for(int i = 0; i < N; i++) {
		a[i] = rand() % 1000;
	}

	// original
	if(apply == 0) {
		int min = a[0];
		for(int i = 1; i < N; ++i) {
			min = (a[i] < min) ? a[i] : min;
		}
		for(int i = 0; i < N; ++i) {
			sum += a[i];
		}
	}
	// transformed code
	else {
		int min = a[0];
		for(int i = 1; i < N; ++i) {
			min = (a[i] < min) ? a[i] : min;
		}
		for(int i = 0; i < N; ++i) {
			sum += a[i];
		}
	}

	free(a);

	return EXIT_SUCCESS;
}