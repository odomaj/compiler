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
    arg_parser.add_argument("--image", "-i", default="true")
    arg_parser.add_argument("--exe", "-e", default="true")
    args: Namespace = arg_parser.parse_args()
    if args.image == "true":
        build_image(args.tag)
    elif args.image != "false":
        pass
    if args.exe == "true":
        build_exe(args.tag)
    elif args.exe != "false":
        pass
