CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c17 -O3 -march=native -g -fopenmp
LDFLAGS=-lpthread

TARGETS=mc_pi_local_sum mc_pi_array mc_pi_array_pad
N_THREADS=1 2 4 6 12

.PHONY: all clean

all: $(TARGETS)

clean:
	$(RM) -f $(TARGETS)
	$(RM) -rf logs

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

.PHONY: bench_all
bench_all:
	@for target in $(TARGETS); do \
		$(MAKE) bench TARGET=$$target; \
	done

.PHONY: bench
bench: $(TARGET)
	$(RM) -f ./logs/$(TARGET)
	@for n_threads in $(N_THREADS); do \
		sbatch --output=logs/$(TARGET) --open-mode=append ./job.sh "$(TARGET) $$n_threads"; \
	done

.PHONY: cache_misses_all
cache_misses_all:
	@for target in $(TARGETS); do \
		$(MAKE) cache_misses TARGET=$$target; \
	done

.PHONY: cache_misses
cache_misses: $(TARGET)
	mkdir -p logs
	srun perf stat -e cache-references,cache-misses,L1-dcache-loads,L1-dcache-load-misses,L1-dcache-stores,L1-dcache-store-misses ./$(TARGET) 12 &> ./logs/$(TARGET)_perf_stat.log