CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -std=c17 -o3 -march=native -g -fopenmp
LDFLAGS=-lpthread

TARGETS=ser_ex1_a ser_ex1_b ser_ex1_c par_ex1_a par_ex1_b par_ex1_c
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
		sbatch --output=logs/$(TARGET)-$$n_threads.log ./job.sh "$(TARGET) $$n_threads 1000000000"; \
	done

