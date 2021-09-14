#ifndef ANANKE_HPP
#define ANANKE_HPP

#include "gzip.hpp"
#include "bzip2.hpp"

#include <nlohmann/json.hpp>

#include <stdexcept>

#include <type_traits>

namespace ananke
{

    enum algorithm
    {
        GZIP,
        BZIP2
    };

    /// \fn
    /// Ananke factory creates a zipper based on the template type provided and configures it using the provided JSON configuration
    /// @param config is the json configuration used to configure the compression algorithm constructor for the parameters
    /// @return the configured compression algorithm zipper; 
    /// @throws std::runtime_error if an unknown template type is used 
    template<typename T> T zipper_factory(const nlohmann::json& config)
    {
        if constexpr (std::is_same<T, gzip>::value)
        {
            return gzip(config); 
        }
        
        else if constexpr (std::is_same<T, bzip2>::value)
        {
            return bzip2(config);
        }
        else
        {
            throw std::runtime_error("[Ananke] unknown compression algorithmn type");
        }
    }

    /// Creates a zipper based on the input algorithm and the configuration compress the data and disgards the zipper
    /// \callergraph
    /// @param algo is the algorithm to be used
    /// @param config is the json configuration used to configure the zipper
    /// @param data will be compressed
    /// @returns a pair of a boolean indicating if any compression happened and the resulting data.
    ///          if the boolean is false it means data was compressed    
    std::pair<bool, std::vector<uint8_t>> compress(const algorithm algo, const nlohmann::json& config, std::vector<uint8_t>& data);


    /// Creates a zipper based on the input algorithm and the configuration decompress the data and disgards the zipper
    /// \callergraph    
    /// @param algo is the algorithm to be used
    /// @param config is the json configuration used to configure the zipper
    /// @param data will be decompressed
    /// @param size in bytes after compression
    /// @returns the decompressed byte vector, if input data.size() == size no processing is done and data is returned
    /// @throws std::runtime_error if algo is unknown 
    std::vector<uint8_t> decompress(const algorithm algo, const nlohmann::json& config, std::vector<uint8_t>& data, size_t size); 
}

#endif /* ANANKE_HPP */ 
