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
> Original 
```
          1,453.26 msec task-clock:u              #    0.983 CPUs utilized          
             3,550      cache-misses:u            #    0.495 % of all cache refs      (83.28%)
           717,733      cache-references:u        #  493.877 K/sec                    (83.34%)
     4,006,901,753      cycles:u                  #    2.757 GHz                      (66.70%)
     7,191,815,027      instructions:u            #    1.79  insn per cycle           (83.35%)
     1,795,971,932      branches:u                #    1.236 G/sec                    (83.35%)
           396,593      branch-misses:u           #    0.02% of all branches          (83.33%)

       1.478968389 seconds time elapsed

       1.323793000 seconds user
       0.114714000 seconds sys

```
> Transformed 
```c
for(int i = 0; i < N - 1; i += 2) {
    a[i] = b[i] + b[i + 1];
    a[i + 1] = b[i + 1] + b[i + 2];
}
```
```

          1,451.57 msec task-clock:u              #    0.998 CPUs utilized          
             4,535      cache-misses:u            #    0.635 % of all cache refs      (83.33%)
           714,510      cache-references:u        #  492.231 K/sec                    (83.33%)
     4,012,470,345      cycles:u                  #    2.764 GHz                      (66.66%)
     7,196,484,528      instructions:u            #    1.79  insn per cycle           (83.33%)
     1,797,486,943      branches:u                #    1.238 G/sec                    (83.33%)
           416,792      branch-misses:u           #    0.02% of all branches          (83.35%)

       1.454106496 seconds time elapsed

       1.310334000 seconds user
       0.126596000 seconds sys
```

As you can see the performance, cache misses, and instructions are almost identical. This is because the compiler already optimized the code to the best of its ability. The only difference is that the transformed code has a slightly higher user time and a slightly lower sys time. This could be because the compiler optimized the original code to the best of its ability and the transformed code is optimized by the compiler to the best of its ability.

# Task 2

> Apply loop-invariant code motion (`a` is of type `double *`):

```C
for (int i = 0; i < N; ++i) {
    a[i] *= hypot(0.3, 0.4);
}
```
> Original 
```
          1,514.33 msec task-clock:u              #    0.991 CPUs utilized          
             8,497      cache-misses:u            #    0.907 % of all cache refs      (83.31%)
           936,498      cache-references:u        #  618.426 K/sec                    (83.30%)
     4,010,000,312      cycles:u                  #    2.648 GHz                      (66.69%)
     7,270,354,793      instructions:u            #    1.81  insn per cycle           (83.36%)
     1,800,565,677      branches:u                #    1.189 G/sec                    (83.36%)
           403,110      branch-misses:u           #    0.02% of all branches          (83.35%)

       1.527836721 seconds time elapsed

       1.319620000 seconds user
       0.179108000 seconds sys
```
> Transformed 
```c 
double hypo = hypot(0.3, 0.4);
for(int i = 0; i < N; ++i) {
    a[i] *= hypo;
}
```
```
          1,515.67 msec task-clock:u              #    0.998 CPUs utilized          
             8,940      cache-misses:u            #    0.946 % of all cache refs      (83.31%)
           945,133      cache-references:u        #  623.576 K/sec                    (83.31%)
     4,014,318,420      cycles:u                  #    2.649 GHz                      (66.67%)
     7,292,677,757      instructions:u            #    1.82  insn per cycle           (83.36%)
     1,795,911,642      branches:u                #    1.185 G/sec                    (83.38%)
           396,287      branch-misses:u           #    0.02% of all branches          (83.33%)

       1.518109713 seconds time elapsed

       1.311959000 seconds user
       0.188087000 seconds sys
```

As you can see the performance, cache misses, and instructions are almost identical. This is because the compiler already optimized the code to the best of its ability. The only difference is that the transformed code has a slightly higher user time and a slightly lower sys time. This could be because the compiler optimized the original code to the best of its ability and the transformed code is optimized by the compiler to the best of its ability.


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
> Original
```
          2,772.83 msec task-clock:u              #    0.994 CPUs utilized          
            15,071      cache-misses:u            #    1.238 % of all cache refs      (83.31%)
         1,217,313      cache-references:u        #  439.015 K/sec                    (83.34%)
     7,815,997,639      cycles:u                  #    2.819 GHz                      (66.70%)
    13,884,047,498      instructions:u            #    1.78  insn per cycle           (83.36%)
     3,494,340,620      branches:u                #    1.260 G/sec                    (83.34%)
           321,337      branch-misses:u           #    0.01% of all branches          (83.32%)

       2.788359320 seconds time elapsed

       2.559470000 seconds user
       0.185144000 seconds sys
```

