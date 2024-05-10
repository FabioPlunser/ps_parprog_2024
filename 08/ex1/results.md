# Description
This exercise consists of exploring the effects of OpenMP thread affinity.

## Task 1

> 1) Write an OpenMP program that atomically increments an `int` using `#pragma omp atomic` in a parallel for loop for a large number of iterations, i.e. such that the program takes at least 2 seconds to execute. Have the program print the time required to process the entire loop. Compile your program with gcc 12.2.0 and optimization level `-O3`. Do not perform any manual optimizations such as reducing the number of atomic operations.
- Done, see .c files.

## Task 2
> 2) Run your program with 6 threads. Explore the affinity features of OpenMP 4.0 to change the way threads are mapped to cores, e.g. using a single CPU only or using both CPUs. Explain the affinity settings that you chose.
- The best fastest setting is:
  - `export OMP_PROC_BIND=master`
  - `export OMP_PLACES=threads`
- master all the threads are in the same place as the master thread(high locality)
- threads each HW thread defines a place
## Task 3
> 3) Benchmark your program with these affinity settings. What can you observe?
    - OMP_PROC_BIND=spread is the worst setting because it spreads the threads across the cores, which is bad for locality
    - OMP_PROC_BIND=close is better than spread, but not as good as master
    - OMP_PROC_BIND=master is the best setting because all the threads are in the same place as the master thread(high locality)
    - OMP_PROC_BIND=sockets is the worst setting
    - OMP_PROC_BIND=cores is better then sockets but not as good as threads
    - OMP_PROC_BIND=threads is the best setting for this program because it utilizes all the HW threads.
## Task 4
> 4) Enter the time for N=500.000.000 into the comparison spreadsheet linked on Discord.
- Done, see sheet