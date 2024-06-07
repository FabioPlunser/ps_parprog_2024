CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c17 -O3 -march=native -g -fopenmp
LDFLAGS=-lpthread

TARGETS=loop_unrolling loop_unswitching loop_peeling_fusion loop_tiling loop_fission loop_invariant loop_splitting
N=100000000

.PHONY: all clean perf perf_all

all: $(TARGETS)
	mkdir -p perf

clean:
	$(RM) -f $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

perf_all:
	@for target in $(TARGETS); do \
		$(MAKE) perf TARGET=$$target; \
	done


perf: $(TARGET)
	srun perf stat -e task-clock,cache-misses,cache-references,cycles,instructions,branches,branch-misses -o ./perf/$(TARGET)_original.log ./$(TARGET) $(N) 0
	srun perf stat -e task-clock,cache-misses,cache-references,cycles,instructions,branches,branch-misses -o ./perf/$(TARGET)_transformed.log ./$(TARGET) $(N) 1

