# Ananke

Ananke is a library for modern C++ developed as a high level wrapper for multiple compression algorithms.
Developed and maintained by the Net-X group at the Department of Electrical and Computer Engineering at Aarhus University.

The software is released under the BSD version 3 license. 

**Why this crazy name?**

Ananke is a Greek goddess and her name is a noun for constraint and compressed data is kind of constrained right? 
Therefore, the name Ananke. 

# Dependencies 

Ananke depends on two no compression algorithm libraries which we do not handle, see table below. 
On Linux both should be installable from your package repository and on Mac it should be available via Homebrew. 

| Library | Description| 
--- | ---
[nlohmann/json](https://github.com/nlohmann/json) | Used for handling JSON in C++
[fmtlib](https://github.com/fmtlib/fmt) | Used for string formatting in C++

Next we depend on developer libraries for the following compression algorithms: 

- gzip 
- bzip2
- snappy 

Again packages should be available for both Linux and Mac OS, the latter via Homebrew. 

These dependencies *must* be installed before building Ananke 

# Build 

Step 1: Read the [Dependencies](#Dependencies) section. 

Step 2: Ananke is by default build with Clang++ so ensure you have the compiler installed or modify `wscript` in the root folder to load gcc-c++ or your compiler of choice.
*Note:* We only officially support Clang++.


Step 2: First we have to configure the project, this is done by running the command 

```bash 
python waf configure
```

This downloads one dependency handle by Ananke, which is gtest.
Next to build Ananke and all tests run:

```bash
python waf build
```
If you want to test that everything went as planned run

```
python waf test
```

# Example for gzip 

```C++ 
#include <ananke/gzip.hpp>

#include <cassert>

const size_t org_size = 4096; 
std::vector<uint8_t> data(org_size, 0); // Just for fun; 
auto expected = data;

ananke::gzip zipper; // Auto intialise to gzip level 6

auto compressed = zipper.compress(data); 

if (compressed.first)
{
    // Data was compressed
    assert(compressed.second.size() != org_size);
    assert(compressed.second == expected); 
}
else
{
    assert(compressed.second != expected);
}

auto decompressed = zipper.decompress(compressed.second); 

assert(decompressed == expected); 
```

# Example for bzip2

```C++ 
#include <ananke/bzip2.hpp>

#include <cassert>

const size_t org_size = 4096; 
std::vector<uint8_t> data(org_size, 0); // Just for fun; 
auto expected = data;

ananke::bzip2 zipper(1, 0, 30); // Auto intialise to gzip level 6

auto compressed = zipper.compress(data); 

if (compressed.first)
{
    // Data was compressed
    assert(compressed.second.size() != org_size);
    assert(compressed.second == expected); 
}
else
{
    assert(compressed.second != expected);
}

auto decompressed = zipper.decompress(compressed.second); 

assert(decompressed == expected); 
```

# Example for Snappy

```C++ 
#include <ananke/snappy.hpp>

#include <cassert>

const size_t org_size = 4096; 
std::vector<uint8_t> data(org_size, 0); // Just for fun; 
auto expected = data;

ananke::snappy zipper;

auto compressed = zipper.compress(data); 

if (compressed.first)
{
    // Data was compressed
    assert(compressed.second.size() != org_size);
    assert(compressed.second == expected); 
}
else
{
    assert(compressed.second != expected);
}

auto decompressed = zipper.decompress(compressed.second); 

assert(decompressed == expected); 
```

