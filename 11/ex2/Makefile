CC=gcc
CC_FLAGS=-O3 -g3 -lm -pg -std=c17 -march=native -g -fopenmp

N_THREADS=1 2 6 12

.PHONEY: all
all: real_seq real_par

SEQ_SRC=$(filter-out real_par.c , $(wildcard *.c))
PAR_SRC=$(filter-out real_seq.c , $(wildcard *.c))

real_seq: $(SEQ_SRC)
	@$(CC) $(CC_FLAGS) $(SEQ_SRC) -o real_seq

real_par: $(PAR_SRC)
	@$(CC) $(CC_FLAGS) $(PAR_SRC) -o real_par

.PHONEY: clean
clean:
	@rm -f real_seq
	@rm -f real_par
	@rm -rf logs

.PHONEY: run
run: all
	sbatch --output=logs/real_seq.log ./job.sh real_seq
	@for n_threads in $(N_THREADS); do \
		sbatch --output=logs/real_par-$$n_threads.log --cpus-per-task=$$n_threads ./job.sh real_par; \
	done

.PHONEY: result
result:
	python3 ../../tool/summarize.py --title "Benchmark" --input ./logs/ --output ./results/