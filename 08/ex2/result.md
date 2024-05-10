# Task 1

> Implement a parallel version of the Hadamard product using OpenMP. Use the snippet below as sequential implementation.

Snippet to use: 
```c
for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
        c[i][j] = a[i][j] * b[i][j];
    }
}
```

See:
- [hadamard_parallel_static](./hadamard_parallel_static.c)
- [hadamard_parallel_dynamic](./hadamard_parallel_dynamic.c)
- [hadamard_parallel_guided](./hadamard_parallel_guided.c)
- [hadamard_parallel_auto](./hadamard_parallel_auto.c)
- [hadamard_parallel_runtime](./hadamard_parallel_runtime.c)

# Task 2

> Benchmark your serial implementations and your parallel implementations with 1, 2, 4, 6 and 12 threads on LCC3 using N=10.000², 20.000² and 30.000². Use OpenMP's time measurement function to measure only the computational loop.

Execute benchmark by running: `make bench_all`

Plot results by running: `make result`

## Benchmark for N=10.000²

![benchmark](./results/10000/Hadamard%20N=10000².png)

| num_threads | hadamard_parallel_static | hadamard_serial | hadamard_parallel_guided | hadamard_parallel_auto | hadamard_parallel_runtime | hadamard_parallel_dynamic |
|---|---|---|---|---|---|---|
| 1 | 0.040s | 0.040s | 0.040s | 0.040s | 0.041s | 0.039s |
| 2 | 0.027s | 0.039s | 0.027s | 0.027s | 0.031s | 0.032s |
| 4 | 0.020s | 0.042s | 0.018s | 0.019s | 0.028s | 0.028s |
| 6 | 0.018s | 0.043s | 0.019s | 0.018s | 0.030s | 0.030s |
| 12 | 0.015s | 0.043s | 0.018s | 0.015s | 0.053s | 0.053s |

## Benchmark for N=20.000²

![benchmark](./results/20000/Hadamard%20N=20000².png)

| num_threads | hadamard_parallel_static | hadamard_serial | hadamard_parallel_guided | hadamard_parallel_auto | hadamard_parallel_runtime | hadamard_parallel_dynamic |
|---|---|---|---|---|---|---|
| 1 | 0.155s | 0.156s | 0.156s | 0.156s | 0.155s | 0.152s |
| 2 | 0.105s | 0.157s | 0.103s | 0.102s | 0.121s | 0.124s |
| 4 | 0.073s | 0.175s | 0.071s | 0.076s | 0.103s | 0.103s |
| 6 | 0.056s | 0.172s | 0.058s | 0.067s | 0.117s | 0.113s |
| 12 | 0.067s | 0.168s | 0.059s | 0.066s | 0.215s | 0.241s |

## Benchmark for N=30.000²

![benchmark](./results/30000/Hadamard%20N=30000².png)

| num_threads | hadamard_parallel_static | hadamard_serial | hadamard_parallel_guided | hadamard_parallel_auto | hadamard_parallel_runtime | hadamard_parallel_dynamic |
|---|---|---|---|---|---|---|
| 1 | 0.344s | 0.345s | 0.348s | 0.350s | 0.350s | 0.353s |
| 2 | 0.241s | 0.349s | 0.242s | 0.245s | 0.287s | 0.289s |
| 4 | 0.132s | 0.362s | 0.135s | 0.135s | 0.239s | 0.268s |
| 6 | 0.129s | 0.377s | 0.144s | 0.153s | 0.256s | 0.259s |
| 12 | 0.130s | 0.376s | 0.132s | 0.152s | 0.555s | 0.538s |

## Benchmark for N=65.536²

![benchmark](./results/65536/Hadamard%20N=65536².png)

| num_threads | hadamard_parallel_static | hadamard_serial | hadamard_parallel_guided | hadamard_parallel_auto | hadamard_parallel_runtime | hadamard_parallel_dynamic |
|---|---|---|---|---|---|---|
| 1 | 1.672s | 1.674s | 1.705s | 2.506s | 2.551s | 1.707s |
| 2 | 1.213s | 2.363s | 1.214s | 1.196s | 1.158s | 1.402s |
| 4 | 0.649s | 1.893s | 0.716s | 0.652s | 1.115s | 1.123s |
| 6 | 0.605s | 1.884s | 0.669s | 0.611s | 1.276s | 1.261s |
| 12 | 0.607s | 1.925s | 0.620s | 0.605s | 2.652s | 2.660s |

# Task 3

> Use the 3 loop scheduling methods discussed in the lecture, `static`, `dynamic` and `guided`. Explain their differences and compare their performance for the two code snippets. What can you observe?

All explanations from https://www.ibm.com/docs/en/xl-c-aix/13.1.3?topic=processing-pragma-omp. 

**static**

> Iterations of a loop are divided into chunks of size ceiling(number_of_iterations/number_of_threads). Each thread is assigned a separate chunk.
This scheduling policy is also known as block scheduling.

As each iteration causes about the same computational effort, static scheduling is fastest, because it creates the lowest overhead.

**dynamic**

> Iterations of a loop are divided into chunks of size ceiling(number_of_iterations/number_of_threads).
Chunks are dynamically assigned to active threads on a "first-come, first-do" basis until all work has been assigned.

The overhead of assigning chunks at runtime makes the program slow down with an increasing number of threads.

**guided**

> Chunks are made progressively smaller until the default minimum chunk size is reached. The first chunk is of size ceiling(number_of_iterations/number_of_threads). Remaining chunks are of size ceiling(number_of_iterations_left/number_of_threads).
The minimum chunk size is 1.
Chunks are assigned to active threads on a "first-come, first-do" basis until all work has been assigned.

Performs almost as good as static scheduling.

# Task 4

> In addition, try the loop scheduling methods `auto` and `runtime`. What do they do, what can you observe?

All explanations from https://www.ibm.com/docs/en/xl-c-aix/13.1.3?topic=processing-pragma-omp. 

**auto**

> With auto, scheduling is delegated to the compiler and runtime system. The compiler and runtime system can choose any possible mapping of iterations to threads (including all possible valid schedules) and these may be different in different loops.

Seems to perform as well as static scheduling (probably also leads to the same mapping). Overhead very high number of iterations possible.

**runtime**

> Scheduling policy is determined at run time. Use the OMP_SCHEDULE environment variable to set the scheduling type and chunk size. 

High overhead at runtime, therefore bad performance. Seems to be identical to dynamic scheduling.

# Task 5

> Enter the time for N=65.536² into the comparison spreadsheet linked on Discord.

Done.