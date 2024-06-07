# Description

For each loop iteration instructions such as compare and add operations have to be performed. If the number of executions is sufficiently large this can have an impact on the performance of the program. Investigate the following given code examples along with their task and, for each example, study why the transformation may or may not be beneficial. \
Furthermore, for each example, you are asked to compare the performance counters of the original and the transformed code. Therefore, you should create a small test program for each configuration, compile it with `gcc` using `-O3`, and profile it with `perf` on LCC3.
Note that if not stated otherwise, variables and array elements are of type `int`.

# Task 1

> Apply loop unrolling. Note that you can assume that `N` is odd.

```C
for (int i = 0; i < N - 1; ++i) {
    a[i] = b[i] + b[i + 1];
}
```


# Task 2

> Apply loop-invariant code motion (`a` is of type `double *`):

```C
for (int i = 0; i < N; ++i) {
    a[i] *= hypot(0.3, 0.4);
}
```


# Task 3

> Apply loop unswitching:

```C
for (int i = 0; i < N; ++i) {
    if (N % 2) {
        a[i] = b[i] + 5;
    } else {
        a[i] = c[i] + 5;
    }
}
```


# Task 4

> Apply loop fission/distribution. Does this transformation impact the number of cache misses?

```C
for (int i = 0; i < N; ++i) {
    sum_a += a[i];
    sum_b += b[i];
    sum_c += c[i];
}
```


# Task 5

> Apply loop peeling and loop fusion/combination. Note that `N` is larger than `0`.

```C
int min = a[0];
for (int i = 1; i < N; ++i) {
    min = (a[i] < min) ? a[i] : min;
}
for (int i = 0; i < N; ++i) {
    sum += a[i];
}
```


# Task 6

> Apply loop splitting:

```C
for (int i = 0; i < N; ++i) {
    if (i % 2) {
        a[i] = b[i] + 4;
    } else {
        a[i] = c[i] + 5;
    }
}
```


# Task 7

> Apply loop tiling (`a`, `b`, and `c` are of type `double`). You can assume that a macro `BLOCK_SIZE`, which is defined in some boilerplate code, defines a suitable block size for tiling (e.g., `#define BLOCK_SIZE 64 / sizeof(double)`). \

```C
for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
        for (int k = 0; k < N; ++k) {
            c[i][j] = a[i][k] * b[k][j];
        }
    }
}
```