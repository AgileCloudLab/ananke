# Ananke

Library for compressing Ananke is the greek good of force constraint, necessity 


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

