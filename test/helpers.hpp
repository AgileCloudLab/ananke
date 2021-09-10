#include <cstdint>

#include <vector>

#include <algorithm>

std::vector<uint8_t> generate_data(size_t size)
{
    std::vector<uint8_t> data(size);
    std::generate(std::begin(data), std::end(data), rand);
    return data; 
}
