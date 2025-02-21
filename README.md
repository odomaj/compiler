# CS445 Compiler Construction Dragon Compiler

hello world for Dragon Compiler build environment

## Requirements

- Python3
- Docker

## Instructions

- Build: run scripts/build.py
    - -i <y/n> build image
    - -t <image_tag> name of image to build
    - -e <y/n> build executable 
- Run: run scripts/run.py <input_file> <output_file>
    - -t <image_tag> name of image to run
    - input file should be located in working/inputs
    - output file is not used but an arbitrary value must be given (future implementations will utilize this file)

## Known Issues

When building if the error "bash: /scripts/build.sh: cannot execute: required file not found" is thrown:

1. Copy the contents of scripts/build.sh
2. Delete scripts/build.sh
3. Create a new scripts/build.sh
4. Paste the original contents of scripts/build.sh into the new file

When running if the error "bash: /build/run.sh: cannot execute: required file not found" is thrown:

1. Copy the contents of scripts/run.sh
2. Delete scripts/run.sh
3. Create a new scripts/run.sh
4. Paste the original contents of scripts/run.sh into the new file
5. Rebuild the image
