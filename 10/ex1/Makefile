CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c17 -march=native -g -fopenmp
LDFLAGS=-lpthread

TARGETS=delannoy_sequential delannoy_parallel
N_THREADS=1 12
N=3 4 5 6 7 8 9 10

.PHONY: all clean bench bench_all

all: $(TARGETS)

clean:
	$(RM) -f $(TARGETS)
	$(RM) -rf logs

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

bench_all:
	$(MAKE) bench_seq delannoy_sequential; \
	$(MAKE) bench_par delannoy_parallel; \


bench_seq: $(TARGET)
	$(RM) ./logs/$(TARGET).log
	@for n in $(N); do \
		sbatch --output=logs/delannoy_sequential/delannoy_sequential-$$n.log ./job.sh "delannoy_sequential $$n"; \
	done

bench_par: $(TARGET)
	$(RM) ./logs/$(TARGET).log
	@for n_threads in $(N_THREADS); do \
		for n in $(N); do \
			sbatch --output=logs/delannoy_parallel/delannoy_parallel-$$n-$$n_threads.log ./job.sh "delannoy_parallel $$n_threads $$n"; \
		done \
	done

result:
	@for n in $(N); do \
		python3 ../../tool/summarize.py --title "delannoy N=$$n²" --input ./logs/$$n --output ./results/$$n; \
	done