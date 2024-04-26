# Given code

```c
for (int i = 0; i < 4; ++i) {
    for (int j = 1; j < 4; ++j) {
        a[i + 2][j - 1] = b * a[i][j] + 4;  // S
    }
}
```

# Task 1

> For each iteration, give the corresponding distance and direction vectors

| | i | j | source (a[i+2][j-1]) | sink (a[i][j]) | distance | direction vectors |
|---|---|---|---|---|---|---|
| S[1,1] | 0 | 1 | a[2][0] | a[0][1] |  |  |
| S[1,2] | 0 | 2 | a[2][1] -> (1) | a[0][2] |  |  |
| S[1,3] | 0 | 3 | a[2][2] -> (2) | a[0][3] |  |  |
| S[2,1] | 1 | 1 | a[3][0] | a[1][1] |  |  |
| S[2,2] | 1 | 2 | a[3][1] -> (3) | a[1][2] |  |  |
| S[2,3] | 1 | 3 | a[3][2] -> (4) | a[1][3] |  |  |
| S[3,1] | 2 | 1 | a[4][0] | a[2][1] -> (1) | (2,-1) | (<,>) |
| S[3,2] | 2 | 2 | a[4][1] | a[2][2] -> (2) | (2,-1) | (<,>) |
| S[3,3] | 2 | 3 | a[4][2] | a[2][3] |  |  |
| S[4,1] | 3 | 1 | a[5][0] | a[3][1] -> (3) | (2,-1) | (<,>) |
| S[4,2] | 3 | 2 | a[5][1] | a[3][2] -> (4) | (2,-1) | (<,>) |
| S[4,3] | 3 | 3 | a[5][2] | a[3][3] |  |  |


# Task 2

> What type of dependence is represented in this code snippet?

Loop carried true dependency:

- S[1,2] &delta; S[3,1] for a[2][1]
- S[1,3] &delta; S[3,2] for a[2][2]
- S[2,2] &delta; S[4,1] for a[3][1]
- S[2,3] &delta; S[4,2] for a[3][2]

# Task 3

> How would you parallelize this code?

Parallelize inner loop. Dependency is carried by outer loop.

As long as outer loop is executed sequentially

- S[1,2] will always be executed before S[3,1]
- S[1,3] will always be executed before S[3,2]
- S[2,2] will always be executed before S[4,1]
- S[2,3] will always be executed before S[4,2]

