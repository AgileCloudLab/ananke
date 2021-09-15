#include <ananke/bzip2.hpp>

#include "../../test/helpers.hpp"

#include <fmt/core.h>

#include <cstdint>
#include <vector>

#include <chrono>
#include <ctime>
#include <algorithm>


std::vector<std::vector<uint8_t>> generate_chunks(const size_t num_chunks, const size_t size)
{
    std::vector<std::vector<uint8_t>> data;

    for (size_t i = 0; i < num_chunks; ++i)
    {
        data.emplace_back(generate_data(size)); 
    }
    return data; 
}

// std::vector<std::vector<uint8_t>> generate_none_random(const size_t num_chunks, const size_t size, const std::vector<uint8_t> pattern)
// {
//     return {{}}; 
// }

void random_experiment(const size_t num_chunks, const size_t size)
{
    auto chunks = generate_chunks(num_chunks, size);

    std::vector<std::vector<uint8_t>> compressed;
    size_t compressed_size = 0;

    uint64_t total_compress_time = 0; 
    
    ananke::bzip2 zipper(1, 0, 30);

    for (auto& chunk : chunks)
    {
        auto t1 = std::chrono::high_resolution_clock::now();
        auto c_chunk = zipper.compress(chunk);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto res = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

        total_compress_time = total_compress_time + res.count(); 
        
        compressed_size = compressed_size + c_chunk.second.size();
        compressed.emplace_back(c_chunk.second); 
    }

    chunks.clear();

    uint64_t total_decompress_time = 0;
    

    
    for (auto& chunk : compressed)
    {
        auto t3 = std::chrono::high_resolution_clock::now();
        zipper.decompress(chunk, size); 
        auto t4 = std::chrono::high_resolution_clock::now();
        auto res = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3);
        
        total_decompress_time = total_decompress_time + res.count();  
    }

    compressed.clear();

    fmt::print("Running full random data experiment\n");
    fmt::print("Number of chunks: {} chunk size in bytes: {}\n", num_chunks, size); 
    fmt::print("Number of bytes before compression: {}\n", (num_chunks * size));
    fmt::print("Number of bytes after compression: {}\n", compressed_size);
    fmt::print("Compression throughput: {}MB/s\n", ((num_chunks * size) / double(total_compress_time))); 
    fmt::print("Compression gain: {}\n", ((num_chunks * size) / float(compressed_size)));
    fmt::print("Decompress throughput: {}MB/s\n", ((num_chunks * size) / double(total_decompress_time)));   
}

int main(void)
{
    srand(static_cast<uint32_t>(time(0)));
    random_experiment(10000, 4096);
     
    random_experiment(10000, 8192);
    
    random_experiment(10000, 16384);        
}
