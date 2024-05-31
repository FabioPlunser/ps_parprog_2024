# Description

The file [real.tar.gz](../real.tar.gz) contains a realistic implementation of a (simple) numerical algorithm. Imagine you are tasked with making this implementation faster by parallelizing it with OpenMP, without any further information. To that end, this exercise consists in analysing the performance of this application with a sample-based profiler, in order to figure out where to start with the parallelization. For simplicity, we recommend using `gprof`, but you can also use another profile of your choice, if you prefer.

As an example, using `gprof` requires three steps: First, the application needs to be compiled with `gcc` and the flag `-pg`. This causes the compiler to put instrumentation code in the executable. Then, run the application normally, which will produce a new file `gmon.out`. Finally, run `gprof <executable> gmon.out > analysis.txt` in order to obtain the analysis results. Add the `--line` flag to `gprof` if you need more fine-grained information.

# Task 1

> Obtain a performance profile of the given application by following the steps outlined above.

Execute `make profile` to obtain performance profile.


# Task 2

> Discuss the performance profile. What information does it hold and how/why is this useful?