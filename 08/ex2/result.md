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

# Task 2

> Benchmark your serial implementations and your parallel implementations with 1, 2, 4, 6 and 12 threads on LCC3 using N=10.000², 20.000² and 30.000². Use OpenMP's time measurement function to measure only the computational loop.

# Task 3

> Use the 3 loop scheduling methods discussed in the lecture, `static`, `dynamic` and `guided`. Explain their differences and compare their performance for the two code snippets. What can you observe?

# Task 4

> In addition, try the loop scheduling methods `auto` and `runtime`. What do they do, what can you observe?

# Task 5

> Enter the time for N=65.536² into the comparison spreadsheet linked on Discord.