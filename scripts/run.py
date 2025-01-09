from pathlib import Path
from argparse import ArgumentParser, Namespace
import subprocess


REPO_ROOT: Path = Path(__file__).parent.parent


def run_container(tag: str, input: str, output: str) -> None:
    BUILD_PATH: Path = REPO_ROOT.joinpath("build")
    WORKING_PATH: Path = REPO_ROOT.joinpath("working")

    subprocess.run(
        [
            "docker",
            "run",
            "--entrypoint",
            "/build/run.sh",
            "--volume",
            f"{BUILD_PATH}:/build",
            "--volume",
            f"{WORKING_PATH}:/working",
            "--workdir",
            "/build",
            "--env",
            f"INPUT=/working/inputs/{input}",
            "--env",
            f"OUTPUT=/working/outputs/{output}",
            "--rm",
            tag,
        ]
    )


if __name__ == "__main__":
    arg_parser: ArgumentParser = ArgumentParser()
    arg_parser.add_argument("--tag", "-t", default="dragon-compiler")
    arg_parser.add_argument("--input", "-i", default="")
    arg_parser.add_argument("--output", "-o", default="")
    args: Namespace = arg_parser.parse_args()

    if args.input == "" or args.output == "":
        print("missing input or output file")
        exit(1)
    run_container(args.tag, args.input, args.output)
