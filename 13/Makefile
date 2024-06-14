CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c17 -march=native -g -fopenmp -lm
LDFLAGS=-lpthread

TARGETS=n_body_simulation_seq n_body_simulation_par
N_THREADS=1 2 4 6 8 12
N_PARTICLES=100 200 500 1000 2000 5000
TIME_STEPS=20 50 100

.PHONY: all clean bench_seq bench_par bench_all gif_par gif_seq result gif

all: $(TARGETS)

clean:
	$(RM) -f $(TARGETS)
	$(RM) -rf logs
	$(RM) -f data.dat
	$(RM) -f output.gif

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

bench_all:
	$(RM) -rf logs
	$(MAKE) bench_seq; \
	$(MAKE) bench_par; \

bench_seq: n_body_simulation_seq
	@for n in $(N_PARTICLES); do \
		for t in $(TIME_STEPS); do \
			sbatch --output=logs/n_body_simulation_seq-$$n-$$t.log ./job.sh "n_body_simulation_seq $$n $$t 1"; \
		done \
	done

bench_par: n_body_simulation_par
	@for n_threads in $(N_THREADS); do \
		for n in $(N_PARTICLES); do \
			for t in $(TIME_STEPS); do \
				sbatch --output=logs/n_body_simulation_par-$$n-$$t-$$n_threads.log ./job.sh "n_body_simulation_par $$n_threads $$n $$t 1"; \
			done \
		done \
	done

gif_seq: n_body_simulation_seq
	$(RM) -rf data.dat
	sbatch --output=logs/n_body_simulation_seq_gif-100.log ./job.sh "n_body_simulation_seq 7 300 0"; \
	$(SH) ./gif_maker.sh 

gif_par: n_body_simulation_par 
	$(RM) -rf data.dat
	sbatch --output=logs/n_body_simulation_par_gif-100-12.log ./job.sh "n_body_simulation_par 12 7 300 0"; \
	$(SH) ./gif_maker.sh 

result:
	timeout 2s python3 ../../tool/summarize.py --title "n body simulation" --input ./logs/ --output ./results/ || true
	sed -i 's/num_threads/size/g' ./results/n_body_simulation.md

gif: 
	gnuplot particle.plt