# gen

[advent of code](https://adventofcode.com) solutions in cpp (… and cmake and vcpkg)

each year has a cmake file which builds a unique binary for each day.

the solutions are not particularly good, and steadily decline in quality as interest drops.

## building

often the tasks required parsing some data, which was saved as a txt file and passed as the first argument to the generated binary.
so, e.g. the 23rd of December 2016 can be built and ran via,

``` shell
mkdir -p /2016/build && cd $_
cmake .. && make && ./20161223 ../data/20161223.txt
```

where `2016/data/20161223.txt` contains the task prompt.

### lib

some days make use of a local library

``` shell
cd /advent_lib
mkdir build && cd $_
cmake --build . --target install
```
