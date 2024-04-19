CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c17 -O3 -march=native -g -fopenmp
LDFLAGS=-lpthread

TARGETS=ex1 ex1-cache-sum-in-mult ex1-improved-cache-allign-mult ex1-reduction-sum ex1-removed-nested-parallel
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
		sbatch --output=logs/$(TARGET)-$(N_THREADS).log --open-mode=append ./job.sh "$(TARGET) $$n_threads 1500"; \
	done

