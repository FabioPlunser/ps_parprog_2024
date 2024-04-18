import os
from arguments import get_arguments
from reader import find_logfiles, read_logfile, join_benchmark_results
from writer import to_markdown, plot_benchmark

if __name__ == "__main__":
    # parse arguments passed to program
    title, input_dir, output_dir, plot_width, plot_height = get_arguments()

    # read logfiles and join results
    logfiles = find_logfiles(input_dir)
    result = join_benchmark_results([read_logfile(file) for file in logfiles])

    # create output directory if it does not exist
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    # write markdown table to file
    with open(os.path.join(output_dir, f"{title}.md"), "w") as f:
        f.write(to_markdown(result))

    # write plot to file
    plot_benchmark(title, result, os.path.join(output_dir, f"{title}.png"), plot_width, plot_height)
