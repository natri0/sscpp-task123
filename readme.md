# C++ Internship Tasks: 1-3

this contains the first three tasks i had to do by myself:
1. list of strings (no `struct` / `union` / etc)
2. type-safe holder for "any primitive type"
3. multi-threaded `tokei` alternative for c++ files

each task is implemented in its respective directory.

tasks have unit tests built with googletest. the library is assumed to be installed system-wide with a package manager that makes it available to CMake.

## Task 1

pretty simple, had to remember how to use `string.h` functions like `strstr` and how to correctly handle manual allocations with `malloc` / `free`.

- [`stringlist.h`](task1/stringlist.h)
- [`stringlist.cpp`](task1/stringlist.cpp)
- [`test.cpp`](task1/test.cpp)

## Task 2

this task can be easily described with one word: *repetitive*. there's like 15 types you need to handle and the code for each of them is pretty much the same.

the container has a `union` for all possible types of the value and an `enum` field that saves which type is currently inside of it.  
retrieving data is done with cast operator overload (i.e. `operator int()`), that checks if the currently-stored type matches what is being retrieved. if those don't match, it throws an exception.

to make it a bit less tedious & less prone to copy-paste errors (e.g. checking for the wrong type) my actual code is in two codegen files:
- [`generate.py`](task2/generate.py), which generates the actual [`anytype.h` header](task2/anytype.h) into stdout
- [`gentest.py`](task2/gentest.py), which generates the [unit tests](task2/test.cpp) for that header

there's also a leftover [`main.cpp`](task2/main.cpp) that's used to quickly verify it compiles & seems to work fine.

## Task 3

counts lines of code, blanks, comments in a given directory. there's a separate `task3` binary and a `task3_test` binary, where the former is the one you actually want to run, and the latter runs the unit tests.

this one is written in a much more OOP style, having e.g. a separate class for finding files using `recursive_directory_iterator`.

the most interesting code (at least if you ask me) is in [`FileStats.cpp`](task3/FileStats.cpp), as that's the file that actually calculates the statistics. when handling comments, it intelligently checks if the comment might be inside a string literal to not have false positives!

at the time of writing, the multi-threading portion of it isn't done yet. we'll see.
