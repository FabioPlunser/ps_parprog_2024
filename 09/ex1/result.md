# Task 1

> Write a sequential program that computes `a[i] += b[i] * c[i]` for three `float` vectors `a`, `b`, and `c`. Enclose this computation in a loop such that it is repeated `1e6` times. I.e. your code should look like this:

```
for(int run = 0; run < repetitions; ++run) {
    for(int i = 0; i < size; ++i) {
        a[i] += b[i] * c[i];
    }
}

# Task 2

> Initialize the vectors with constant values and add some output that allows you to verify correct computation of the program for subsequent optimization steps (try to avoid overflows). Compile this program on LCC3 with `gcc 12.2.0` using `-O1` and measure the execution time **of the computation only** for several problem sizes (=vector lengths). This sequential program is our baseline reference.

# Task 3

> Try to use auto-vectorization in the compiler to vectorize the computation. Investigate which flag(s) to use for that, and try to limit your compiler change to only enable vectorization but not any other optimizations. Measure the execution time for the same problem sizes as before and compute the respective speedups. What can you observe in terms of performance? Is the result still correct? Does varying the problem size affect the performance gain or loss?

# Task 4

> Use `perf` to further investigate the origin of any performance difference you might observe. `perf stat -e rYYXX` (mind the order of X and Y!) allows you to measure custom events supported by the CPU, where - on Intel systems - XX is the so-called _event code_ and YY is the so-called _unit mask_ (also called _umask_). A few event codes and unit masks for measuring vectorized instructions are given below. Check which ones are suitable for your investigation:

  | Name                                 | Event Code | Unit Mask |
  |--------------------------------------|:----------:|:---------:|
  | FP_COMP_OPS_EXE.X87                  |     10     |    01     |
  | FP_COMP_OPS_EXE.MMX                  |     10     |    02     |
  | FP_COMP_OPS_EXE.SSE_FP               |     10     |    04     |
  | FP_COMP_OPS_EXE.SSE2_INTEGER         |     10     |    08     |
  | FP_COMP_OPS_EXE.SSE_FP_PACKED        |     10     |    10     |
  | FP_COMP_OPS_EXE.SSE_FP_SCALAR        |     10     |    20     |
  | FP_COMP_OPS_EXE.SSE_SINGLE_PRECISION |     10     |    40     |
  | FP_COMP_OPS_EXE.SSE_DOUBLE_PRECISION |     10     |    80     |

# Task 5

> Enter the wall clock time of the sequential program and the auto-vectorized version with size 2048 and 1e6 repetitions to the spreadsheet linked on Discord.