#include "gzip_compressor.hpp"

#include <zlib.h>

#include <fmt/core.h>

#include <stdexcept>


namespace ananke
{
    gzip::gzip(const nlohmann::json& config)
    {
        if (!config.contains("level"))
        {
            throw std::runtime_error("Gzip configuration needs to contain a level");
        }

        m_level = config["level"].get<size_t>(); 
    }

    gzip::gzip(const size_t level) : m_level(level) {}

    std::vector<uint8_t> gzip::compress(std::vector<uint8_t>& data)
    {
        auto tmp_data = data;

        // We add 15 to ensure the compres sized is big enough as data can expand
        unsigned long compressed_size = data.size() + 15;

        std::vector<uint8_t> compressed(compressed_size);


        int result = compress2(compressed.data(), &compressed_size, data.data(), (unsigned long) data.size(), m_level);

        if (result != Z_OK)
        {
            throw std::runtime_error("Gzip error compressing data"); 
        }


        // TRUE: No compression achived
        if (tmp_data.size() <= static_cast<size_t>(compressed_size))
        {
            return tmp_data; 
        }

        tmp_data = std::vector<uint8_t>(compressed_size);
        std::memcpy(tmp_data.data(), compressed.data(), compressed_size);
        return tmp_data;        
    }

    std::vector<uint8_t> gzip::decompress(std::vector<uint8_t>& data, size_t size)
    {
        if (data.size() == size)
        {
            return data; 
        }

        auto tmp_data = data;         

        unsigned long decompressed_size = static_cast<unsigned long>(size); 
        std::vector<uint8_t> decompressed(size);

        int result = uncompress(decompressed.data(), &decompressed_size, data.data(), (unsigned long) data.size());

        if (result != Z_OK)
        {
            throw std::runtime_error("Gzip error uncompressing data"); 
        }

        if (tmp_data.size() <= decompressed.size())
        {
            return tmp_data; 
        }

        return decompressed; 
    }
}
