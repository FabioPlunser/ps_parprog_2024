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

# Task 2
> Normalize the following loop nest:
```C
for (int i=4; i<=N; i+=9) {
    for (int j=0; j<=N; j+=5) {
        A[i] = 0;
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