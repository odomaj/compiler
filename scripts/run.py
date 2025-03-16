from pathlib import Path
from argparse import ArgumentParser, Namespace
import subprocess

REPO_ROOT: Path = Path(__file__).parent.parent


def run_container(tag: str, debug: bool, input: str, output: str) -> None:
    BUILD_PATH: Path = REPO_ROOT.joinpath("build")
    WORKING_PATH: Path = REPO_ROOT.joinpath("working")

    build_type: str = "Debug"
    if not debug:
        build_type: str = "Release"

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
            f"/build/{build_type}/",
            "--env",
            f"INPUT=/working/inputs/{input}",
            "--env",
            f"OUTPUT=/working/outputs/{output}",
            "--env",
            "EXECUTABLE=./compiler",
            "--rm",
            tag,
        ]
    )


if __name__ == "__main__":
    arg_parser: ArgumentParser = ArgumentParser()
    arg_parser.add_argument("--tag", "-t", default="dragon-compiler")
    arg_parser.add_argument("--debug", "-d", default="n")
    args, extras = arg_parser.parse_known_args()

    if len(extras) != 2:
        print("missing input or output file")
        exit(1)
    debug: bool = True
    if args.debug == "n":
        debug = False
    elif args.debug != "y":
        print(
            f"[ERROR] {args.debug} not an option for --debug flag,"
            " enter y or n"
        )
        exit(1)

    run_container(args.tag, debug, extras[0], extras[1])
