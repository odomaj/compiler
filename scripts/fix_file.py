from pathlib import Path
import sys

if __name__ == "__main__":
    if len(sys.argv) != 2:
        exit(1)
    with Path(__file__).parent.parent.joinpath(sys.argv[1]).open("r") as file:
        contents = file.read()
    with Path(__file__).parent.parent.joinpath(sys.argv[1]).open("w") as file:
        for c in contents:
            if c not in {"\r", "\f", "\v"}:
                file.write(c)
