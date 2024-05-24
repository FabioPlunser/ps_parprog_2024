CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c17 -march=native -g -fopenmp
LDFLAGS=-lpthread

TARGETS=delannoy_sequential delannoy_parallel
N_THREADS=1 12
N=3 4 5 6 7 8 9 10 11 12

.PHONY: all clean bench_seq bench_par bench_all result

all: $(TARGETS)

clean:
	$(RM) -f $(TARGETS)
	$(RM) -rf logs

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

bench_all:
	$(RM) -rf logs
	$(MAKE) bench_seq; \
	$(MAKE) bench_par; \


bench_seq: 
	@for n in $(N); do \
		sbatch --output=logs/delannoy_sequential-$$n.log ./job.sh "delannoy_sequential $$n"; \
	done

bench_par: 
	@for n_threads in $(N_THREADS); do \
		for n in $(N); do \
			sbatch --output=logs/delannoy_parallel-$$n-$$n_threads.log ./job.sh "delannoy_parallel $$n_threads $$n"; \
		done \
	done


result:
	timeout 2s python3 ../../tool/summarize.py --title "Delannoy" --input ./logs/ --output ./results/ || true
	sed -i 's/num_threads/size/g' ./results/Delannoy.md