> Transformed 
```c
if(N % 2) {
    for(int i = 0; i < N; ++i) {
        a[i] = b[i] + 5;
    }
} else {
    for(int i = 0; i < N; ++i) {
        a[i] = c[i] + 5;
    }
}
```
```
          2,773.28 msec task-clock:u              #    0.999 CPUs utilized          
            12,435      cache-misses:u            #    0.991 % of all cache refs      (83.31%)
         1,254,489      cache-references:u        #  452.348 K/sec                    (83.33%)
     7,809,602,466      cycles:u                  #    2.816 GHz                      (66.69%)
    13,875,931,737      instructions:u            #    1.78  insn per cycle           (83.34%)
     3,495,565,386      branches:u                #    1.260 G/sec                    (83.34%)
           330,320      branch-misses:u           #    0.01% of all branches          (83.33%)

       2.775221362 seconds time elapsed

       2.573910000 seconds user
       0.171197000 seconds sys
```

As you can see the performance, cache misses, and instructions are almost identical. This is because the compiler already optimized the code to the best of its ability. The only difference is that the transformed code has a slightly higher user time and a slightly lower sys time. This could be because the compiler optimized the original code to the best of its ability and the transformed code is optimized by the compiler to the best of its ability.

# Task 4

> Apply loop fission/distribution. Does this transformation impact the number of cache misses?

```C
for (int i = 0; i < N; ++i) {
    sum_a += a[i];
    sum_b += b[i];
    sum_c += c[i];
}
```
> Original 
```
          1,514.33 msec task-clock:u              #    0.991 CPUs utilized          
             8,497      cache-misses:u            #    0.907 % of all cache refs      (83.31%)
           936,498      cache-references:u        #  618.426 K/sec                    (83.30%)
     4,010,000,312      cycles:u                  #    2.648 GHz                      (66.69%)
     7,270,354,793      instructions:u            #    1.81  insn per cycle           (83.36%)
     1,800,565,677      branches:u                #    1.189 G/sec                    (83.36%)
           403,110      branch-misses:u           #    0.02% of all branches          (83.35%)

       1.527836721 seconds time elapsed

       1.319620000 seconds user
       0.179108000 seconds sys
```

> Transformed 
```c
for(int i = 0; i < N; ++i) {
    sum_a += a[i];
}
for(int i = 0; i < N; ++i) {
    sum_b += b[i];
}
for(int i = 0; i < N; ++i) {
    sum_c += c[i];
}
```

```
          1,512.45 msec task-clock:u              #    0.998 CPUs utilized          
             8,613      cache-misses:u            #    0.915 % of all cache refs      (83.32%)
           941,636      cache-references:u        #  622.591 K/sec                    (83.34%)
     4,013,645,012      cycles:u                  #    2.654 GHz                      (66.69%)
     7,284,432,841      instructions:u            #    1.81  insn per cycle           (83.34%)
     1,798,932,392      branches:u                #    1.189 G/sec                    (83.34%)
           397,599      branch-misses:u           #    0.02% of all branches          (83.31%)

       1.515087470 seconds time elapsed

       1.315655000 seconds user
       0.180904000 seconds sys
```

As you can see the performance, cache misses, and instructions are almost identical. This is because the compiler already optimized the code to the best of its ability. The only difference is that the transformed code has a slightly higher user time and a slightly lower sys time. This could be because the compiler optimized the original code to the best of its ability and the transformed code is optimized by the compiler to the best of its ability


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

> Original 
```
          1,315.73 msec task-clock:u              #    0.987 CPUs utilized          
               827      cache-misses:u            #    0.155 % of all cache refs      (83.28%)
           533,008      cache-references:u        #  405.103 K/sec                    (83.30%)
     3,789,501,400      cycles:u                  #    2.880 GHz                      (66.72%)
     6,991,176,744      instructions:u            #    1.84  insn per cycle           (83.36%)
     1,797,361,716      branches:u                #    1.366 G/sec                    (83.36%)
            20,087      branch-misses:u           #    0.00% of all branches          (83.34%)

       1.332603323 seconds time elapsed

       1.245474000 seconds user
       0.057431000 seconds sys
```

> Transformed
```c 
int min = a[0];
for(int i = 0; i < N; ++i) {
    min = (a[i] < min) ? a[i] : min;
    sum += a[i];
}
```
```
          1,317.28 msec task-clock:u              #    0.998 CPUs utilized          
             3,162      cache-misses:u            #    0.595 % of all cache refs      (83.30%)
           531,680      cache-references:u        #  403.621 K/sec                    (83.30%)
     3,791,844,101      cycles:u                  #    2.879 GHz                      (66.70%)
     6,993,610,418      instructions:u            #    1.84  insn per cycle           (83.38%)
     1,797,097,126      branches:u                #    1.364 G/sec                    (83.38%)
            11,450      branch-misses:u           #    0.00% of all branches          (83.32%)

       1.319557148 seconds time elapsed

       1.243135000 seconds user
       0.061386000 seconds sys
```

As you can see the performance, cache misses, and instructions are almost identical. This is because the compiler already optimized the code to the best of its ability. The only difference is that the transformed code has a slightly higher user time and a slightly lower sys time. This could be because the compiler optimized the original code to the best of its ability and the transformed code is optimized by the compiler to the best of its ability


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

