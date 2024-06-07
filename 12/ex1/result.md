# Description

Assume that during testing of your program on a scalar architecture, you found that the execution time is too high, and you have to optimize it. You suppose that the following extracts significantly impact the execution time of your program.

**a)** `c1` is of type `unsigned`:

```C
unsigned c2 = 32 * c1;
```

**b)** `c1` is of type `unsigned`:

```C
unsigned c2 = 15 * c1;
```

**c)** `c1` is of type `unsigned`:

```C
unsigned c2 = 96 * c1;
```

_Hint_: use shift(s) and addition(s) to replace the multiplication

**d)** `c1` is of type `unsigned`:

```C
unsigned c2 = 0.125 * c1;
```

**e)** `a` is of type `unsigned *`:

```C
unsigned sum_fifth = 0;

for (int i = 0; i < N / 5; ++i) {
    sum_fifth += a[5 * i];
}
```

**f)** `a` is of type `double *`:

```C
for (int i = 0; i < N; ++i) {
    a[i] += i / 5.3;
}
```

**g)** `c1` is of type `float`:

```C
float c2 = -1 * c1;
```

_Hint_: Inquire how IEEE 754 single-precision floating-point numbers are represented in memory.

# Task 1

> Apply strength reduction.


# Task 2

> State under which circumstances the transformation should be applied (e.g. if the cost of performing two additions is less than one multiplication).


# Task 3

> After you have applied strength reduction, compare the assembly code of the original snippets with your transformation. Investigate how the compiler (`gcc`) optimizes the snippets when using `-O3` and whether the compiler uses your transformation or applies another optimization on top of it. You can use [Compiler Explorer](https://godbolt.org/) to carry out this task. The given examples are already available at <https://godbolt.org/z/NxEBrD>. Note that you can easily navigate to the assembler code for a given input source line by right-clicking, but be aware that the source for one line might be distributed among interleaved instructions.

