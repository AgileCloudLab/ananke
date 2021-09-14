# Ananke

Ananke is a library for modern C++ developed as a high level wrapper for multiple compression algorithms.
Developed and maintained by the Net-X group at the Department of Electrical and Computer Engineering at Aarhus University.

The software is released under the BSD version 3 license. 

# Dependencies 

Ananke depends on two no compression algorithm libraries [nlohmann json](klajdkasjlk)

# Example for gzip 

```C++ 
#include <ananke/gzip_compressor.hpp>

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
#include <ananke/gzip_compressor.hpp>

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

