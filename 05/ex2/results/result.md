# Task 1

> Examine [ex2.c](../ex2.c) and explain what the code does from an abstract, high-level perspective. What should happen here?

- Two individual threads are spawned, that share an uninitialized data variable and an initialized and unset flag.
- The first thread writes data into the variable, then sets the flag.
- The second thread creates a local variable to store the state of the flag and assumes the flag is initially unset. It then waits for the flag to be set, before finally printing data and flag.

More simplified, the second thread should wait for the first thread to complete. 


# Task 2

> Compile this code with optimization level `-O3`. Run it in an interactive job (e.g. using `salloc --exclusive --tasks-per-node=1 --cpus-per-task=1 srun --pty bash`) in a loop many times (e.g. write a loop in bash that executes it 1000 times). Run this loop repeatedly. What can you observe? **Note: Please quit your interactive job once you are done!**

Once `-O3` is enabled, the program never terminates. This happens as thread number 2 uses a deprecated state of the shared flag and never leaves the loop.

[https://hpc-tutorials.llnl.gov/openmp/shared_clause/](https://hpc-tutorials.llnl.gov/openmp/shared_clause/):

>
    A shared variable exists in only one memory location and all threads can read or write to that address.

    It is the programmer’s responsibility to ensure that multiple threads properly access SHARED variables (such as via CRITICAL sections).


[https://hpc-tutorials.llnl.gov/openmp/flush_directive/](https://hpc-tutorials.llnl.gov/openmp/flush_directive/):

> 
    Q17: Is the !$omp flush directive necessary on a cache coheresnt system?

    A17: Yes the flush directive is necessary. Look in the OpenMP specifications for examples of it’s uses. The directive is necessary to instruct the compiler that the variable must be written to/read from the memory system, i.e. that the variable can not be kept in a local CPU register over the flush “statement” in your code.

    Cache coherency makes certain that if one CPU executes a read or write instruction from/to memory, then all other CPUs in the system will get the same value from that memory address when they access it. All caches will show a coherent value. However, in the OpenMP standard there must be a way to instruct the compiler to actually insert the read/write machine instruction and not postpone it. Keeping a variable in a register in a loop is very common when producing efficient machine language code for a loop.

# Task 3

> Does this code require any `#pragma omp flush` and/or `#pragma omp atomic` directives? If it does, where are they necessary? If it does not, why not?

Yes `#pragma omp flush` and/or `#pragma omp atomic` is necessary to guarantee correct access to the shared variables.

There are multiple possibilities.

Using `#pragma omp flush` place it at the end of thread 1 to update the shared variables written by this thread and before the flag retrieval in thread 2 to ensure that it updates its view of the shared variables.

Using `#pragma omp atomic` place `#pragma omp atomic write` before each of the write operations in thread 1 and `#pragma omp atomic read` before the read operations in thread 2 (read of flag AND first read of data). While we have never experienced a false value on the data variable (even without the second `#pragma omp atomic read`), we suspect that this is random and not guaranteed.
