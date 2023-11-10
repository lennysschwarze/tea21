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

    printf("Eingabe des Counters: %d\n",counter);

    std::srand(std::time(nullptr));
    
    for(int i=0;i<counter;i++)
    {
        int_vct.push_back(std::rand() % 101);
    }

    fmt::print("Das ist der Vector:");

    for(int j=0;j<counter;j++)
    {
        fmt::print("{} ", int_vct[j]);
    }

    sort(int_vct.begin(), int_vct.end());
    
    fmt::print("\nDas ist der sortierte Vector:");

    for(int k=0;k<counter;k++)
    {
        fmt::print("{} ", int_vct[k]);
    }
    
    return 0;

}
