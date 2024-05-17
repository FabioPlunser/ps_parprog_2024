# Task 1

> Vectorize your code for `float` types using the gcc-specific intrinsic functions `_mm_load_ps`, `_mm_add_ps`, `_mm_mul_ps`, and `_mm_store_ps`. Do not forget to include the respective header `xmmintrin.h`.

# Task 2

> Compile your manually vectorized code with `-O1` but without any compiler flags for auto-vectorization and compare its performance for your set of problem sizes to your previous code versions. What can you observe? Is the result still correct?

# Task 3

> Verify any findings using `perf` as described in Exercise 1.

# Task 4

> How does the solution for this Exercise compare to Exercise 2 and Exercise 1? Are there any advantages or disadvantages?

# Task 5

> Enter the wall clock time of the compiler-specific intrinsics version with size 2048 and 1e6 repetitions to the spreadsheet linked on Discord.