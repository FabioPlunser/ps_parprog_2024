# Description

This exercise consists of implementing a 2-dimensional heat stencil application.

A large class of scientific applications are so-called stencil or structured grid applications. These simulate time-dependent physical processes such as the propagation of heat or pressure in a given medium. The core of the simulation operates on a grid and updates each cell with information from its neighbor cells.

# Task 1

> Given the code in [heat_stencil_2D.c](heat_stencil_2D.c), finish the implementation:
>  - implement the heat propagation by updating each cell with information from its neighbors. If in doubt, you can start with the formula given in https://en.wikipedia.org/wiki/Finite_difference_method#Example:_The_Laplace_operator
>  - make sure the heat source stays the same through all iterations
>  - if computing the value at the boundary, use temperature at the center position as the next value (e.g if you want to calculate A[0,1], use A[0,1] as the left neighbor cell instead of the non-existent A[-1,1])
>  - The simple verification at the end should pass

Done. See [heat_stencil_2D_seq.c](./heat_stencil_2D_seq.c)

# Task 2

> Parallelize the implementation using OpenMP. Investigate the use of the `collapse` clause and explain its purpose and effects.

Done. See [heat_stencil_2D_par.c](./heat_stencil_2D_par.c)

The collapse clause in OpenMP merges multiple loops into a single loop to improve parallelization efficiency by exposing more parallelism. The collapse(2) clause is used here to collapse the two nested loops over x and y into a single iteration space, making it possible to parallelize them effectively.


# Task 3

> Measure the time, speedup and efficiency of the stencil codes for varying problem sizes and numbers of threads.

![Heat Stencil 2D (N=200).png](./results/Heat%20Stencil%202D%20(N=200).png)

| num_threads | heat_stencil_2D_seq-200 | heat_stencil_2D_par-200 | Speedup | Efficiency |
|---|---|---|---|---|
| 1 | 0.298s | 0.454s | 0.656 | 0.656 |
| 2 | 0.299s | 0.228s | 1.311 | 0.656 |
| 4 | 0.311s | 0.126s | 2.468 | 0.617 |
| 6 | 0.304s | 0.084s | 3.619 | 0.603 |
| 10 | 0.299s | 0.057s | 5.246 | 0.525 |
| 12 | 0.317s | 0.073s | 4.342 | 0.362 |


![Heat Stencil 2D (N=500).png](./results/Heat%20Stencil%202D%20(N=500).png)

| num_threads | heat_stencil_2D_seq-500 | heat_stencil_2D_par-500 | Speedup | Efficiency |
|---|---|---|---|---|
| 1 | 4.683s | 7.017s | 0.668 | 0.668 |
| 2 | 4.620s | 3.588s | 1.288 | 0.644 |
| 4 | 4.632s | 1.803s | 2.569 | 0.642 |
| 6 | 4.665s | 1.250s | 3.732 | 0.622 |
| 10 | 4.619s | 0.834s | 5.538 | 0.554 |
| 12 | 4.645s | 0.766s | 6.064 | 0.505 |

# Task 4

> Enter the wall clock time of the sequential version and the parallel version for 1 and 12 threads for 500x500 on LCC3 to the comparison spreadsheet linked on Discord.

Done.