# Task 1

> Review the pthreads-based implementation provided in [monte_carlo_pi/mc_pi_pthreads.c](monte_carlo_pi/mc_pi_pthreads.c). Benchmark it with 1, 2, 4, 6, and 12 threads on LCC3. What can you observe?

The execution time seems to scale inversely proportional to the number of threads.

# Task 2+3

> Implement parallel versions of this approximation using OpenMP. In total, three different versions using the following OpenMP constructs should be provided:
>   1) `critical` section
>   2) `atomic` statement
>   3) `reduction` clause

> To increase the performance difference among these versions, make sure you increment the samples counter directly, without aggregating to private variables first.