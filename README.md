# Mindera Graduate Program

## Adjacent Cells Challenge

This repository contains my submission to the Mindera Graduate Program, namely for the Adjacent Cells challenge.

### The project

This project consists of a tool, done in C++, which, upon reading a valid JSON file comprised of a matrix of 1s and 0s, will  output the coordinates
of the cells which have a 1 and are adjacent to each other, considering 4-connectivity.

### Algorithms

Two methods are provided to solve the challenge:

+ A recursive exploration algorithm ([Flood Fill](https://en.wikipedia.org/wiki/Flood_fill))

+ A method which uses [OpenCV](https://opencv.org/)'s Connected Component Labeling capabilities

### Installation and Dependencies

This project has two dependencies:

+ [OpenCV](https://opencv.org/) 

* [Google Test](https://github.com/google/googletest)

As mentioned above, [OpenCV](https://opencv.org/)  is used for its exemplary speed in performing tasks such as Connected Component Labeling.

[Google Test](https://github.com/google/googletest) is used as the project's unit testing framework.

When both of these packages are installed, as well as `pkg-config`, one simply needs to proceed with a standard CMake building process:

(Assuming one is in the repository)
```
mkdir build
cd build

cmake ..
make
```
This sequence of commands will produce two folders in the `build` directory: `src` and `test. Within these will be the binaries for
the tool and the unit tests, respectively.

### Usage

The actual tool can be run as follows: 

```
./AdjacentCellsChallenge path/to/your/json/matrix
```
The tool also supports some additional arguments:


+ --out <path> - Writes the result to the specified file path instead of stdout. 

+ --solver <algorithm> - Defaults to recursive exploration. To use the OpenCV solver, use `--solver opencv`

+ --notime - Won't print the time it took from parsing the JSON to finishing solving the problem.

### Miscellaneous

+ This project uses the `-O3`compilation flag. O3 is the highest optimization level available in most C++ compilers.
The performance difference between the optimized and non-optimized versions of this project are quite significant.

+ The first drafts of this tool were made in Python. I ended up using C++ for the performance boost.

+ Aside from the two methods presented here, I also tried implementing a concurrent algorithm using [OpenMP](https://www.openmp.org/).
Alas, that approach turned out to be slower than the single-threaded solutions.
