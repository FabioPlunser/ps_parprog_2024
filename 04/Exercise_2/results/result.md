# Task 1-3

> Implement (or copy from Exercise 1) a parallel Monte Carlo PI version that uses a local sum approach, i.e. that first aggregates to a per-thread private variable before using `atomic` to aggregate the entire sum of samples.

> Create a second version that does not rely on private variables but a single array where each thread gets one element for local sum storage. In memory, the data layout should then look like `[thread_0][thread_1][_thread_2][...]`.

> Create a third version that continues to use a single array but add padding to it, ensuring that the individual local sum storage locations are separated by unused data, e.g. `[thread_0][N_unused_bytes][thread_1][N_unused_bytes][thread_2][...]`. How you achieve this padding is up to you (there are several implementation possibilities). How large should the padding distance ideally be?

See [mc_pi_local_sum.c](../mc_pi_local_sum.c), [mc_pi_array.c](../mc_pi_array.c) and [mc_pi_array_pad.c](../mc_pi_array_pad.c).

The padding on the implementation of task 3 should be large enough, that every array item containing an actual sum is loaded into it's individual cache line. The cache line size on the LLC3 cluster should be 64 bytes and experiments indicated that speed-up is maximized assuming this cache line size.

# Task 4

> Benchmark all three versions (private variable, array, array with padding) and document your results. Also check the L1 cache misses using `perf stat`. Feel free to also check for this effect on your local machines and report the data (including the CPU type!).

- Build with `make all`
- Run all benchmarks with `make bench_all`
- Run individual benchmark with `make bench TARGET=<binary>` (if required)
- Run all cache miss analysis with `make cache_misses_all`
- Run individual cache miss analysis with `make cache_misses TARGET=<binary>`
- Benchmark and cache miss analysis output in [logs](../logs)

## Benchmark results

| Number of threads | Local sum | Array | Array with padding |
|---|---|---|---|
| 1 | 10,300s | 14,046s | 13,969s |
| 2 | 5,211s | 9,824s | 6,964s |
| 4 | 2,633s | 15,173s | 3,506s |
| 6 | 1,802s | 10,373s | 2,430s |
| 12 | 1,004s | 10,110s | 1,320s |

Also see [results.png](results.png).

## Benchmark interpretation

Accumulating local sums before attempting final calculation seems to be the fastest implementation.

Following an array implementation caching seems to hinder performance improvement by increasing the thread number as storing a whole region of the array for some threads makes synchronization between threads necessary.

Implementing padding between the array elements containing data resolves that issue and brings performance almost back to the local sum approach's performance. The remaining performance difference would have to be subject to further research.

## Cache miss results

The cache miss analysis was carried out for all three implementations with 12 threads each.

| Metric | Local sum | Array | Array with padding |
|---|---|---|---|
| L1-dcache-loads | 7.000.136.487 | 7.549.914.838 | 7.549.914.707 |
| L1-dcache-load-misses | 20.789 | 24.149 | 25.225 |
| L1-dcache-stores | 3.500.053.011 | 4.049.831.373 | 4.049.831.233 |
| L1-dcache-store-misses | 1.237 | 1.942 | 1.618 |
| Elapsed time | 10,363s | 14,065s | 13,964s |

## Cache miss interpretation

It is not really understandable why there is no difference in cache misses between the array and the array with padding implementation.

The following things have been tried to prevent an unintended influence by user error:
- Deactivated compiler optimization
- Experimented with different cache line size assumptions (for padding size calculation)
- Experimented with a different number of threads
- Analyzed further metrics (cache-misses, LLC-load-misses, LLC-store-misses)

In no case has there been an observable, significant difference between array and array with padding. The implementation itself however seems correct, as the observed differences in performance benchmarking suggest.

# Task 5

> Enter the wall clock time of each version for 12 threads on LCC3 to the comparison spreadsheet linked on Discord.

TODO