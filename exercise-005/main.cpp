#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"
#include <chrono>
#include <thread>
#include <iostream>


void getInput(int* BTN_p, int* ES_Buff, int* ES_Bottom, int* ES_top)
{
    fmt::print("Geben Sie hier den BTN-State ein: \n");
    std::cin >> *BTN_p;
    fmt::print("Geben Sie hier den ES-State ein: (0: kein ES, 1: ES_top=1, 2: ES_bottom=1) \n");
    std::cin >> *ES_Buff;
    if (*ES_Buff==0)
    {
        *ES_Bottom = 0;
        *ES_top = 0;
    }
    else if (*ES_Buff==1)
    {
        *ES_Bottom = 0;
        *ES_top = 1;
    }
    else if (*ES_Buff==2)
    {
        *ES_Bottom = 1;
        *ES_top = 0;
    }
};

typedef enum {TorState_Auf = 0,
    TorState_Stop_Top = 1,
    TorState_Stop_Bottom = 2,
    TorState_Runter = 3,
    DB_STATE_MAX} TorState;

TorState state = TorState_Auf;

void stateMachine(int* BTN_p, int* ES_Buff, int* ES_Bottom, int* ES_top)
{
    switch (state)
    {
        case TorState_Auf:
        if (1 == *BTN_p)
        {
            state=TorState_Runter;
        }
        else if (1 == *ES_top)
        {
            state = TorState_Stop_Top;
        }
        break;
        case TorState_Runter:
        if (1==*BTN_p)
        {
            state=TorState_Auf;
        }
        else if (1==*ES_Bottom)
        {
            state=TorState_Stop_Bottom;
        }
        break;
        case TorState_Stop_Top:
        if (1==*BTN_p)
        {
            state=TorState_Runter;
        }
        break;
        case TorState_Stop_Bottom:
        if (1==*BTN_p)
        {
            state=TorState_Auf;
        }
        break;
    }

}

void printState ()
{
    fmt::print("Der aktuelle Status ist: {}\n",(int)state);
    return;
};

auto main(int argc, char **argv) -> int
{

    int ES_top;
    int ES_Bottom;
    int ES_Buff;
    int BTN;
    int* BTN_p = &BTN;
    int* ES_Buff_p = &ES_Buff;
    int* ES_Bottom_p = &ES_Bottom;
    int* ES_top_p = &ES_top;
    

    while(1==1)
    {
        using namespace std::chrono_literals;
        getInput(BTN_p, ES_Buff_p, ES_Bottom_p, ES_top_p);
        stateMachine(BTN_p, ES_Buff_p, ES_Bottom_p, ES_top_p);
        printState();
        const auto start = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(2000ms);
        const auto end = std::chrono::high_resolution_clock::now();

    }

    return 0; /* exit gracefully*/
}
