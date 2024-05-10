CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c17 -O3 -march=native -g -fopenmp
LDFLAGS=-lpthread

## module load  gcc/12.2.0-gcc-8.5.0-p4pe45v

TARGETS=ex_01_close ex_01_master ex_01_spread
N_THREADS=6
PROC_TYPES=threads cores sockets

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
	@i=1; \
	for proc_typ in $(PROC_TYPES); do \
		for n_threads in $(N_THREADS); do \
			export OMP_PLACES=$$proc_typ; \
			sbatch --output=logs/$(TARGET)-$$i-$$proc_typ.log ./job.sh "$(TARGET) $$i 500000000"; \
			i=$$(( $$i + 1 )); \
		done \
	done
