#ifndef ANANKE_BZIP2_HPP
#define ANANKE_BZIP2_HPP

#include <nlohmann/json.hpp>

#include <cstdint>

#include <vector>

namespace ananke
{

class bzip2
{

public:

    bzip2(const nlohmann::json& config);
    
    bzip2(const int block_size, const int verbosity, const int work_factor);

    std::vector<uint8_t> compress(std::vector<uint8_t>& data);

    std::vector<uint8_t> decompress(std::vector<uint8_t>& data, const size_t size);

    void block_size(const int new_block_size); 
    int block_size() const;

    void verbosity(const int new_verbosity);
    int verbosity() const;

    void work_factor(const int new_work_factor);
    int work_factor() const;
    
private:

    int m_block_size;
    int m_verbosity;
    int m_work_factor; 
};   
}
#endif /* ANANKE_BZIP2_HPP */
