CFLAGS_normal = -std=gnu11 -Wall -Wextra -lm 
CFLAGS_fast = -std=gnu11 -Wall -Wextra -lm -O3 -fopenmp

.PHONY: all
all: mandelbrot

.PHONY: clean
clean:
	$(RM) mandelbrot mandelbrot.png
	$(RM) mandelbrot_fast mandelbrot_fast.png
	$(RM) -r logs

.PHONE: test
test: mandelbrot
	sbatch --output=logs/mandelbrot.log ./job.sh mandelbrot 

.PHONE: test_fast
test_fast: mandelbrot_fast
	sbatch --output=logs/mandelbrot_fast.log ./job.sh  mandelbrot_fast 


mandelbrot: mandelbrot.c
	$(CC) $(CFLAGS_normal) -o mandelbrot mandelbrot.c

mandelbrot_fast: mandelbrot_fast.c
	$(CC) $(CFLAGS_fast) -o mandelbrot_fast mandelbrot_fast.c