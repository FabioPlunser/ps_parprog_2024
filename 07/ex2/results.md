# Description
> Compilers often perform dependence analysis as a pre-step in order to safely perform optimizations such as vectorization in a second step. In this exercise, we will look at the first step only, namely compiler capabilities and reporting.

# Task 1
> Compile the given program [analysis.c](analysis.c) with gcc 12.2.0 (`module load  gcc/12.2.0-gcc-8.5.0-p4pe45v`) and the flags `-O2 -ftree-vectorize -fopt-info-vec-all-internals`.




# Task 2
> Examine the output. What information about dependence analysis can you find in the output? Can you identify any information pointing to successful or unsuccessful vectorization? Does the compiler perform any analysis beyond checking for dependencies and semantic correctness? What are your findings?