from pathlib import Path
from argparse import ArgumentParser, Namespace
import shutil
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


def build_exe(tag: str) -> None:
    SRC_PATH: Path = REPO_ROOT.joinpath("src")
    SCRIPTS_PATH: Path = REPO_ROOT.joinpath("scripts")
    BUILD_PATH: Path = REPO_ROOT.joinpath("build")
    BUILD_PATH.mkdir(exist_ok=True)
    subprocess.run(
        [
            "docker",
            "run",
            "--entrypoint",
            "/scripts/build.sh",
            "--volume",
            f"{SRC_PATH}:/src",
            "--volume",
            f"{BUILD_PATH}:/build",
            "--volume",
            f"{SCRIPTS_PATH}:/scripts",
            "--workdir",
            "/build",
            "--rm",
            tag,
        ]
    )
    shutil.copy(
        REPO_ROOT.joinpath("scripts").joinpath("run.sh"),
        REPO_ROOT.joinpath("build").joinpath("run.sh"),
    )


if __name__ == "__main__":
    arg_parser: ArgumentParser = ArgumentParser()
    arg_parser.add_argument("--tag", "-t", default="dragon-compiler")
    arg_parser.add_argument("--image", "-i", default="y")
    arg_parser.add_argument("--exe", "-e", default="y")
    args: Namespace = arg_parser.parse_args()
    if args.image == "y":
        build_image(args.tag)
    elif args.image != "n":
        print(
            f"[ERROR] {args.image} not an option for --image flag, enter y"
            " or n"
        )
        exit(1)
    if args.exe == "y":
        build_exe(args.tag)
    elif args.exe != "n":
        print(f"[ERROR] {args.exe} not an option for --exe flag, enter y or n")
        exit(1)
    exit(0)
