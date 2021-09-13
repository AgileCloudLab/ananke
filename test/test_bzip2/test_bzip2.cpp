#include <ananke/bzip2_compressor.hpp>

#include "../helpers.hpp"

#include <gtest/gtest.h>

#include <ctime>


TEST(test_bzip2, test_bzip2_compress_decompress_default)
{
    
    const size_t expected_size = 4096;
    ananke::bzip2 zipper(1, 0, 30);

    for (size_t i = 0; i < 10000; ++i)
    {
        auto data = generate_data(expected_size);
        auto EXPECTED = data;

        EXPECT_EQ(data, EXPECTED);
        
        auto compressed = zipper.compress(data);

        if (compressed.size() == EXPECTED.size())
        {
            EXPECT_EQ(EXPECTED, compressed);
        }
        else
        {
            EXPECT_NE(EXPECTED, compressed);
        }

        auto decompressed = zipper.decompress(compressed, expected_size);
    }
}

TEST(test_bzip2, test_bzip2_compress_decompress_default_zeros)
{
    
    const size_t expected_size = 16384;
    ananke::bzip2 zipper(1, 0, 30);

    for (size_t i = 0; i < 10000; ++i)
    {
        auto data = std::vector<uint8_t>(expected_size, 0); 
        auto EXPECTED = data;

        EXPECT_EQ(data, EXPECTED);
        
        auto compressed = zipper.compress(data);

        if (compressed.size() == EXPECTED.size())
        {
            EXPECT_EQ(EXPECTED, compressed);
        }
        else
        {
            EXPECT_NE(EXPECTED, compressed);
        }
    
        auto decompressed = zipper.decompress(compressed, expected_size);
    }
}




int main(int argc, char **argv) {
    srand(static_cast<uint32_t>(time(0)));
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
