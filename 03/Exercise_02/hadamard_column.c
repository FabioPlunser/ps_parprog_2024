#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int main() {
	const size_t n = 1000;
	int32_t a[n][n];
	int32_t b[n][n];
	int32_t c[n][n];

	for(size_t j = 0; j < n; ++j) {
		for(size_t i = 0; i < n; ++i) {
			c[i][j] = a[i][j] * b[i][j];
		}
	}

	return 0;
}