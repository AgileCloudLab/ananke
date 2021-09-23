#ifndef ANANKE_SNAPPY_HPP
#define ANANKE_SNAPPY_HPP

#include <cstddef>

#include <cstdint>

#include <vector>
#include <utility>

namespace ananke
{
class snappy
{
public:

    snappy() = default;
    std::pair<bool, std::vector<uint8_t>> compress(const std::vector<uint8_t>& data);
    
    std::vector<uint8_t> decompress(const std::vector<uint8_t>& data, const size_t size); 
}; 
}

#endif /* ANANKE_SNAPPY_HPP */ 
