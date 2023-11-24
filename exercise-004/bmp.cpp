#include "bmp.h"

std::vector<std::vector<pixel>> BMP::read(const std::string& filename)
{
    uint32_t offset;
    uint16_t color;
    uint32_t height;
    uint32_t width;
    std::ifstream infile(filename, std::ios::binary | std::ios::in);
    infile.seekg(10);
    infile.read(reinterpret_cast<char*>(&offset), sizeof(offset));
    infile.seekg(18);
    infile.read(reinterpret_cast<char*>(&width), sizeof(width));
    infile.seekg(22);
    infile.read(reinterpret_cast<char*>(&height), sizeof(height));
    infile.seekg(28);
    infile.read(reinterpret_cast<char*>(&color), sizeof(color));
    fmt::print("offset:{}\nwidth:{}\nheight:{}\ncolordepth:{}\n", offset, width, height, color);
    // uint32_t bytestopad = (width * (color / 3)) % 4;
    uint32_t bytestopad = (width * 3) % 4;
    uint32_t current_pos = offset;
    //fmt::print("bytestopad:{}",bytestopad);

    pixel pi;
    std::vector<std::vector<pixel>> pixelBuffer(height);
    //uint32_t padding_bytes;
    for (int row = 0; row < height; row++)
    {
        infile.seekg(current_pos);
        pixelBuffer[row].resize(width);
        for (int column = 0; column < width; column++)
        {
            infile.read(reinterpret_cast<char*>(&pi.red), sizeof(pi.red));
            infile.read(reinterpret_cast<char*>(&pi.green), sizeof(pi.green));
            infile.read(reinterpret_cast<char*>(&pi.blue), sizeof(pi.blue));
            pixelBuffer[row][column] = pi;
            
        }
        // Padding
        current_pos = infile.tellg() + bytestopad;
        //fmt::print("Current pos {}", current_pos);
        // infile.read(reinterpret_cast<char*>(&padding_bytes), bytestopad);
    }
    // infile.seekg(54);

    return pixelBuffer;
};
bool BMP::write(const std::string& filename)
{
    auto ret = false;
    /*    ifstream infile;
    infile.open("./example/DHBW_24bit.bmp");
    */
    return ret;
}

uint8_t pixel::grey(uint8_t red, uint8_t blue, uint8_t green)
{
    uint8_t grey = (red + green + blue) / 3;
    return grey;
};