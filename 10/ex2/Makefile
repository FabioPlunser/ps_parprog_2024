CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c17 -O3 -march=native -g -fopenmp
LDFLAGS=-lpthread

TARGETS=heat_stencil_2D_seq heat_stencil_2D_par
N_THREADS=1 2 4 6 10 12
N=200 500

.PHONY: all clean bench bench_all

all: $(TARGETS)

clean:
	$(RM) -f $(TARGETS)
	$(RM) -rf logs

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

bench_all:
	@for target in $(TARGETS); do \
		$(MAKE) bench TARGET=$$target; \
	done


bench: $(TARGET)
	$(RM) ./logs/$(TARGET).log
	@for n_threads in $(N_THREADS); do \
		for n in $(N); do \
			sbatch --output=logs/$$n/$(TARGET)-$$n_threads.log ./job.sh "$(TARGET) $$n_threads $$n"; \
		done \
	done

result:
	@for n in $(N); do \
		python3 ../../tool/summarize.py --title "Heat Stencil 2D (N=$$n)" --input ./logs/$$n/ --output ./results/; \
	done