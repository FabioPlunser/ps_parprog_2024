#include <omp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Include that allows to print result as an image
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Default size of image
#define X 1280
#define Y 720
#define MAX_ITER 10000

void calc_mandelbrot(uint8_t image[Y][X]) {
	#pragma omp parallel for
	for(size_t i = 0; i < Y; i++) {
		for(size_t j = 0; j < X; j++) {
			double x = 0.0;
			double y = 0.0;
			double cx = (double)j / X * 3.5 - 2.5;
			double cy = (double)i / Y * 2.0 - 1.0;
			int iteration = 0;
			while(x * x + y * y <= 4 && iteration < MAX_ITER) {
				double x_temp = x * x - y * y + cx;
				y = 2 * x * y + cy;
				x = x_temp;
				iteration++;
			}
			if(iteration == MAX_ITER) {
				image[i][j] = 0;
			} else {
				image[i][j] = iteration % 255;
			}
		}
	}
}

int main() {
	uint8_t image[Y][X];
	double start_time, end_time;
	start_time = omp_get_wtime();
	calc_mandelbrot(image);
	end_time = omp_get_wtime();
	float diff = end_time - start_time;
	printf("time: %2.6f seconds\n", diff);
	const int channel_nr = 1, stride_bytes = 0;
	stbi_write_png("mandelbrot_fast.png", X, Y, channel_nr, image, stride_bytes);
	return EXIT_SUCCESS;
}