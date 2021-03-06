#include <ananke/ananke.hpp>

#include "../helpers.hpp"

#include <nlohmann/json.hpp>

#include <gtest/gtest.h>

#include <ctime>


TEST(test_ananke, test_ananke_bzip2_compress_decompress_default)
{
    
    const size_t expected_size = 4096;

    nlohmann::json config;

    config["block_size"] = 1;
    config["verbosity"] = 0;
    config["work_factor"] = 30;

    auto zipper = ananke::zipper_factory<ananke::bzip2>(config); 

    for (size_t i = 0; i < 10000; ++i)
    {
        auto data = generate_data(expected_size);
        auto EXPECTED = data;

        EXPECT_EQ(data, EXPECTED);
        
        auto compressed = zipper.compress(data);

        if (compressed.second.size() == EXPECTED.size())
        {
            EXPECT_EQ(EXPECTED, compressed.second);
        }
        else
        {
            EXPECT_NE(EXPECTED, compressed.second);
        }

        auto decompressed = zipper.decompress(compressed.second, expected_size);
        EXPECT_EQ(EXPECTED, decompressed);         
    }
}

TEST(test_ananke, test_ananke_bzip2_compress_decompress_default_zeros_and_a_one)
{
    
    const size_t expected_size = 16384;

    nlohmann::json config;

    config["block_size"] = 1;
    config["verbosity"] = 0;
    config["work_factor"] = 30;

    auto zipper = ananke::zipper_factory<ananke::bzip2>(config);     

    for (size_t i = 0; i < 10000; ++i)
    {
        auto data = std::vector<uint8_t>(expected_size, 0);
        data.at(i) = 1; 
        auto EXPECTED = data;

        EXPECT_EQ(data, EXPECTED);
        
        auto compressed = zipper.compress(data);

        if (compressed.second.size() == EXPECTED.size())
        {
            EXPECT_EQ(EXPECTED, compressed.second);
        }
        else
        {
            EXPECT_NE(EXPECTED, compressed.second);
        }
    
        auto decompressed = zipper.decompress(compressed.second, expected_size);
        EXPECT_EQ(EXPECTED, decompressed);         
    }
}

TEST(test_ananke, test_ananke_snappy_compress_decompress_default)
{
    
    const size_t expected_size = 4096;


    auto zipper = ananke::zipper_factory<ananke::snappy>(); 

    for (size_t i = 0; i < 10000; ++i)
    {
        auto data = generate_data(expected_size);
        auto EXPECTED = data;

        EXPECT_EQ(data, EXPECTED);
        
        auto compressed = zipper.compress(data);

        if (compressed.second.size() == EXPECTED.size())
        {
            EXPECT_EQ(EXPECTED, compressed.second);
        }
        else
        {
            EXPECT_NE(EXPECTED, compressed.second);
        }

        auto decompressed = zipper.decompress(compressed.second, expected_size);
        EXPECT_EQ(EXPECTED, decompressed);         
    }
}

TEST(test_ananke, test_ananke_snappy_compress_decompress_default_zeros_and_a_one)
{
    
    const size_t expected_size = 16384;

    auto zipper = ananke::zipper_factory<ananke::snappy>();     

    for (size_t i = 0; i < 10000; ++i)
    {
        auto data = std::vector<uint8_t>(expected_size, 0);
        data.at(i) = 1; 
        auto EXPECTED = data;

        EXPECT_EQ(data, EXPECTED);
        
        auto compressed = zipper.compress(data);

        if (compressed.second.size() == EXPECTED.size())
        {
            EXPECT_EQ(EXPECTED, compressed.second);
        }
        else
        {
            EXPECT_NE(EXPECTED, compressed.second);
        }
    
        auto decompressed = zipper.decompress(compressed.second, expected_size);
        EXPECT_EQ(EXPECTED, decompressed);         
    }
}


