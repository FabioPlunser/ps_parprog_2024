# Benchmark Summarization Tool

The **Benchmark Summarization Tool** can be used to automatically generate a markdown table and a line plot to display the results of a runtime benchmark for binaries executed with a different number of threads.

## Tool setup

Copy the tool into any directory on your machine. It seems reasonable to include it within the root directory of your project. A sample file structure is given further down in the section *Tool usage*.

To run the tool a function Python 3 installation is required. Install dependencies specified in [requirements.txt](requirements.txt) either by executing the provided setup script ([setup.sh](setup.sh)) or by manually running `python3 -m pip install -r requirements.txt`.

*NOTE:* The provided setup script creates a virtual environment before installing Python dependencies. Ensure to have this virtual environment active before executing the tool by running `source ./venv/bin/activate`.

## Preparation

The tool expects all benchmarks to log their measurements into a single directory into (possibly multiple) `.log` files.

Every benchmark run must produce a single line entry within one of the logfiles, according to the following format:

`#Benchmark | <program name> | <number of threads> | <runtime in seconds>`

*NOTE*: Additional lines within the logfile (not starting with `#Benchmark`) are simply ignored by the tool.

If the binary to benchmark is written in C, the following code structure could be used to generate valid output:

```c
#include <omp.h>

int main() {
    // Setup, etc.
    // ...

    // Set number of OpenMP threads
	omp_set_num_threads(num_threads);

    // Prepare timing measurement
	double start_time, end_time, elapsed_time;

    // ...

    // Start timing measurement
    start_time = omp_get_wtime();

    // Functionality to benchmark
    // ...

    // Stop timing measurement
    stop_time = omp_get_wtime();
    elapsed_time = stop_time - start_time;

    // Generate benchmark result output
    printf("#Benchmark | %s | %u | %.3f\n", argv[0], num_threads, elapsed_time);
}

```
## Tool usage

A valid file structure containing binaries and logfiles could be the following:

```
Project_Root
├── 01
│   ├── Exercise_1                      << assumed working directory for command examples below
│   │   ├── Makefile
│   │   ├── job.sh
│   │   ├── program_1.c
│   │   ├── program_2.c
|   |   ├── logs                        << directory containing logfiles
│   │   │   ├── logfile1.log
│   │   │   ├── logfile2.log
│   │   │   └── logfile3.log
│   │   └── results
│   │       ├── benchmark_out           << directory containing (generated) tool output
│   │       │   ├── sample-benchmark.md        
│   │       │   └── sample-benchmark.png
│   │       └── result.md
│   └── README.md
└── tool                                << directory containing tool itself
    ├── LICENSE.txt
    ├── README.md
    ├── arguments.py
    ├── reader.py
    ├── requirements.txt
    ├── setup.sh
    ├── summarize.py
    ├── test.md
    └── writer.py
```

A logfile could look like:

```
#Benchmark | ./program_1 | 1 | 12.512
#Benchmark | ./program_2 | 4 | 4.502
Some other sample output                # this line will be ignored
```

Start the tool by executing the following command (assume that you are in `Project_Root/01/Exercise_01` in the above file structure):

`python3 ../../tool/summarize.py --title sample-benchmark --input ./logs --output ./results/benchmark_out`

The tool will then read all logfiles and generate both a markdown table containing benchmark data, as well as a line plot to graphically display the benchmark results.

More info on possible arguments to pass to the tool can be gathered by running:

`python3 <Path to tool directory>/summarize.py -h`