# Description

Assume that during testing of your program on a scalar architecture, you found that the execution time is too high, and you have to optimize it. You suppose that the following extracts significantly impact the execution time of your program.

**a)** `c1` is of type `unsigned`:

```C
unsigned c2 = 32 * c1;
```
Strength reduction: Replace multiplication with shift operation.  `32 = 2^5`
```C
unsigned c2 = c1 << 5;

```

**b)** `c1` is of type `unsigned`:

```C
unsigned c2 = 15 * c1;
```

Strength reduction: Replace multiplication with shift and subtraction operation.
```C	
unsigned c2 = (c1 << 4) - c1; // (16 * c1) - c1
```

**c)** `c1` is of type `unsigned`:

```C
unsigned c2 = 96 * c1;
```

Strength reduction: Replace multiplication with shift and addition operation. `96 = 32 + 64`
```C
unsigned c2 = (c1 << 5) + (c1 << 6); // 32 * c1 + 64 * c1
```
**d)** `c1` is of type `unsigned`:

```C
unsigned c2 = 0.125 * c1;
```

Strength reduction: Replace multiplication with shift operation. `0.125 = 1 / 8`
```C
unsigned c2 = c1 >> 3; // c1 / 8

```

**e)** `a` is of type `unsigned *`:

```C
unsigned sum_fifth = 0;

for (int i = 0; i < N / 5; ++i) {
    sum_fifth += a[5 * i];
}
```

Strength reduction: Replace multiplication with addition operation.
```C
unsigned sum_fifth = 0;

for (int i = 0; i < N; i += 5) {
    sum_fifth += a[i];
}
```


**f)** `a` is of type `double *`:

```C
for (int i = 0; i < N; ++i) {
    a[i] += i / 5.3;
}
```

Strength reduction: Pull out the division operation from the loop. Replace division with multiplication operation.
```C
double factor = 1 / 5.3;
for (int i = 0; i < N; ++i) {
    a[i] += i * factor; 
}
```

**g)** `c1` is of type `float`:

```C
float c2 = -1 * c1;
```

Strength reduction: Let the compiler do the rest.
```C
float c2 = -c1; 
```
This is also possible:
```C
*(int*)&c1 ^= (1 << 31); // Flip the sign bit
float c2 = c1;
```
But this is not recommended because the pointer typecast is not safe and it is not portable. It is better to let the compiler do the optimization. Also it does not compile with the `-Werror` flag.
_Hint_: Inquire how IEEE 754 single-precision floating-point numbers are represented in memory.

# Task 1

> Apply strength reduction.
- Done see the code above.


# Task 2

> State under which circumstances the transformation should be applied (e.g. if the cost of performing two additions is less than one multiplication).
- Shift operations are faster than multiplication operations. If the multiplication factor is a power of 2, then it is better to use left shift operations.
- Addition operations are faster than multiplication operations. If the multiplication factor is a small number, then it is better to use addition operations.
- Multiplication operations are faster than division operations. And if the division factor is a power of 2, then it is better to use right shift operations.
- Shift operations can only be applied to integers, not to floating-point numbers.
- Bitwise operations are also efficient compared to multiplication and division operations.


# Task 3

> After you have applied strength reduction, compare the assembly code of the original snippets with your transformation. Investigate how the compiler (`gcc`) optimizes the snippets when using `-O3` and whether the compiler uses your transformation or applies another optimization on top of it. You can use [Compiler Explorer](https://godbolt.org/) to carry out this task. The given examples are already available at <https://godbolt.org/z/NxEBrD>. Note that you can easily navigate to the assembler code for a given input source line by right-clicking, but be aware that the source for one line might be distributed among interleaved instructions.

- Done, see [comparisonCode.c](comparisonCode.c) and [comparisonCode.asm](comparisonCode.asm)
- Our implementation matches the compiler in all function except of two d() and c().
- In d() the compiler does not try to optimize the multiplication with a shift operation.
- In c() the compiler the optimization solution is not obvious at the first glance. Because it uses a multiplication and a bit shift operation. In our solution we used a addition and two bit shift operations. In Assembly our solution is converted to a multiplication and the other solution is converted into a single shift operation. The compiler solution is better because it uses only one shift operation.