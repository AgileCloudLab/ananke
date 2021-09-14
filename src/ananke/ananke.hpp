#ifndef ANANKE_HPP
#define ANANKE_HPP

#include "gzip.hpp"
#include "bzip2.hpp"

#include <nlohmann/json.hpp>

#include <stdexcept>

#include <type_traits>

namespace ananke
{

    
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
