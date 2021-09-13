#include "bzip2_compressor.hpp"

// BZLIB include 
#include <bzlib.h>

#include <fmt/core.h>

#include <cstring>

#include <stdexcept>

// Implementation is based on documentation https://www.cs.cmu.edu/afs/cs/project/pscico-guyb/realworld/99/code/bzip2-0.9.5c/manual_toc.html#TOC35

namespace ananke
{
    bzip2::bzip2(const int block_size, const int verbosity, const int work_factor) : m_block_size(block_size),
                                                                                                           m_verbosity(verbosity),
                                                                                                           m_work_factor(work_factor) {}
    

    std::pair<bool, std::vector<uint8_t>> bzip2::compress(std::vector<uint8_t>& data)
    {
        std::vector<uint8_t> org_data_backup = data;

        unsigned int source_length = data.size();

        // We add 20% to the destination length
        // It is not well document in bzip 2 what the value should be 
        unsigned int dest_length = data.size() + static_cast<unsigned int> (data.size() * 0.20);

        std::vector<uint8_t> compressed(dest_length);

        int result = BZ2_bzBuffToBuffCompress((char*) compressed.data(), &dest_length, (char*)data.data(),
                                              source_length, m_block_size, m_verbosity, m_work_factor);

        if (result != BZ_OK)
        {
            std::string msg = "Compression error: {}"; 
            if (result == BZ_PARAM_ERROR)
            {
                msg = fmt::format(msg, "Parameter error"); 
            }
            else if (result == BZ_MEM_ERROR)
            {
                msg = fmt::format(msg, "Memory error"); 
            }
            else if (result == BZ_OUTBUFF_FULL)
            {
                msg = fmt::format(msg, "Outbuffer is full"); 
            }
            // Todo throw error
            throw std::runtime_error(msg); 
        }

        if (dest_length >= source_length)
        {
            auto ret = std::make_pair(false, org_data_backup);
            return ret; 
        }
        org_data_backup.clear(); 

        if (compressed.size() > dest_length)
        {
            compressed.resize(dest_length); 
            // std::vector<uint8_t> compressed2(dest_length);
            // std::memcpy(compressed.data(), compressed.data(), dest_length);
            // return compressed2; 
        }

        auto ret = std::make_pair(true, compressed);
        return ret; 
    }

    std::vector<uint8_t> bzip2::decompress(std::vector<uint8_t>& data, const size_t size)
    {
        if (data.size() == size)
        {
            return data; 
        }
        unsigned int dest_length = size + static_cast<unsigned int> (size * 0.20);;
        std::vector<uint8_t> decompressed(dest_length);

        unsigned int source_length = data.size();

        // TODO: Validate the two last inputs
        int result = BZ2_bzBuffToBuffDecompress((char*) decompressed.data(), &dest_length, (char*) data.data(), source_length, 0, 0);

        if (result != BZ_OK)
        {
            std::string msg = "Decompression error: {}";
            if (result == BZ_CONFIG_ERROR)
            {
                msg = fmt::format(msg, "Configuration error");
            }
            else if (result == BZ_PARAM_ERROR)
            {
                msg = fmt::format(msg, "Parameter error"); 
            }
            else if (result == BZ_MEM_ERROR)
            {
                msg = fmt::format(msg, "Memory error"); 
            }
            else if (result == BZ_OUTBUFF_FULL)
            {
                msg = fmt::format(msg, "Outbuffer is full"); 
            }
            else if (result == BZ_DATA_ERROR)
            {
                msg = fmt::format(msg, "Data integrity broken"); 
            }
            else if (result == BZ_DATA_ERROR_MAGIC)
            {
                msg = fmt::format(msg, "Compressed data is missing the magic byte"); 
            }
            else if (result == BZ_UNEXPECTED_EOF)
            {
                msg = fmt::format(msg, "Unexpected EOF"); 
            }
            else
            {
                msg = fmt::format(msg, "Unknonw error: " + std::to_string(result) ); 
            }
            throw std::runtime_error(msg); 
        }

        if (decompressed.size() == size)
        {
            return decompressed; 
        }

        std::vector<uint8_t> decompressed2(size);
        std::memcpy(decompressed2.data(), decompressed.data(), size);
        return decompressed2;
        
    }
    

    void bzip2::block_size(const int new_block_size)
    {
        m_block_size = new_block_size; 
    }
    
    int bzip2::block_size() const
    {
        return m_block_size;
    }

    void bzip2::verbosity(const int new_verbosity)
    {
        m_verbosity = new_verbosity;
    }
    
    int bzip2::verbosity() const
    {
        return m_verbosity; 
    }

    void bzip2::work_factor(const int new_work_factor)
    {
        m_work_factor = new_work_factor; 
    }
    
    int bzip2::work_factor() const
    {
        return m_work_factor; 
    }
}
