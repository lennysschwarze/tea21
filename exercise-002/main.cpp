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


    for(int i=0;i<counter;i++)
    {
        int_vct.push_back(std::rand() % 101);
    }

    fmt::print("Das ist der Vector:");

    for(int j=0;j<counter;j++)
    {
        fmt::print("{} ", int_vct[j]);
    }
    

    return 0;
/*
    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", app.get_name());

    /* INSERT YOUR CODE HERE */

    return 0; /* exit gracefully*/
}
