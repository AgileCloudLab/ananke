#ifndef ANANKE_HPP
#define ANANKE_HPP

#include "gzip.hpp"
#include "bzip2.hpp"

#include <nlohmann/json.hpp>

#include <stdexcept>

#include <type_traits>

namespace ananke
{

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
}

#endif /* ANANKE_HPP */ 
