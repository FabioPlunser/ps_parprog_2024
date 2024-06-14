import os
import shutil
import subprocess

LOGDIR = "logs"
DIR_PARTICLES = os.path.join(LOGDIR, "particles")
DIR_TIMESTEPS = os.path.join(LOGDIR, "timesteps")
DIR_THREADS = os.path.join(LOGDIR, "threads")
RESULT_DIR = "results"

def get_particle_number(filename: str) -> int:
    filename = filename.split(".")[0]
    return int(filename.split("-")[1])

def get_timesteps(filename: str) -> int:
    filename = filename.split(".")[0]
    return int(filename.split("-")[2])

def get_number_of_threads(filename: str) -> int:
    filename = filename.split(".")[0]
    parts = filename.split("-")
    return 1 if len(parts) < 4 else int(parts[3])

def delete_all_in_directory(path: str):
    for file in os.listdir(path):
        os.remove(os.path.join(path, file))

def copy_files(source_dir: str, dest_dir: str, files: list):
    for file in files:
        shutil.copy(os.path.join(source_dir, file), os.path.join(dest_dir, file))

def modify_files(dir: str, modifier):
    for file in os.listdir(dir):
        modifier(os.path.join(dir, file))

def modify_file_for_particle_number_benchmark(file: str):
    new_lines = []
    with open(file, "r") as f:
        for line in f.readlines():
            parts = line.split("|")
            parts.pop(3)
            new_lines.append("|".join(parts))
    with open(file, "w") as f:
        f.write("\n".join(new_lines))

def modify_file_for_timestep_benchmark(file: str):
    new_lines = []
    with open(file, "r") as f:
        for line in f.readlines():
            parts = line.split("|")
            parts.pop(2)
            new_lines.append("|".join(parts))
    with open(file, "w") as f:
        f.write("\n".join(new_lines))

def modify_file_for_number_of_threads_benchmark(file: str):
    new_lines = []
    with open(file, "r") as f:
        if "par" in file:
            number_of_threads = get_number_of_threads(file)
        elif "seq" in file:
            number_of_threads = 1

        for line in f.readlines():
            parts = line.split("|")
            parts[2] = f" {number_of_threads} "
            parts.pop(3)
            new_lines.append("|".join(parts))
            if "seq" in file:
                parts[2] = " 12 "
                new_lines.append("|".join(parts))
    with open(file, "w") as f:
        f.write("\n".join(new_lines))

def create_results(title: str, dir: str):
    subprocess.run(
        [
            "python3",
            os.path.join("..", "tool", "summarize.py"),
            "--title", title,
            "--input", dir,
            "--output", RESULT_DIR
        ]
    )

runtime_seq_over_particle_numbers = []
runtime_seq_over_timesteps = []
runtime_over_number_of_threads = []

# find relevant files
for file in os.listdir(LOGDIR):
    if os.path.isdir(os.path.join(LOGDIR, file)):
        continue
    if "seq" in file and get_timesteps(file) == 100:
        runtime_seq_over_particle_numbers.append(file)
    if "seq" in file and get_particle_number(file) == 5000:
        runtime_seq_over_timesteps.append(file)
    if (
        ("par" in file and get_timesteps(file) == 100 and get_particle_number(file) == 5000) or
        ("seq" in file and get_timesteps(file) == 100 and get_particle_number(file) == 5000)
    ):
        runtime_over_number_of_threads.append(file)

# make dirs for individual plots
os.makedirs(DIR_PARTICLES, exist_ok=True)
os.makedirs(DIR_TIMESTEPS, exist_ok=True)
os.makedirs(DIR_THREADS, exist_ok=True)

# delete previous files
delete_all_in_directory(DIR_PARTICLES)
delete_all_in_directory(DIR_TIMESTEPS)
delete_all_in_directory(DIR_THREADS)

# copy relevant files
copy_files(LOGDIR, DIR_PARTICLES, runtime_seq_over_particle_numbers)
copy_files(LOGDIR, DIR_TIMESTEPS, runtime_seq_over_timesteps)
copy_files(LOGDIR, DIR_THREADS, runtime_over_number_of_threads)

# modify files as necessary
modify_files(DIR_PARTICLES, modify_file_for_particle_number_benchmark)
modify_files(DIR_TIMESTEPS, modify_file_for_timestep_benchmark)
modify_files(DIR_THREADS, modify_file_for_number_of_threads_benchmark)

# create result diagrams
create_results("Runtime over number of particles", DIR_PARTICLES)
create_results("Runtime over number of timesteps", DIR_TIMESTEPS)
create_results("Runtime over number of threads", DIR_THREADS)