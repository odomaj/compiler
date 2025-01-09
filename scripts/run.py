from pathlib import Path
from argparse import ArgumentParser, Namespace
import subprocess


REPO_ROOT: Path = Path(__file__).parent.parent


def run_container(tag: str) -> None:
    BUILD_PATH: Path = Path(REPO_ROOT).joinpath("build")
    subprocess.run(
        [
            "docker",
            "run",
            "--entrypoint",
            "/run.sh",
            "--volume",
            f"{BUILD_PATH}:/build",
            "--workdir",
            "/build",
            "--rm",
            tag,
        ]
    )


if __name__ == "__main__":
    arg_parser: ArgumentParser = ArgumentParser()
    arg_parser.add_argument("--tag", "-t", default="dragon-compiler")
    args: Namespace = arg_parser.parse_args()
    run_container(args.tag)
