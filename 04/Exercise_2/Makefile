CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c17 -O3 -march=native -g -fopenmp
LDFLAGS=-lpthread

TARGETS=mc_pi_local_sum mc_pi_array mc_pi_array_pad
N_THREADS=1 2 4 6 12

.PHONY: all clean

all: $(TARGETS)

clean:
	$(RM) $(TARGETS)
	$(RM) -r logs

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

.PHONY: bench_all
bench_all:
	@for target in $(TARGETS); do \
		$(MAKE) bench TARGET=$$target; \
	done

.PHONY: bench
bench:
	@for n_threads in $(N_THREADS); do \
		sbatch --output=logs/$(TARGET).log ./job.sh "$(TARGET) $$n_threads"; \
	done
