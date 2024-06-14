CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c17 -march=native -g -fopenmp
LDFLAGS=-lpthread

TARGETS=n_body_simulation_seq n_body_simulation_par
N_THREADS=1 12
N_PARTICLES=10 100
TIME_STEPS=5 10

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
	@for n in $(N_PARTICLES); do \
		for t in $(TIME_STEPS); do \
			sbatch --output=logs/n_body_simulation_seq-$$n.log ./job.sh "n_body_simulation_seq $$n $$t"; \
		done \
	done

bench_par: 
	@for n_threads in $(N_THREADS); do \
		for n in $(N_PARTICLES); do \
			for t in $(TIME_STEPS); do \
				sbatch --output=logs/n_body_simulation_par-$$n-$$n_threads.log ./job.sh "n_body_simulation_par $$n_threads $$n $$t"; \
			done \
		done \
	done


result:
	timeout 2s python3 ../../tool/summarize.py --title "n body simulation" --input ./logs/ --output ./results/ || true
	sed -i 's/num_threads/size/g' ./results/n_body_simulation.md