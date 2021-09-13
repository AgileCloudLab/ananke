#ifndef ANANKE_GZIP_HPP
#define ANANKE_GZIP_HPP

#include <nlohmann/json.hpp>

#include <utility>

namespace ananke
{
class gzip
{
public:

    /// Creates gzip object based on a json configuration
    /// @param config is a json object with the appropriate fields for bzip,
    ///        see second constructor for needed values and naming
    /// @throws std::runtime_error if a configuration parameter is missing     
    gzip(const nlohmann::json& config);

    /// Construct gzip object
    /// @param level that gzip will run at. Values should be between 1 and 9
    gzip(const size_t level = 6); 

    /// Compresses a byte vector
    /// @param data to be compresed
    /// @returns a pair of a boolean indicating if any compression happened and the resulting data.
    ///          if the boolean is false it means data was compressed    
    std::pair<bool, std::vector<uint8_t>> compress(std::vector<uint8_t>& data);

    /// Decompress a byte vector
    /// @param data contains the bytes to be decompressed
    /// @param size in bytes after compression
    /// @returns the decompressed byte vector, if input data.size() == size no processing is done and data is returned 
    std::vector<uint8_t> decompress(std::vector<uint8_t>& data, size_t size);

    void level(const size_t level);
    size_t level() const; 

private:

    size_t m_level;
    
}; 
}

#endif /* ANANKE_GZIP_HPP */
