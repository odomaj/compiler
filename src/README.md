# CS445 Spring 2025 Dragon Compiler

## Status

1. Passes 15/17 semantic checks located at /afs/cu/class/cs445/public/Testing/Semantic/
2. Does not check the dangling else problem
3. Does not ensure functions do not alter non-local variables
4. Sometimes runs into problems during some forms of statements

## General Build Instructions

1. generate a build directory (optional)
2. cmake -DCMAKE_BUILD_TYPE=<desired_build_type> <path_to_src>
   1. -DCMAKE_BUILD_TYPE=Debug, will echo files as they are parsed and ensure asserts are run
   2. -DCMAKE_BUILD_TYPE=Release, will not echo files as they are parsed and does not ensure asserts are run
3. make

## Build Example

1. starting in src
2. mkdir ../build/
3. mkdir ../build/Debug/
4. cd ../build/Debug/
5. cmake -DCMAKE_BUILD_TYPE=Debug ../../src/
6. make

## Run Compiler

- Run Individual File: ./compiler <path_to_file>
- Run Semantic Testing Dir: ./compiler_test <path_to_dir>
  - on polaris: ./compiler_test /afs/cu/class/cs445/public/Testing/Semantic/
