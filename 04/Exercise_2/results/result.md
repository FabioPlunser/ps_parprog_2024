# Task 1-3

> Implement (or copy from Exercise 1) a parallel Monte Carlo PI version that uses a local sum approach, i.e. that first aggregates to a per-thread private variable before using `atomic` to aggregate the entire sum of samples.

> Create a second version that does not rely on private variables but a single array where each thread gets one element for local sum storage. In memory, the data layout should then look like `[thread_0][thread_1][_thread_2][...]`.

> Create a third version that continues to use a single array but add padding to it, ensuring that the individual local sum storage locations are separated by unused data, e.g. `[thread_0][N_unused_bytes][thread_1][N_unused_bytes][thread_2][...]`. How you achieve this padding is up to you (there are several implementation possibilities). How large should the padding distance ideally be?

See [mc_pi_local_sum.c](../mc_pi_local_sum.c), [mc_pi_array.c](../mc_pi_array.c) and [mc_pi_array_pad.c](../mc_pi_array_pad.c).

The padding on the implementation of task 3 should be large enough, that every array item containing an actual sum is loaded into it's individual cache line.

# Task 4

> Benchmark all three versions (private variable, array, array with padding) and document your results. Also check the L1 cache misses using `perf stat`. Feel free to also check for this effect on your local machines and report the data (including the CPU type!).
