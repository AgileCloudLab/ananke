#ifndef ANANKE_GZIP_HPP
#define ANANKE_GZIP_HPP

#include <nlohmann/json.hpp>

#include <utility>

namespace ananke
{
class gzip
{
public:
    gzip(const nlohmann::json& config);
    gzip(const size_t level = 6); 

    std::pair<bool, std::vector<uint8_t>> compress(std::vector<uint8_t>& data);
    std::vector<uint8_t> decompress(std::vector<uint8_t>& data, size_t size);

private:

    size_t m_level;
    
}; 
}

#endif /* ANANKE_GZIP_HPP */
