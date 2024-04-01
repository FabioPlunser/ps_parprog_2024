CFLAGS = -std=gnu11 -Wall -Wextra -lm 


.PHONY: all
all: hadamard_column hadamard_row


.PHONY: clean
clean:
	$(RM) hadamard_column hadamard_row
	$(RM) cachegrind.out.*


hadamard_column: hadamard_column.c
	$(CC) $(CFLAGS) -o hadamard_column hadamard_column.c

hadamard_row: hadamard_row.c
	$(CC) $(CFLAGS) -o hadamard_row hadamard_row.c

.PHONY: run_tests
run_tests: test_val_col  test_perf_col test_val_row test_perf_row

.PHONY: 
test_val_col: hadamard_column
	srun valgrind --tool=cachegrind ./hadamard_column

.PHONY:
test_val_row: hadamard_row
	srun valgrind --tool=cachegrind ./hadamard_row

.PHONY:
test_perf_col: hadamard_column
	srun perf stat -e LLC-load-misses -e LLC-store-misses ./hadamard_column

.PHONY:
test_perf_row: hadamard_row
	srun perf stat -e LLC-load-misses -e LLC-store-misses ./hadamard_row

