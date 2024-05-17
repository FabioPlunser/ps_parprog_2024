CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c17 -O1 -march=native -g -fopenmp
LDFLAGS=-lpthread

TARGETS=sequential sequential_vectorized
SIZES=64 128 256 512 1024 2048


.PHONY: all clean bench bench_all

all: $(TARGETS)

clean:
	$(RM) -f $(TARGETS)
	$(RM) -rf logs

sequential: sequential.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

sequential_vectorized: sequential.c
	$(CC) $(CFLAGS) -ftree-vectorize $< -o $@ $(LDFLAGS)

bench_all:
	@for target in $(TARGETS); do \
		$(MAKE) bench TARGET=$$target; \
	done


bench: $(TARGET)
	$(RM) ./logs/$(TARGET).log
	@for size in $(SIZES); do \
		sbatch --output=logs/$(TARGET)-$$size.log ./job.sh "$(TARGET) $$size"; \
	done

result:
	python3 ../../tool/summarize.py --title "Sequential" --input ./logs/ --output ./results/; \