CFLAGS = -std=gnu11 -Wall -Wextra -lm -fopenmp -O3
TARGETS=ex2 ex2_flush ex2_atomic

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	$(RM) $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

.PHONY: run
run: $(TARGETS)
	salloc --exclusive --tasks-per-node=1 --cpus-per-task=1 srun --pty bash
