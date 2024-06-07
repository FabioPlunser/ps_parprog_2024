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
	int* b = (int*)malloc(N * sizeof(int));
	int* c = (int*)malloc(N * sizeof(int));

	for(int i = 0; i < N; i++) {
		a[i] = 0;
		c[i] = 0;
		b[i] = rand() % 1000;
	}

	// original
	if(apply == 0) {
		for(int i = 0; i < N; ++i) {
			if(i % 2) {
				a[i] = b[i] + 4;
			} else {
				a[i] = c[i] + 5;
			}
		}
	}
	// transformed code
	else {
		// Handle even indices
		for(int i = 0; i < N; i += 2) {
			a[i] = c[i] + 5;
		}
		// Handle odd indices
		for(int i = 1; i < N; i += 2) {
			a[i] = b[i] + 4;
		}
	}

	free(a);
	free(b);
	free(c);

	return EXIT_SUCCESS;
}