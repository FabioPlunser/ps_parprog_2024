# Description
> Consider the following, individual code examples in the context of dependence analysis, race conditions, and parallelization:

# Task 1 
> For each example, investigate whether it is parallelized correctly or whether there are any dependencies, and how any potential parallelization mistakes can be solved while keeping the parallelism. Are there multiple solutions and if so, what are their advantages and disadvantages?

## a)

```C
a[0] = 0;
#pragma omp parallel for
for (i=1; i<N; i++) {
    a[i] = 2.0*i*(i-1);
    b[i] = a[i] - a[i-1];
}
```

## b)

```C
a[0] = 0;
#pragma omp parallel
{
    #pragma omp for nowait
    for (i=1; i<N; i++) {
        a[i] = 3.0*i*(i+1);
    }
    #pragma omp for
    for (i=1; i<N; i++) {
        b[i] = a[i] - a[i-1];
    }
}
```


## c)

```C
#pragma omp parallel for
for (i=1; i<N; i++) {
    x = sqrt(b[i]) - 1;
    a[i] = x*x + 2*x + 1;
}
```


## d)

```C
f = 2;
#pragma omp parallel for private(f,x)
for (i=1; i<N; i++) {
    x = f * b[i];
    a[i] = x - 7;
}
a[0] = x; 
```

## e)

```C
sum = 0; 
#pragma omp parallel for
for (i=1; i<N; i++) {
    sum = sum + b[i];
}
```



