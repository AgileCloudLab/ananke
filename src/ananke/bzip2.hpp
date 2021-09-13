#ifndef ANANKE_BZIP2_HPP
#define ANANKE_BZIP2_HPP

#include <nlohmann/json.hpp>

#include <cstdint>

#include <vector>

#include <utility>

namespace ananke
{
///
/// This is a wrapper for the bzip algorithm 
///
class bzip2
{

public:

    /// Construct the bzip2 object using a json configuration
    /// @param config is a json object with the appropriate fields for bzip,
    ///        see second constructor for needed values and naming
    /// @throws std::runtime_error if a configuration parameter is missing 
    bzip2(const nlohmann::json& config);

    /// Construct the bzip2 object
    /// @param block_size that bzip2 will work on
    /// @param verboisity which bzip2 will use - silent = 0
    /// @param work_factor used by bzip2 - 30 is the standard value 
    bzip2(const int block_size, const int verbosity, const int work_factor);

    /// Compresses a byte vector
    /// @param data to be compresed
    /// @returns a pair of a boolean indicating if any compression happened and the resulting data.
    ///          if the boolean is false it means data was compressed
    std::pair<bool, std::vector<uint8_t>> compress(std::vector<uint8_t>& data);

    /// Decompress a byte vector
    /// @param data contains the bytes to be decompressed
    /// @param size in bytes after compression
    /// @returns the decompressed byte vector, if input data.size() == size no processing is done and data is returned
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
