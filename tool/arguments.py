import argparse
import os

from typing import Tuple


def _dir_path(string: str) -> os.PathLike:
    path = os.path.join(os.getcwd(), string)
    if os.path.isdir(path):
        return path
    else:
        raise argparse.ArgumentTypeError(f"'{string}' is not a path to an existing directory")


def _potential_dir_path(string: str) -> os.PathLike:
    path = os.path.join(os.getcwd(), string)
    if os.path.isfile(path):
        raise argparse.ArgumentTypeError(f"'{string}' is a path to an already existing file")
    else:
        return path


def _plot_dim(size: int) -> int:
    if 400 <= size <= 4000:
        return size
    else:
        raise argparse.ArgumentTypeError(f"Plot dimension must be between 400 and 4000 pixels (given: {size})")


def get_arguments() -> Tuple[str, os.PathLike, os.PathLike, int, int]:
    """Parses the arguments that got passed to the programm."""
    parser = argparse.ArgumentParser(
        description="Create a plot for runtime over thread number for different executables as well as a markdown table containing the benchmark results",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )

    parser.add_argument("-t", "--title", help="title of the benchmark", type=str, required=True)

    parser.add_argument(
        "-i",
        "--input",
        help="path to directory containing the log outputs (relative to working directory)",
        type=_dir_path,
        required=True,
    )

    parser.add_argument(
        "-o",
        "--output",
        help="path to directory where diagram and markdown table shall be saved (relative to working)",
        type=_potential_dir_path,
        required=True,
    )

    parser.add_argument("--width", help="width of the plot in pixels", default=1000, type=_plot_dim)

    parser.add_argument("--height", help="height of the plot in pixels", default=600, type=_plot_dim)

    args = parser.parse_args()

    title = args.title
    input_dir = args.input
    output_dir = args.output
    plot_width = args.width
    plot_height = args.height

    return title, input_dir, output_dir, plot_width, plot_height
