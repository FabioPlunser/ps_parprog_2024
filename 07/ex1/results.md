# Description
> Consider the following, individual code examples in the context of dependence analysis, race conditions, and parallelization:

# Task 1 
> For each example, investigate whether it is parallelized correctly or whether there are any dependencies, and how any potential parallelization mistakes can be solved while keeping the parallelism. Are there multiple solutions and if so, what are their advantages and disadvantages?

## a)
```C
a[0] = 0; // S1
#pragma omp parallel for
for (i=1; i<N; i++) {
    a[i] = 2.0*i*(i-1); //S2
    b[i] = a[i] - a[i-1]; //S3
}
```

- Is the code parallelized correctly? </br>
    No
- Are there any dependencies? </br>
    Yes, there is a true dependence between S2 and S3.
- How can potential parallelization mistakes be solved while keeping the parallelism?   </br>
    Either split it into two loops or write $2.0*i*(i-1)$ as the array index of a. 
    ```c 
    a[0] = 0; // S1
    #pragma omp parallel for
    for (i=1; i<N; i++) {
        a[i] = 2.0*i*(i-1); //S2
    }
    #pragma omp parallel for
    for (i=1; i<N; i++) {
        b[i] = a[i] - a[i-1]; //S3
    }
    ``` 

    ```c 
    a[0] = 0; // S1
    #pragma omp parallel for
    for (i=1; i<N; i++) {
        b[i] = a[2.0*i*(i-1)] - a[2.0*(i-1)*(i-2)]; //S2
    }
    ``` 
- Are there multiple solutions and if so, what are their advantages and disadvantages? </br>
Yes there are multiple solutions. The first solution is easier to understand and maintain. The second solution is more efficient since it reduces the number of loops.


<div style="display: flex; gap: 0.5rem;">

<div>

### D1 
|     | Iter. | Read a[i] | Write a[i-1] |
| --- | ----- | --------- | ------------ |
| S2  | 1     | a[1]      |              |
| S3  | 1     | a[1]      | a[0]         |
| S2  | 2     | a[2]      | a[0]         |
| S3  | 2     | a[2]      | a[1]         |
| S2  | 3     | a[3]      | a[1]         |
| S3  | 3     | a[3]      | a[2]         |

Loop carried true dependence: $S_2 \delta S_3$ </br>
a[i] = Source </br>
a[i-1] = Sink 

Distance Vector: </br>
$(2)-(1) = 1$ </br>
$(3)-(2) = 1$

</div>

<div>

### D2 
|     | Iter. | Read a[i] | Write a[i] |
| --- | ----- | --------- | ---------- |
| S2  | 1     | a[1]      | a[1]       |
| S3  | 1     | a[1]      | a[1]       |
| S2  | 2     | a[2]      | a[2]       |
| S3  | 2     | a[2]      | a[2]       |

Loop independent true dependence: $S_2 \delta S_3$ </br>
a[i] = Source </br>
a[i-1] = Sink 

Distance Vector: $0$

</div>
</div>


## b)

```C
a[0] = 0;
#pragma omp parallel
{
    //Doesn't wait for other threads 
    #pragma omp for nowait
    for (i=1; i<N; i++) {
        a[i] = 3.0*i*(i+1); //S1
    }

    #pragma omp for
    for (i=1; i<N; i++) {
        b[i] = a[i] - a[i-1]; //S2
    }
}
```
- Is the code parallelized correctly? </br>
    No
- Are there any dependencies?</br>
    Yes, because of the nowait there is a dependence where b[i] depends on the previous iteration a[i-1]
- How can potential parallelization mistakes be solved while keeping the parallelism?   </br>
    Remove the nowait clause
    Write ```c #pragma omp barrier``` after the first loop
    Or same as in a) replace i with the expression
- Are there multiple solutions and if so, what are their advantages and disadvantages? </br>
    Yes there are both are very similar 


## c)

```C
#pragma omp parallel for 
for (i=1; i<N; i++) {
    x = sqrt(b[i]) - 1;
    a[i] = x*x + 2*x + 1;
}
```
- Is the code parallelized correctly? </br>
No
- Are there any dependencies? </br>
There is a loop independent depdence where X has to be written before it can be read. 
This does not conflict with the parallelization.
- How can potential parallelization mistakes be solved while keeping the parallelism?   </br>
There is an issue, x is shared between threads. To fix this, x should be declared as lastprivate.
```c
#pragma omp parallel for lastprivate(x)
```
- Are there multiple solutions and if so, what are their advantages and disadvantages? </br>
There is only one solution  


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

- Is the code parallelized correctly? </br>
No
- Are there any dependencies? </br>
There is a loop independent depdence where X has to be written before it can be read. 
This does not conflict with the parallelization.
- How can potential parallelization mistakes be solved while keeping the parallelism?  </br>
However, there is an issue, ```c private(f,x)``` is not quiet correct. It creates an unintialized variable f and x. 
Which isn't a problem for x but for f since it should be initialized with 2. 
To fix this, f should be declared as firstprivate
```c
#pragma omp parallel for firstprivate(f) private(x)
```
Also after the parallel region the global x is not eeffected by the parallel region so we need lastprivate(x)
```c	    
#pragma omp parallel for firstprivate(f) lastprivate(x)
```

- Are there multiple solutions and if so, what are their advantages and disadvantages? </br>
No there is only one solution

## e)

```C
sum = 0; 
#pragma omp parallel for
for (i=1; i<N; i++) {
    sum = sum + b[i]; //S1
}
```
- Is the code parallelized correctly? </br>
NO
- Are there any dependencies? </br>
Yes there is a loop carried true dependency. 

|     | Iter. | Read sum    | Write sum = sum + b[i]      |
| --- | ----- | ----------- | --------------------------- |
| S1  | 1     | sum         | sum (=sum + b[i]) -> source |
| S1  | 2     | sum -> sink | sum (=sum + b[2])           |

- How can potential parallelization mistakes be solved while keeping the parallelism?   </br>
Solved by using a reduction clause
```c
#pragma omp parallel for reduction(+:sum)
```
Or by using a private variable for each thread
```c
int sum_private = 0;
#pragma omp parallel for private(sum_private)
for (i=1; i<N; i++) {
    sum_private = sum_private + b[i]; //S1
}
```
Or by using a critical section
```c
#pragma omp parallel for
for (i=1; i<N; i++) {
    #pragma omp critical
    sum = sum + b[i]; //S1
}
```
Or by using an atomic operation
```c
#pragma omp parallel for
for (i=1; i<N; i++) {
    #pragma omp atomic
    sum = sum + b[i]; //S1
}
```

- Are there multiple solutions and if so, what are their advantages and disadvantages? </br>
Yes there are multiple solutions. As we eplored a few weeks ago the first solution with reduction should be the best. 

