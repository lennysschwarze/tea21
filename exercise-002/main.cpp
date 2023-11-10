#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"

auto main(int argc, char **argv) -> int
{
   int counter=20;
   std::vector <int> int_vct;

    /**
     * CLI11 is a command line parser to add command line options
     * More info at https://github.com/CLIUtils/CLI11#usage
     */
    CLI::App app{PROJECT_NAME};
    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        app.add_option("-c,--count", counter, "A help string");
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }

    fmt::print("Eingabe des Counters: {}\n",counter);

    std::srand(std::time(nullptr));

    for(int i=0;i<counter;i++)
    {
        int_vct.push_back(std::rand() % 101);
    }

    fmt::print("Das ist der Vektor: ");

    for(int j=0;j<counter;j++)
    {
        fmt::print("{} ", int_vct[j]);
    }

    auto start = std::chrono::system_clock::now();
    sort(int_vct.begin(), int_vct.end());
    auto end = std::chrono::system_clock::now();
    auto elapsed = end - start;
    //auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    fmt::print("\nDas ist der sortierte Vektor: ");

    for(int k=0;k<counter;k++)
    {
        fmt::print("{} ", int_vct[k]);
    }
    
    fmt::print("\ntime elapsed: {}", elapsed);
    
    return 0;

}
