#ifndef ANANKE_HPP
#define ANANKE_HPP

#include "gzip.hpp"
#include "bzip2.hpp"

#include <nlohmann/json.hpp>

#include <stdexcept>

#include <type_traits>

namespace ananke
{

    enum algorithmn
    {
        GZIP,
        BZIP2
    };
    
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

    std::pair<bool, std::vector<uint8_t>> compress(const algorithmn algo, const nlohmann::json& config, std::vector<uint8_t>& data);

    std::vector<uint8_t> decompress(const algorithmn algo, const nlohmann::json& config, std::vector<uint8_t>& data, size_t size); 
}

#endif /* ANANKE_HPP */ 