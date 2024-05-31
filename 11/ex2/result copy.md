# Description

The file [real.tar.gz](../real.tar.gz) contains a realistic implementation of a (simple) numerical algorithm. Imagine you are tasked with making this implementation faster by parallelizing it with OpenMP, without any further information. To that end, this exercise consists in analysing the performance of this application with a sample-based profiler, in order to figure out where to start with the parallelization. For simplicity, we recommend using `gprof`, but you can also use another profile of your choice, if you prefer.

As an example, using `gprof` requires three steps: First, the application needs to be compiled with `gcc` and the flag `-pg`. This causes the compiler to put instrumentation code in the executable. Then, run the application normally, which will produce a new file `gmon.out`. Finally, run `gprof <executable> gmon.out > analysis.txt` in order to obtain the analysis results. Add the `--line` flag to `gprof` if you need more fine-grained information.

# Task 1

> Obtain a performance profile of the given application by following the steps outlined above.

Execute `make profile` to obtain performance profile.


# Task 2

> Discuss the performance profile. What information does it hold and how/why is this useful?

**Flat Profile:**
This section shows the total time spent in each function, sorted by decreasing order of time. It helps identify the functions that consume the most execution time.

**Call Graph:**
This section provides more detailed information about how functions call each other, including the time spent in each call chain. It includes:

    - Parents: Functions that call the given function.
    - Children: Functions called by the given function.
    - Time: The total time spent in the function and its children.
    - Self: The time spent in the function itself, excluding its children.

The functions `resid`, `psinv`, `rprj3` and `interp` seem to be the biggest time consumers with a relatively low call numbers, indicating that there might be loops in there that hold potential for parallelization.

The functions `resid`, `psinv` and `reprj3` seem to regularly call `norm2u3` which also consumes significant computation time, with relatively low call numbers.

It seems likely the five mentioned functions contain parallelizable loops. Due to the consumed computation time, the functions will be optimized in the following order:

1. `resid`
2. `psinv`
3. `rprj3`
4. `interp`
5. `norm2u3`

The functions `vranlc` and `randlc` are called very often. It does not seem likely that introducing parallelization in these functions will increase performance, as the necessary overhead will likely exceed any performance gained by parallelization.