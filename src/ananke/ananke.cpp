#include "ananke.hpp"

namespace ananke
{
    std::pair<bool, std::vector<uint8_t>> compress(const algorithm algo, const nlohmann::json& config, std::vector<uint8_t>& data)
    {
        if (algo == algorithm::GZIP)
        {
            auto zipper = zipper_factory<gzip>(config);
            return zipper.compress(data); 
        }
        else if (algo == algorithm::BZIP2)
        {
            auto zipper = zipper_factory<bzip2>(config);
            return zipper.compress(data); 
        }
        else if (algo == algorithm::SNAPPY)
        {
            auto zipper = zipper_factory<snappy>(config);
            return zipper.compress(data); 
        }
        else
        {
            throw std::runtime_error("[Ananke] Unknown algorithmn provided");
        }
            
    }

    std::vector<uint8_t> decompress(const algorithm algo, const nlohmann::json& config, std::vector<uint8_t>& data, size_t size)
    {
        if (algo == algorithm::GZIP)
        {
            auto zipper = zipper_factory<gzip>(config);
            return zipper.decompress(data, size); 
        }
        else if (algo == algorithm::BZIP2)
        {
            auto zipper = zipper_factory<bzip2>(config);
            return zipper.decompress(data, size); 
        }
        else if (algo == algorithm::SNAPPY)
        {
            auto zipper = zipper_factory<snappy>(config);
            return zipper.decompress(data, size); 
        }
        else
        {
            throw std::runtime_error("[Ananke] Unknown algorithmn provided");
        }
            
    }
}
