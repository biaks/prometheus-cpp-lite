# Prometheus C++ header-only client library

This is a lite, C++ header-only client library for prometheus based on [jupp0r/prometheus-cpp](https://github.com/jupp0r/prometheus-cpp) project.

To see how this can be used see the examples folders.

## Why I decided to do this deep refactoring of an original project prometheus-cpp:
1. I need a simple header only wariant library without dependencies to write metrics to a .prom file,
2. I need the fastest possible work using integer values of counters (original project use only floating pointer values),
3. The origianl project have problems on compilers that do not know how to do LTO optimization,
4. I did not like the python style of the original project and the large amount of extra code in it and I wanted to make it lighter and more c++ classic.

## Now the core of the library has been rewritten:
- The amount of code in core is greatly reduced,
- All the kernel code has been moved to the header files (due to this, the problem with LTO optimization is also solved),
- It is possible to set the type of value that will be used in the counter (you can even use several counters with different value types at the same time).

## What am I going to do next:
- Write a couple of examples how to using the existing core functionality,
- Check and debug this refactored code for Linux mashine (now I worked only in Visual Studio),
- Move from the original project a part of the code responsible for sending metrics through libcurl to the prometheus server, refactoring it and write some examples for it too.

