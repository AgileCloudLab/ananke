#include "ananke.hpp"

namespace ananke
{
    std::pair<bool, std::vector<uint8_t>> compress(const algorithmn algo, const nlohmann::json& config, std::vector<uint8_t>& data)
    {
        if (algo == algorithmn::GZIP)
        {
            auto zipper = zipper_factory<gzip>(config);
            return zipper.compress(data); 
        }
        else if (algo == algorithmn::BZIP2)
        {
            auto zipper = zipper_factory<bzip2>(config);
            return zipper.compress(data); 
        }
        else
        {
            throw std::runtime_error("[Ananke] Unknown algorithmn provided");
        }
            
    }

    std::vector<uint8_t> decompress(const algorithmn algo, const nlohmann::json& config, std::vector<uint8_t>& data, size_t size)
    {
        if (algo == algorithmn::GZIP)
        {
            auto zipper = zipper_factory<gzip>(config);
            return zipper.decompress(data, size); 
        }
        else if (algo == algorithmn::BZIP2)
        {
            auto zipper = zipper_factory<bzip2>(config);
            return zipper.decompress(data, size); 
        }
        else
        {
            throw std::runtime_error("[Ananke] Unknown algorithmn provided");
        }
            
    }
}