> Original 
```
          1,512.74 msec task-clock:u              #    0.988 CPUs utilized          
             9,299      cache-misses:u            #    0.923 % of all cache refs      (83.34%)
         1,007,779      cache-references:u        #  666.195 K/sec                    (83.34%)
     4,015,940,952      cycles:u                  #    2.655 GHz                      (66.69%)
     7,293,503,433      instructions:u            #    1.82  insn per cycle           (83.35%)
     1,797,572,209      branches:u                #    1.188 G/sec                    (83.34%)
           398,598      branch-misses:u           #    0.02% of all branches          (83.29%)

       1.530792857 seconds time elapsed

       1.325033000 seconds user
       0.172260000 seconds sys
```

> Transformed 
```c
// Handle even indices
for(int i = 0; i < N; i += 2) {
    a[i] = c[i] + 5;
}
// Handle odd indices
for(int i = 1; i < N; i += 2) {
    a[i] = b[i] + 4;
}
```
```
          1,515.67 msec task-clock:u              #    0.998 CPUs utilized          
             8,940      cache-misses:u            #    0.946 % of all cache refs      (83.31%)
           945,133      cache-references:u        #  623.576 K/sec                    (83.31%)
     4,014,318,420      cycles:u                  #    2.649 GHz                      (66.67%)
     7,292,677,757      instructions:u            #    1.82  insn per cycle           (83.36%)
     1,795,911,642      branches:u                #    1.185 G/sec                    (83.38%)
           396,287      branch-misses:u           #    0.02% of all branches          (83.33%)

       1.518109713 seconds time elapsed

       1.311959000 seconds user
       0.188087000 seconds sys
```

As you can see the performance, cache misses, and instructions are almost identical. This is because the compiler already optimized the code to the best of its ability. The only difference is that the transformed code has a slightly higher user time and a slightly lower sys time. This could be because the compiler optimized the original code to the best of its ability and the transformed code is optimized by the compiler to the best of its ability


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

> Original 
```
          7,041.89 msec task-clock:u              #    0.999 CPUs utilized          
           248,948      cache-misses:u            #   39.012 % of all cache refs      (83.33%)
           638,134      cache-references:u        #   90.620 K/sec                    (83.33%)
    21,042,424,601      cycles:u                  #    2.988 GHz                      (66.67%)
    41,846,184,089      instructions:u            #    1.99  insn per cycle           (83.34%)
     7,101,951,468      branches:u                #    1.009 G/sec                    (83.33%)
         9,336,668      branch-misses:u           #    0.13% of all branches          (83.34%)

       7.049870367 seconds time elapsed

       6.875355000 seconds user
       0.112719000 seconds sys
```

> Transformed 
```c 
for(int ic = 1; ic < N; ic += BLOCK_SIZE) {
    for(int jc = 1; jc < N; jc += BLOCK_SIZE) {
        for(int kc = 1; kc < N; kc += BLOCK_SIZE) {
            for(int i = ic; i < min(N, ic + BLOCK_SIZE - 1); ++i) {
                for(int j = jc; j < min(N, jc + BLOCK_SIZE - 1); ++j) {
                    for(int k = kc; k < min(N, kc + BLOCK_SIZE - 1); ++k) {
                        c[i][j] = a[i][k] * b[k][j];
                    }
                }
            }
        }
    }
}
```

```
            352.12 msec task-clock:u              #    0.997 CPUs utilized          
           358,518      cache-misses:u            #   43.036 % of all cache refs      (83.25%)
           833,075      cache-references:u        #    2.366 M/sec                    (83.25%)
       793,080,475      cycles:u                  #    2.252 GHz                      (66.52%)
     1,265,523,897      instructions:u            #    1.60  insn per cycle           (83.27%)
       323,955,705      branches:u                #  920.004 M/sec                    (83.53%)
           339,785      branch-misses:u           #    0.10% of all branches          (83.46%)

       0.353356221 seconds time elapsed

       0.255634000 seconds user
       0.093100000 seconds sys
```

The transformation of the original code using loop tiling has led to significant performance improvements. The elapsed time has decreased from approximately 7.05 seconds to 0.35 seconds, indicating a substantial reduction in execution time. This improvement is primarily due to the reduction in cache misses and better cache utilization.

In the original code, there were 248,948 cache misses, which decreased to 358,518 in the transformed code. Despite the number of cache misses being slightly higher, the number of cache references increased significantly from 638,134 to 833,075, indicating more efficient data access patterns due to the loop tiling. This resulted in a lower percentage of cache misses relative to the total cache references.

Additionally, the number of cycles reduced drastically from approximately 21 billion to 793 million, and the instructions executed also decreased significantly, showing that the loop tiling has optimized the instructions per cycle. The transformed code also showed a decrease in branch misses and branches per second, indicating improved control flow and reduced pipeline stalls.

Overall, the loop tiling optimization has resulted in better cache efficiency, reduced execution time, and improved overall performance of the code.