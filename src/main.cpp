#include "pch.h"
#include "Canvas.h"
#include "Window/Window.h"
#include "Window/SDLUtil.h"

void runProgram()
{
    rt::Window window;
    sleep(1);
}

int main(int argc, char **argv)
{
    spdlog::log(spdlog::level::info, "Starting program...");
    if (rt::initSDL())
        runProgram();
    spdlog::log(spdlog::level::info, "Exiting program...");
    return 0;
}