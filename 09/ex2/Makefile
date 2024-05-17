CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c17 -O1 -march=native -g -fopenmp
LDFLAGS=-lpthread

TARGETS=sequential sequential_vectorized vectorized_double vectorized_float
SIZES=2048


.PHONY: all clean bench bench_all perf perf_all result

all: $(TARGETS)

clean:
	$(RM) -f $(TARGETS)
	$(RM) -rf logs
	$(RM) -rf perf

sequential: sequential.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

sequential_vectorized: sequential.c
	$(CC) $(CFLAGS) -ftree-vectorize $< -o $@ $(LDFLAGS)


vectorized_float: sequential_float.c
	$(CC) -Wall -Wextra -Wpedantic -Werror -std=c17 -O1 -fopenmp $< -o $@ $(LDFLAGS)

vectorized_double: sequential_double.c
	$(CC) -Wall -Wextra -Wpedantic -Werror -std=c17 -O1 -fopenmp $< -o $@ $(LDFLAGS)

bench_all:
	@for target in $(TARGETS); do \
		$(MAKE) bench TARGET=$$target; \
	done

bench: $(TARGET)
	$(RM) ./logs/$(TARGET).log
	@for size in $(SIZES); do \
		sbatch --output=logs/$(TARGET)-$$size.log ./job.sh "$(TARGET) $$size"; \
	done

perf_all:
	mkdir -p perf
	@for target in $(TARGETS); do \
		$(MAKE) perf TARGET=$$target; \
	done

perf: $(TARGET)
	srun perf stat -o ./perf/$(TARGET).log -e r0110,r0210,r0410,r0810,r1010,r2010,r4010,r8010 ./$(TARGET) 2048

result:
	timeout 2s python3 ../../tool/summarize.py --title "Sequential" --input ./logs/ --output ./results/ || true
	$(RM) ./results/Sequential.png
	sed -i 's/num_threads/size/g' ./results/Sequential.md
