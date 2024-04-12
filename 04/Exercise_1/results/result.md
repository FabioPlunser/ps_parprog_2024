# Task 1

> Review the pthreads-based implementation provided in [monte_carlo_pi/mc_pi_pthreads.c](../../monte_carlo_pi/mc_pi_pthreads.c). Benchmark it with 1, 2, 4, 6, and 12 threads on LCC3. What can you observe?

The execution time seems to scale inversely proportional to the number of threads. See results for Task 4+5 for detailled timing measurements.

# Task 2+3

> Implement parallel versions of this approximation using OpenMP. In total, three different versions using the following OpenMP constructs should be provided:
>   1) `critical` section
>   2) `atomic` statement
>   3) `reduction` clause

> To increase the performance difference among these versions, make sure you increment the samples counter directly, without aggregating to private variables first.

See available source files.

# Task 4+5

> Benchmark your OpenMP implementations with the same number of threads using OpenMP's time measurement function. What can you observe? How do those results compare to your earlier measurements?

> The tool `/usr/bin/time` can be used to get useful information on the properties of a program's execution, e.g. its execution time or the maximum amount of main memory used. Measure the execution time of your OpenMP implementation using `/usr/bin/time -v <program_name>`. Take a look at the output, specifically "user time" and "elapsed (wall clock) time". How do they differ? Does either of them match the time measurement function of OpenMP?

- Build with `make all`
- Run all benchmarks with `make bench_all`
- Run individual benchmark with `make bench TARGET=<binary>` (if required)
- Benchmark output in [logs](../logs) (contains data for both timing measurement with OpenMP's time measurement as well as measurement taken with `/usr/bin/time`)

## Benchmark results

| Number of threads | PThread | OMP (Critical) | OMP (Atomic) | OMP (Reduction) |
|---|---|---|---|---|
| 1 | 10,899s | 16,411s | 14,037s | 10,335s |
| 2 | 5,455s | 43,594s | 12,287s | 5,156s |
| 4 | 2,757s | 119,466s | 24,861s | 2,616s |
| 6 | 1,894s | 152,977s | 25,667s | 1,874s |
| 12 | 0,962s | 176,399s | 20,593s | 0,988s |

Also see [results.png](results.png).

## Benchmark interpretation

The OMP (Critical) implementation shows degrading performance with an increasing number of threads. This is well explainable, as each thread blocks access to the counter update section within the program and might thereby halt all other threads. Every time a thread wants to update the counter, a switching overhead occurs.

The OMP (Atomic) implementation also shows decreasing performance with an increasing number of threads, although there seems to be a maximum around threads after which performance slightly increases again. It is however important to notice that performance is still well below the original PThreads implementation. Again this can be explained by the atomic nature of the (centralized) counter update operation.

The OMP (Reduction) implementation shows basically identical performance to the original PThreads implementation. This seems reasonable as there would be no reason for threads to block each other.

## User time vs. elapsed time

Relevant excerpts of timing measurement for `mc_pi_critical` with 12 threads:

```
Command being timed: "./mc_pi_critical 12"
	User time (seconds): 1937.08
    ...
	Percent of CPU this job got: 1098%
	Elapsed (wall clock) time (h:mm:ss or m:ss): 2:56.41
	...
	Involuntary context switches: 2161
    ...
```

Relevant excerpts of timing measurement for `mc_pi_reduction` with 12 threads:

```
Command being timed: "./mc_pi_reduction 12"
	User time (seconds): 10.98
	...
	Percent of CPU this job got: 1090%
	Elapsed (wall clock) time (h:mm:ss or m:ss): 0:01.00
	...
	Involuntary context switches: 47
	...
```
- The user time represents the total computation time the program consumed, where each thread is accounted for individually.
- The elapsed (wall clock) time is the actual runtime of the program. This comes closest to the OpenMP time measurement.
- It is also interesting to note the number of involuntary context switches, which seems to be - as explained before - the main reason for the bad performance of the OMP (Critical) implementation.


# Task 6

> Add the wall clock time measurements for 12 threads on LCC3 to the comparison spreadsheet linked on Discord.

Done