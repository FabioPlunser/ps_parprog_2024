CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c17 -O3 -march=native -g -fopenmp
LDFLAGS=-lpthread

TARGETS=mc_pi_pthreads
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
	$(MAKE) bench_mc_pi_pthreads

.PHONY: bench_mc_pi_pthreads
bench_mc_pi_pthreads:
	@for n_threads in $(N_THREADS); do \
		sbatch --output=logs/mc_pi_pthreads.log ./job.sh "mc_pi_pthreads $$n_threads"; \
	done

