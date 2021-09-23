#include <ananke/snappy.hpp>

#include "../helpers.hpp"

#include <gtest/gtest.h>

#include <ctime>


TEST(test_snappy, test_snappy_compress_decompress_default)
{
    
    const size_t expected_size = 4096;
    ananke::snappy zipper;

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

TEST(test_snappy, test_snappy_compress_decompress_default_zeros_and_a_one)
{
    
    const size_t expected_size = 16384;
    ananke::snappy zipper;

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




int main(int argc, char **argv) {
    srand(static_cast<uint32_t>(time(0)));
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
