CC=gcc
CFLAGS= -O2 -ftree-vectorize -fopt-info-vec-all-internals

TARGETS= analysis

.PHONY: all clean 

all: $(TARGETS)

clean:
	$(RM) -f $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@ 



