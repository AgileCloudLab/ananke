#include "snappy.hpp"
#include <snappy.h>

#include <string>



namespace ananke
{
    // We have to apply the namespace as we otherwise class with snappy's namespace
    using namespace snappy;
    std::pair<bool, std::vector<uint8_t>> snappy::compress(const std::vector<uint8_t>& data)
    {
        std::string input(data.begin(), data.end());
        std::string output;

        // From the snappy namespace
        Compress(input.data(), input.size(), &output);

        if (output.size() == data.size())
        {
            return {false, data};
        }

        std::vector<uint8_t> compressed(output.begin(), output.end());
        return {true, compressed};
            
    }

    std::vector<uint8_t> snappy::decompress(const std::vector<uint8_t>& data, const size_t size)    
    {
        if (data.size() == size)
        {
            return data; 
        }

        std::string input(data.begin(), data.end());
        std::string output;

        // From the snappy namespace        
        Uncompress(input.data(), input.size(), &output);

        std::vector<uint8_t> decompressed(output.begin(), output.end());
        return decompressed; 
    }
}
