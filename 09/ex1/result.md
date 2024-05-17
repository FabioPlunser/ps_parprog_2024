# Task 1

> Write a sequential program that computes `a[i] += b[i] * c[i]` for three `float` vectors `a`, `b`, and `c`. Enclose this computation in a loop such that it is repeated `1e6` times. I.e. your code should look like this:

```
for(int run = 0; run < repetitions; ++run) {
    for(int i = 0; i < size; ++i) {
        a[i] += b[i] * c[i];
    }
}
```

Done. See [sequential.c](./sequential.c).

# Task 2

> Initialize the vectors with constant values and add some output that allows you to verify correct computation of the program for subsequent optimization steps (try to avoid overflows). Compile this program on LCC3 with `gcc 12.2.0` using `-O1` and measure the execution time **of the computation only** for several problem sizes (=vector lengths). This sequential program is our baseline reference.

- Initializing with random values from interval [0,2).
- Verification by summing up final values in vector a
- Activate gcc 12.2.0 by running `module load gcc/12.2.0-gcc-8.5.0-p4pe45v`

See task 3 for execution time results.

# Task 3

> Try to use auto-vectorization in the compiler to vectorize the computation. Investigate which flag(s) to use for that, and try to limit your compiler change to only enable vectorization but not any other optimizations. Measure the execution time for the same problem sizes as before and compute the respective speedups. What can you observe in terms of performance? Is the result still correct? Does varying the problem size affect the performance gain or loss?

- Build non-vectorized and vectorized version by running `make all`
- Benchmark both versions with `make bench_all`
- Calculated speedup as execution time without vectorization divided by execution time with vectorization

| num_threads | sequential | sequential_vectorized | speedup |
|---|---|---|---|
| 16 | 0.016s | 0.005s | 3.200 |
| 32 | 0.032s | 0.009s | 3.556 |
| 64 | 0.064s | 0.017s | 3.765 |
| 128 | 0.170s | 0.033s | 5.152 |
| 256 | 0.338s | 0.064s | 5.281 |
| 512 | 0.672s | 0.134s | 5.015 |
| 1024 | 1.342s | 0.259s | 5.181 |
| 2048 | 2.677s | 0.510s | 5.249 |
| 4096 | 5.377s | 1.600s | 3.361 |
| 8192 | 10.758s | 3.236s | 3.324 |

Results verified and still correct.

There seems to be a range of problem sizes that profits the most from vectorization. Below a certain limit and after a certain limit, speedup seems to decrease.

# Task 4

> Use `perf` to further investigate the origin of any performance difference you might observe. `perf stat -e rYYXX` (mind the order of X and Y!) allows you to measure custom events supported by the CPU, where - on Intel systems - XX is the so-called _event code_ and YY is the so-called _unit mask_ (also called _umask_).


Execute `make perf_all` to measure the performance of both vectorized and non-vectorized program with a vector size of 2048 each.

| event | non-vectorized | vectorized | explanation | remark |
|---|---|---|---|---|
| FP_COMP_OPS_EXE.X87 | 3,486 | 741 | Counts the number of floating-point operations executed by the x87 floating-point unit. | Does not seem relevant as x87 floating point instructions are not really used anymore. |
| FP_COMP_OPS_EXE.MMX | 0 | 0 | Counts the number of MMX instructions executed. | Does not seem relevant as MMX instructions are not really used anymore. |
| FP_COMP_OPS_EXE.SSE_FP | 4,090,621,574 | 1,020,645,777 | Counts the number of SSE (Streaming Single Instruction, Multiple Data Extensions) floating-point operations. | Relevant but no difference, as it counts the overall floating point instructions mainly used within the programs. |
| FP_COMP_OPS_EXE.SSE2_INTEGER | 32,566 | 12,083 | Counts the number of integer SSE2 instructions executed. | Does not seem relevant as major number of operations within programs are on floating point numbers. 
| FP_COMP_OPS_EXE.SSE_FP_PACKED | 0 | 1,022,338,138 | Counts the number of packed (multiple data in single operation) single-precision floating-point SSE instructions. | **Very relevant** as it shows that auto-vectorization combines multiple data into single instructions. This is not the case on the non-vectorized version. |
| FP_COMP_OPS_EXE.SSE_FP_SCALAR | 4,099,363,382 | 24,535 | Counts the number of scalar (single data in single instruction) single-precision floating-point SSE instructions. | **Very relevant** as it shows that the non-vectorized program uses a single instruction for every single operation |
| FP_COMP_OPS_EXE.SSE_SINGLE_PRECISION | 4,101,462,815 | 1,027,384,119 | Counts the number of single-precision floating-point operations executed. | Relevant but no difference, as it counts the overall floating point instructions mainly used within the programs. When switching to `double` values this should almost reduce to zero. |
| FP_COMP_OPS_EXE.SSE_DOUBLE_PRECISION | 0 | 8,203 | Counts the number of double-precision floating-point operations executed. | Does not seem relevant, as there are not distinct operations on `double` type variables in the program. Auto-vectorization seems to introduce at least some double precision operations. |

The main performance improvement seems to stem from using single instructions for multiple data in the vectorized version. This allows the program to execute with less overall instructions on the CPU.

# Task 5

> Enter the wall clock time of the sequential program and the auto-vectorized version with size 2048 and 1e6 repetitions to the spreadsheet linked on Discord.

TODO