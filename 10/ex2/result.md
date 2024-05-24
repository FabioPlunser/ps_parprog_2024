# Task 1

> Given the code in [heat_stencil_2D.c](heat_stencil_2D.c), finish the implementation:
>  - implement the heat propagation by updating each cell with information from its neighbors. If in doubt, you can start with the formula given in https://en.wikipedia.org/wiki/Finite_difference_method#Example:_The_Laplace_operator
>  - make sure the heat source stays the same through all iterations
>  - if computing the value at the boundary, use temperature at the center position as the next value (e.g if you want to calculate A[0,1], use A[0,1] as the left neighbor cell instead of the non-existent A[-1,1])
>  - The simple verification at the end should pass



# Task 2

> Parallelize the implementation using OpenMP. Investigate the use of the `collapse` clause and explain its purpose and effects.



# Task 3

> Measure the time, speedup and efficiency of the stencil codes for varying problem sizes and numbers of threads.



# Task 4

> Enter the wall clock time of the sequential version and the parallel version for 1 and 12 threads for 500x500 on LCC3 to the comparison spreadsheet linked on Discord.

