from pathlib import Path
from argparse import ArgumentParser, Namespace
import subprocess


REPO_ROOT: Path = Path(__file__).parent.parent


def build_image(tag: str) -> None:
    subprocess.run(
        [
            "docker",
            "buildx",
            "build",
            "--tag",
            tag,
            str(REPO_ROOT),
        ]
    )


def run_build(tag: str) -> None:
    SRC_PATH: Path = Path(REPO_ROOT).joinpath("src")
    BUILD_PATH: Path = Path(REPO_ROOT).joinpath("build")
    BUILD_PATH.mkdir(exist_ok=True)
    subprocess.run(
        [
            "docker",
            "run",
            "--entrypoint",
            "/build.sh",
            "--volume",
            f"{SRC_PATH}:/src",
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
    build_image(args.tag)
    run_build(args.tag)
