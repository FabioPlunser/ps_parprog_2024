# Description
> Investigate the following given code examples along with their task.

# Task 1
> Investigate the given code excerpt. Can this code be safely parallelized manually? Can this code be safely parallelized by the compiler?
```C
void copy(double* x, double* y) {
    for(int i = 0; i < 1024; i++) {
        x[i] = y[i];
    }
}
```

Assuming that the memory regions referenced by `x` and `y` do not overlap, there are no dependencies between any statements. Manual parallelization is possible by:

```C
void copy(double* x, double* y) {
    #pragma omp parallel for
    for(int i = 0; i < 1024; i++) {
        x[i] = y[i];
    }
}
```

The compiler does not know if the memory regions overlap and will (might) therefore not assume that parallelization is safe.


# Task 2
> Normalize the following loop nest:
```C
for (int i=4; i<=N; i+=9) {
    for (int j=0; j<=N; j+=5) {
        A[i] = 0;
    }
}
```

Algorithm for loop normalization:
1. Replace loop header `for (int i=L; i<=U; i+=S)` with adjusted loop header `for (int i=1; i<=(U-L+S)/S; i++)`:
    - i-loop: `L=4, U=N, S=9` --> `(U-L+S)/S=(N-4+9)/9=(N+5)/9` --> adjusted loop header: `for (int i=1; i<=((double)(N+5)/9); i++)`
    - j-loop: `L=0, U=N, S=5` --> `(U-L+S)/S=(N-0+5)/5=(N+5)/5` --> adjusted loop header: `for (int j=1; j<=((double)(N+5)/5); j++)`
2. Replace every inference to `i` within the loop body by `i*S-S+L`:
    - i-loop: `i` --> `i*9-5`
    - j-loop: no reference to j
3. Insert finalization assignment `i=i*S-S+L` immediately after end of loop
    - i-loop: `i=i*9-5`
    - j-loop: `j=j*5-5`

Normalized code:

```C
for (int i=1; i<=((double)(N+5)/9); i++) {
    for (int j=1; j<=((double)(N+5)/5); j++) {
        A[i*9-5] = 0;
    }
}
```

# Task 3
> Does the following code excerpt hold any dependencies? If not, how would you parallelize it? If yes, what are the distance and direction vectors?
```C
for(int i = 1; i < N; i++) {
    for(int j = 1; j < M; j++) {
        for(int k = 1; k < L; k++) {
            a[i+1][j][k-1] = a[i][j][k] + 5;
        }
    }
}
```