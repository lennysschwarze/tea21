#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"
#include "bmp.h"

auto main(int argc, char **argv) -> int
{
    std::string filename{DEFAULT_BMP_FILE};
    /**
     * CLI11 is a command line parser to add command line options
     * More info at https://github.com/CLIUtils/CLI11#usage
     */
    CLI::App app{PROJECT_NAME};
    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        app.add_option("-f,--filename",filename,fmt::format("Enter filename "));
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */

    fmt::print("Hello, {}!\n", app.get_name());
    fmt::println("Entered filename {}",filename);

    /* INSERT YOUR CODE HERE */
    BMP bmp;
    std::vector<std::vector<pixel>> pixelMatrix;
    pixelMatrix = bmp.read(filename);
    //     for (size_t row = 30; row < 50; ++row) {
    //     // Iterate through columns
    //     for (size_t col = 0; col < 120; ++col) {
    //         std::cout << "Pixel at row " << row << ", column " << col << ": ";
    //         std::cout << "Red: " << static_cast<int>(pixelMatrix[row][col].red) << " ";
    //         std::cout << "Green: " << static_cast<int>(pixelMatrix[row][col].green) << " ";
    //         std::cout << "Blue: " << static_cast<int>(pixelMatrix[row][col].blue) << "\n";
    //     }
    // }
    std::vector< std::vector<char> > greypixelMatrix(pixelMatrix.size());
    uint8_t grey;
    pixel px;
    for (size_t row = 0; row < pixelMatrix.size(); row++)
    {
        greypixelMatrix[row].resize(pixelMatrix[0].size());
        for (size_t col = 0; col < pixelMatrix[row].size(); col++) {
            
            grey = px.grey(pixelMatrix[row][col].red,pixelMatrix[row][col].green,pixelMatrix[row][col].blue);
            if(grey>192)
            {
                greypixelMatrix[row][col] = ' ';

            }
            else if(grey>128)
            {
                greypixelMatrix[row][col] = '.';
            }
            else if(grey>64)
            {
                greypixelMatrix[row][col] = '/';
            }
            else
            {
                greypixelMatrix[row][col] = '#';
            }

        }
    }   

        // Print greypixelMatrix
    for (size_t row = greypixelMatrix.size()-1; row > 0 ; row--) {
        for (size_t col = 0; col < greypixelMatrix[row].size(); col++) 
        {
            fmt::print("{}",greypixelMatrix[row][col]);
        }
        fmt::print("\n");
    }
    
    
    return 0; /* exit gracefully*/
}
