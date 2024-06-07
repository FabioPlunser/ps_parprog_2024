CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -std=c17 -march=native -g -O3

TARGETS=comparisonCode

.PHONY: all clean

all: $(TARGETS)

clean:
	$(RM) -f $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@ 

comparisonCode: comparisonCode.c