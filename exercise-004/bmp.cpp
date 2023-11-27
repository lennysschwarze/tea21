#include "bmp.h"

std::vector<std::vector<pixel>> BMP::read(const std::string& filename)
{
    uint32_t offset;
    uint16_t color;
    uint32_t height;
    uint32_t width;
    /*
    uint8_t  pad1;
    uint8_t  pad2;
    uint8_t  pad3;
    */
    std::ifstream infile(filename, std::ios::binary | std::ios::in);
    infile.seekg(10);  //bytes 10 to 14 are the amount of offset bytes till pixel data begins 
    infile.read(reinterpret_cast<char*>(&offset), sizeof(offset));
    infile.seekg(18);  //reading of the picture width 
    infile.read(reinterpret_cast<char*>(&width), sizeof(width));
    infile.seekg(22);  //reading of the picture hight 
    infile.read(reinterpret_cast<char*>(&height), sizeof(height));
    infile.seekg(28);  // reading of the color depth (24Bit)
    infile.read(reinterpret_cast<char*>(&color), sizeof(color));
    fmt::print("offset:{}\nwidth:{}\nheight:{}\ncolordepth:{}\n", offset, width, height, color);

    uint32_t bytestopad = 4-((width * 3) % 4); 
    uint32_t current_pos = offset;
    //fmt::print("bytestopad:{}",bytestopad);

    /*
    infile.seekg(639);
    infile.read(reinterpret_cast<char*>(&pad1), sizeof(pad1));
    infile.read(reinterpret_cast<char*>(&pad2), sizeof(pad2));
    infile.read(reinterpret_cast<char*>(&pad3), sizeof(pad3));
    
    fmt::print("pad1:{}\npad2:{}\npad3:{}\n", pad1, pad2, pad3);
    */

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
        //infile.read(reinterpret_cast<char*>(&bytestopad), bytestopad);
    }
    
    return pixelBuffer;
};

uint8_t pixel::grey(uint8_t red, uint8_t blue, uint8_t green)
{
    uint8_t grey = (red + green + blue) / 3;
    return grey;
};

bool BMP::write(std::vector< std::vector<char> > greypixelMatrix)
{
    auto ret = false;
    /*    ifstream infile;
    infile.open("./example/DHBW_24bit.bmp");
    */
    std::ofstream outfile;
    outfile.open("/workspaces/tea21/exercise-004/greyscale.txt");

    for (size_t row = greypixelMatrix.size()-1; row > 0 ; row--) {
        for (size_t col = 0; col < greypixelMatrix[row].size(); col++) 
        {
            fmt::print("{}",greypixelMatrix[row][col]);
            outfile << greypixelMatrix[row][col];
        }
        fmt::print("\n");
        outfile << "\n";
    }

    outfile.close();

    return ret;
}