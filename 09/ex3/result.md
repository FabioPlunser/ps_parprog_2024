# Task 1

> Vectorize your code for `float` types using the gcc-specific intrinsic functions `_mm_load_ps`, `_mm_add_ps`, `_mm_mul_ps`, and `_mm_store_ps`. Do not forget to include the respective header `xmmintrin.h`.

- `_mm_load_ps` Loads a 128-bit floating-point vector of [4 x float] from an aligned memory location. 
- `_mm_add_ps` Adds two 128-bit vectors of [4 x float], and returns the results of the addition. 
- `_mm_mul_ps` Multiplies two 128-bit vectors of [4 x float] and returns the results of the multiplication.
- `_mm_store_ps` Stores a 128-bit vector of [4 x float] into an aligned memory location.  
Done. See [sequential_vectorized.c](./sequential_vectorized.c).

# Task 2

> Compile your manually vectorized code with `-O1` but without any compiler flags for auto-vectorization and compare its performance for your set of problem sizes to your previous code versions. What can you observe? Is the result still correct?

- Activate gcc 12.2.0 by running `module load gcc/12.2.0-gcc-8.5.0-p4pe45v`
- Build non-vectorized and vectorized version by running `make all`
- Benchmark both versions with `make bench_all`
- Calculated speedup as execution time without vectorization divided by execution time with vectorization(Same as in Exercise 1)  

| size | sequential | sequential_vectorized | speedup |
| ---- | ---------- | --------------------- | ------- |
| 16   | 0.016s     | 0.005s                | 0.011s  |
| 32   | 0.032s     | 0.010s                | 0.022s  |
| 64   | 0.063s     | 0.019s                | 0.044s  |
| 128  | 0.171s     | 0.035s                | 0.136s  |
| 256  | 0.338s     | 0.066s                | 0.272s  |
| 512  | 0.673s     | 0.171s                | 0.502s  |
| 1024 | 1.344s     | 0.339s                | 1.005s  |
| 2048 | 2.690s     | 0.673s                | 2.017s  |
| 4096 | 5.358s     | 1.611s                | 3.747s  |
| 8192 | 10.718s    | 3.261s                | 7.457s  |

Results verified and still correct.

# Task 3

> Verify any findings using `perf` as described in Exercise 1.

Execute `make perf_all` to measure the performance of both vectorized and non-vectorized program with a vector size of 2048 each. (Same tables as in Exercise 1 with updated values)

| event                                | non-vectorized | vectorized    | explanation                                                                                                         | remark                                                                                                                                                                                   |
| ------------------------------------ | -------------- | ------------- | ------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| FP_COMP_OPS_EXE.X87                  | 2,189          | 3,419         | Counts the number of floating-point operations executed by the x87 floating-point unit.                             | Does not seem relevant as x87 floating point instructions are not really used anymore.                                                                                                   |
| FP_COMP_OPS_EXE.MMX                  | 0              | 0             | Counts the number of MMX instructions executed.                                                                     | Does not seem relevant as MMX instructions are not really used anymore.                                                                                                                  |
| FP_COMP_OPS_EXE.SSE_FP               | 4,096,701,278  | 1,021,263,753 | Counts the number of SSE (Streaming Single Instruction, Multiple Data Extensions) floating-point operations.        | Relevant but no difference, as it counts the overall floating point instructions mainly used within the programs.                                                                        |
| FP_COMP_OPS_EXE.SSE2_INTEGER         | 26,854         | 30,716        | Counts the number of integer SSE2 instructions executed.                                                            | Does not seem relevant as major number of operations within programs are on floating point numbers.                                                                                      |
| FP_COMP_OPS_EXE.SSE_FP_PACKED        | 0              | 1,026,374,510 | Counts the number of packed (multiple data in single instruction) single-precision floating-point SSE instructions. | **Very relevant** as it shows that auto-vectorization combines multiple data into single instructions. This is not the case on the non-vectorized version.                               |
| FP_COMP_OPS_EXE.SSE_FP_SCALAR        | 4,094,019,687  | 0         | Counts the number of scalar (single data in single instruction) single-precision floating-point SSE instructions.   | **Very relevant** as it shows that the non-vectorized program uses a single instruction for every single operation                                                                       |
| FP_COMP_OPS_EXE.SSE_SINGLE_PRECISION | 4,095,375,374  | 1,026,806,561 | Counts the number of single-precision floating-point operations executed.                                           | Relevant but no difference, as it counts the overall floating point instructions mainly used within the programs. When switching to `double` values this should almost reduce to zero.   |
| FP_COMP_OPS_EXE.SSE_DOUBLE_PRECISION | 7,254          | 0             | Counts the number of double-precision floating-point operations executed.                                           | Does not seem relevant, as there are not distinct operations on `double` type variables in the program. Auto-vectorization seems to introduce at least some double precision operations. |

# Task 4

> How does the solution for this Exercise compare to Exercise 2 and Exercise 1? Are there any advantages or disadvantages?

#### Comparison
- The User is responsible for the alignment of the memory.(using _mm_malloc)
- If the number of elements is not a multiple of 4, the user has to handle the remaining elements in a separate loop.

#### Advantages
- More control over the vectorization process.

#### Disadvantages
- More error-prone.
- More verbose.
- More difficult to maintain.

# Task 5

> Enter the wall clock time of the compiler-specific intrinsics version with size 2048 and 1e6 repetitions to the spreadsheet linked on Discord.