TEST(test_gzip, test_gzip_compress_decompress_default)
{
    
    const size_t expected_size = 16384;

    nlohmann::json config;
    config["level"] = 6;
    
    auto zipper = ananke::zipper_factory<ananke::gzip>(config); 

    for (size_t i = 0; i < 10000; ++i)
    {
        auto data = generate_data(expected_size);
        auto EXPECTED = data;

        EXPECT_EQ(data, EXPECTED);
        
        auto compressed = zipper.compress(data);

        if (compressed.second.size() == EXPECTED.size())
        {
            EXPECT_EQ(EXPECTED, compressed.second);
        }
        else
        {
            EXPECT_NE(EXPECTED, compressed.second);
        }
    

        auto decompressed = zipper.decompress(compressed.second, expected_size);
        EXPECT_EQ(EXPECTED, decompressed); 
    }
}

TEST(test_ananke, test_ananke_gzip_compress_decompress_default_zeros)
{
    
    const size_t expected_size = 16384;

    nlohmann::json config;
    config["level"] = 6;
    
    auto zipper = ananke::zipper_factory<ananke::gzip>(config);     

    for (size_t i = 0; i < 10000; ++i)
    {
        auto data = std::vector<uint8_t>(expected_size, 0); 
        auto EXPECTED = data;

        EXPECT_EQ(data, EXPECTED);
        
        auto compressed = zipper.compress(data);

        if (compressed.second.size() == EXPECTED.size())
        {
            EXPECT_EQ(EXPECTED, compressed.second);
        }
        else
        {
            EXPECT_NE(EXPECTED, compressed.second);
        }
    
        auto decompressed = zipper.decompress(compressed.second, expected_size);
        EXPECT_EQ(EXPECTED, decompressed);         
    }
}

TEST(test_ananke, test_ananke_gzip_ananke_compress_decompress_default_zeros)
{
    
    const size_t expected_size = 16384;

    nlohmann::json config;
    config["level"] = 6;

    for (size_t i = 0; i < 10000; ++i)
    {
        auto data = std::vector<uint8_t>(expected_size, 0); 
        auto EXPECTED = data;

        EXPECT_EQ(data, EXPECTED);
        
        auto compressed = ananke::compress(ananke::algorithm::GZIP, config, data); 

        if (compressed.second.size() == EXPECTED.size())
        {
            EXPECT_EQ(EXPECTED, compressed.second);
        }
        else
        {
            EXPECT_NE(EXPECTED, compressed.second);
        }
    
        auto decompressed = ananke::decompress(ananke::algorithm::GZIP, config, compressed.second, expected_size);
        EXPECT_EQ(EXPECTED, decompressed); 
    }
}

TEST(test_ananke, test_ananke_bzip2_ananke_compress_decompress_default_zeros)
{
    
    const size_t expected_size = 16384;

    nlohmann::json config;

    config["block_size"] = 1;
    config["verbosity"] = 0;
    config["work_factor"] = 30;


    for (size_t i = 0; i < 10000; ++i)
    {
        auto data = std::vector<uint8_t>(expected_size, 0); 
        auto EXPECTED = data;

        EXPECT_EQ(data, EXPECTED);
        
        auto compressed = ananke::compress(ananke::algorithm::BZIP2, config, data); 

        if (compressed.second.size() == EXPECTED.size())
        {
            EXPECT_EQ(EXPECTED, compressed.second);
        }
        else
        {
            EXPECT_NE(EXPECTED, compressed.second);
        }
    
        auto decompressed = ananke::decompress(ananke::algorithm::BZIP2, config, compressed.second, expected_size);
        EXPECT_EQ(EXPECTED, decompressed); 
    }
}

TEST(test_ananke, test_ananke_snappy_ananke_compress_decompress_default_zeros)
{
    
    const size_t expected_size = 16384;

    nlohmann::json config;

    for (size_t i = 0; i < 10000; ++i)
    {
        auto data = std::vector<uint8_t>(expected_size, 0); 
        auto EXPECTED = data;

        EXPECT_EQ(data, EXPECTED);
        
        auto compressed = ananke::compress(ananke::algorithm::SNAPPY, config, data); 

        if (compressed.second.size() == EXPECTED.size())
        {
            EXPECT_EQ(EXPECTED, compressed.second);
        }
        else
        {
            EXPECT_NE(EXPECTED, compressed.second);
        }
    
        auto decompressed = ananke::decompress(ananke::algorithm::SNAPPY, config, compressed.second, expected_size);
        EXPECT_EQ(EXPECTED, decompressed); 
    }
}


int main(int argc, char **argv) {
    srand(static_cast<uint32_t>(time(0)));
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
