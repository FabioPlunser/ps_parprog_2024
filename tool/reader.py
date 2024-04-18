from os import PathLike
from functools import reduce
from typing import Dict, List, Tuple
import os


def find_logfiles(directory: PathLike) -> List[PathLike]:
    """Finds all logfiles in a given directory and returns the paths to the files as a list."""

    logfiles = []

    for file in os.listdir(directory):
        if file.endswith(".log"):
            logfiles.append(os.path.join(directory, file))

    return logfiles


def read_logfile(file: PathLike) -> Dict[str, List[Tuple[int, float]]]:
    """Reads the content of a logfile and extracts the benchmark information, then return it as a dictionary
    where the program name is the key and the value is a list containing tuples with the number of threads and
    the measured runtime, ordered by the number of threads.
    """

    results: dict[str, List[Tuple[int, float]]] = {}

    with open(file, "r") as f:
        lines = f.readlines()
        lines = [line.strip() for line in lines]
        lines = [line for line in lines if line.startswith("#Benchmark")]

        for line in lines:
            _, program, num_threads, runtime = [token.strip() for token in line.split("|")]

            program = os.path.basename(program)

            if program not in results:
                results[program] = []

            results[program].append((int(num_threads), float(runtime)))

    for key in results:
        results[key].sort(key=lambda x: x[0])

    return results


def join_benchmark_results(results: List[Dict[str, List[Tuple[int, float]]]]) -> Dict[str, List[Tuple[int, float]]]:
    """Joins the benchmark results read from multiple logfiles with `read_logfile()` into a single dictionary."""
    total_result: Dict[str, List[Tuple[int, float]]] = {}

    # join all results into a single dictionary
    for single_result in results:
        for program in single_result:
            if program not in total_result:
                total_result[program] = []

            # add only results for number of threads that are not already in the result
            for num_threads, runtime in single_result[program]:
                if num_threads not in [nt for (nt, _) in total_result[program]]:
                    total_result[program].append((num_threads, runtime))

    # order the results of each program by the number of threads
    for program in total_result:
        total_result[program].sort(key=lambda x: x[0])

    return total_result
