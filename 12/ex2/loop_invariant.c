#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	if(argc != 3) {
		fprintf(stderr, "Error: usage: %s <N> <apply tranformation>\n", argv[0]);
		return EXIT_FAILURE;
	}

	int N = atoi(argv[1]);
	int apply = atoi(argv[2]);

	double* a = (double*)malloc(N * sizeof(double));
	int* b = (int*)malloc(N * sizeof(int));

	for(int i = 0; i < N; i++) {
		a[i] = 0;
		b[i] = rand() % 1000;
	}

	// original
	if(apply == 0) {
		for(int i = 0; i < N; ++i) {
			a[i] *= hypot(0.3, 0.4);
		}
	}
	// transformed code
	else {
		// don't need to call hypot every iteration if the
		// variables don't change
		double hypo = hypot(0.3, 0.4);
		for(int i = 0; i < N; ++i) {
			a[i] *= hypo;
		}
	}

	free(a);
	free(b);

	return EXIT_SUCCESS;
}