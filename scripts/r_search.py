from pathlib import Path
import sys

if __name__ == "__main__":
    if len(sys.argv) != 2:
        exit(1)
    with Path(__file__).parent.joinpath(sys.argv[1]).open("r") as file:
        contents = file.read()
    new_contents = ""
    for c in contents:
        if c != "\t":
            new_contents += c
    print(new_contents)
