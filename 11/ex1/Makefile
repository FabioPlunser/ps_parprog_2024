CC=gcc
CC_FLAGS=-O3 -g3 -lm -pg

.PHONEY: all
all: real

SRC=$(wildcard *.c)

real: $(SRC)
	@$(CC) $(CC_FLAGS) $(SRC) -o real

.PHONEY: clean
clean:
	@rm real
	@rm -rf logs

.PHONEY: run
run: all
	sbatch --output=logs/real.log ./job.sh real

.PHONEY: profile
profile: run
	@mkdir -p results
	gprof real logs/gmon.out.log > results/analysis.txt