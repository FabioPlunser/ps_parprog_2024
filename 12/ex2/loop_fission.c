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

	int sum_a= 0, sum_b = 0, sum_c = 0;
	// original
	if(apply == 0) {
		for(int i = 0; i < N; ++i) {
			sum_a += a[i];
			sum_b += b[i];
			sum_c += c[i];
		}
	}
	// transformed code
	else {
		for(int i = 0; i < N; ++i) {
			sum_a += a[i];
		}
		for(int i = 0; i < N; ++i) {
			sum_b += b[i];
		}
		for(int i = 0; i < N; ++i) {
			sum_c += c[i];
		}
	}


  free(a);
  free(b);
  free(c);


	return EXIT_SUCCESS;
}