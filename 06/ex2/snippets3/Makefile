CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c17 -o3 -march=native -g -fopenmp
LDFLAGS=-lpthread

TARGETS=snippet3_twice snippet3_ntwice snippet3_twice_improved_omp snippet3_ntwice_improved_omp
N_THREADS=1 2 4 6 12

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
		sbatch --output=logs/$(TARGET)-$$n_threads.log ./job.sh "$(TARGET) $$n_threads 999999999"; \
	done

