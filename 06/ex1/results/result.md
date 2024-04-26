# Task 1

> What are the data dependencies?
## a

```c
for(int i = 0; i < n - 1; i++) {
S1	x[i] = (y[i] + x[i + 1]) / 7;
}
```

def: n = 5

| i   | $S_1$:x[i] | $S_1$:x[i+1] |
| --- | ---------- | ------------ |
| 0   | x[0]       | x[1]         |
| 1   | x[1]       | x[2]         |
| 2   | x[2]       | x[3]         |
| 3   | x[3]       | x[4]         |

D1 = $S_1 \, \delta^{-1} \, S_1 $

(1) - (0) = (1) $\rightarrow$ (<)  
(2) - (1) = (1) $\rightarrow$ (<)  
(3) - (2) = (1) $\rightarrow$ (<)  
(4) - (3) = (1) $\rightarrow$ (<)  

| Dep | Source     | Type          | Sink          | DistVec | DirVec | LoopCarried | CarriedBy |
| --- | ---------- | ------------- | ------------- | ------- | ------ | ----------- | --------- |
| D1  | $S_1$:x[i] | $\delta^{-1}$ | $S_1$: x[i+1] | (1)     | (<)    | Yes         | I-Loop    |

## b

```c	
for(int i = 0; i < n; i++) {
S1	a = (x[i] + y[i]) / (i + 1);
S2	z[i] = a;
}

S3  f = sqrt(a + k);
```
def: n = 4

| i   | $S_1$:x[i] | $S_1$:y[i] | $S_2$:z[i] |
| --- | ---------- | ---------- | ---------- |
| 0   | x[0]       | y[0]       | z[0]       |
| 1   | x[1]       | y[1]       | z[1]       |
| 2   | x[2]       | y[2]       | z[2]       |
| 3   | x[3]       | y[3]       | z[3]       |

D1 = $S_1 \, \delta^{1} \, S_2$  
D2 = $S_1 \, \delta^{1} \, S_3$

(0) - (0) = (0) $\rightarrow$ (=)  
(1) - (1) = (0) $\rightarrow$ (=)  
(2) - (2) = (0) $\rightarrow$ (=)  
(3) - (3) = (0) $\rightarrow$ (=)  

| Dep | Source          | Type         | Sink        | DistVec | DirVec | LoopCarried | CarriedBy |
| --- | --------------- | ------------ | ----------- | ------- | ------ | ----------- | --------- |
| D1  | $S_1$:x[i],y[i] | $\delta^{1}$ | $S_2$: z[i] | (0)     | (=)    | No          | -         |
| D2  | $S_1$:a         | $\delta^{1}$ | $S_3$: f()  | -       | -      | No          | -         |

## c
```c
for (int i=0; i < n; i++) {
S1   x[i] = y[i] * 2 + b * i;
}


for (int i=0; i < n; i++) {
S2   y[i] = x[i]  + a / (i+1);
}
```
D1 = $S_1 \delta^{1} S_2$  
D2 = $S_1 \delta^{-1} S_2$  
D3 = $S_2 \delta^{1} S_1$  
D4 = $S_2 \delta^{-1} S_1$  


| Dep | Source     | Type          | Sink        | DistVec | DirVec | LoopCarried | CarriedBy |
| --- | ---------- | ------------- | ----------- | ------- | ------ | ----------- | --------- |
| D1  | $S_1$:x[i] | $\delta^{1}$  | $S_2$: x[i] | -       | -      | No          | -         |
| D2  | $S_2$:y[i] | $\delta^{-1}$ | $S_1$: y[i] | -       | -      | No          | -         |
| D3  | $S_2$:x[i] | $\delta^{1}$  | $S_1$: x[i] | -       | -      | No          | -         |
| D4  | $S_1$:y[i] | $\delta^{-1}$ | $S_2$: y[i] | -       | -      | No          | -         |



# Task 2

> Parallelize and optimize the code  

| num_threads | ser_ex1_a | par_ex1_a | ser_ex1_b | par_ex1_b | ser_ex1_c | par_ex1_c |
| ----------- | --------- | --------- | --------- | --------- | --------- | --------- |
| 1           | 7.490s    | 12.668s   | 9.392s    | 10.112s   | 11.397s   | 7.669s    |
| 2           | 7.471s    | 6.976s    | 9.852s    | 4.334s    | 11.382s   | 3.868s    |
| 4           | 7.491s    | 3.849s    | 10.417s   | 2.220s    | 11.438s   | 1.979s    |
| 6           | 7.465s    | 2.867s    | 9.529s    | 1.858s    | 11.394s   | 1.632s    |
| 12          | 7.447s    | 2.437s    | 9.041s    | 1.407s    | 11.421s   | 1.602s    |

 ![table](/06/ex1/results/Excercise_01.png)

> Also see source code.