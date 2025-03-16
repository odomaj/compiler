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


def build_exe(tag: str, run_test: bool, debug: bool) -> None:
    SRC_PATH: Path = REPO_ROOT.joinpath("src")
    SCRIPTS_PATH: Path = REPO_ROOT.joinpath("scripts")
    TESTS_PATH: Path = REPO_ROOT.joinpath("tests")
    BUILD_PATH: Path = REPO_ROOT.joinpath("build")
    BUILD_PATH.mkdir(exist_ok=True)

    cmake_flag: str = "-DCMAKE_BUILD_TYPE=Debug"
    build_type: str = "Debug"
    if not debug:
        cmake_flag: str = "-DCMAKE_BUILD_TYPE=Release"
        build_type: str = "Release"

    build_command: list[str] = [
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
        "--env",
        "BUILD_TARGET=/src",
        "--env",
        f"BUILD_FLAG={cmake_flag}",
        "--workdir",
        f"/build/{build_type}",
        "--rm",
    ]
    if run_test:
        build_command.extend(
            [
                "--volume",
                f"{TESTS_PATH}:/tests",
                "--env",
                f"TEST_TARGET=/build/{build_type}/compiler_test",
                "--env",
                "INPUT_DIR=/tests/",
            ]
        )
    build_command.append(tag)

    subprocess.run(build_command)
    shutil.copy(
        REPO_ROOT.joinpath("scripts").joinpath("run.sh"),
        REPO_ROOT.joinpath("build").joinpath("run.sh"),
    )


if __name__ == "__main__":
    arg_parser: ArgumentParser = ArgumentParser()
    arg_parser.add_argument("--tag", "-t", default="dragon-compiler")
    arg_parser.add_argument("--image", "-i", default="y")
    arg_parser.add_argument("--exe", "-e", default="y")
    arg_parser.add_argument("--run_tests", "-r", default="y")
    arg_parser.add_argument("--debug", "-d", default="n")
    args: Namespace = arg_parser.parse_args()
    if args.image == "y":
        build_image(args.tag)
    elif args.image != "n":
        print(
            f"[ERROR] {args.image} not an option for --image flag, enter y"
            " or n"
        )
        exit(1)
    run_tests: bool = True
    if args.run_tests == "n":
        run_tests = False
    elif args.run_tests != "y":
        print(
            f"[ERROR] {args.run_tests} not an option for --run_tests flag,"
            " enter y or n"
        )
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
    if args.exe == "y":
        build_exe(args.tag, run_tests, debug)
    elif args.exe != "n":
        print(f"[ERROR] {args.exe} not an option for --exe flag, enter y or n")
        exit(1)
    exit(0)
