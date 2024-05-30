#include "pch.h"
#include "Canvas.h"
#include "Window/Window.h"
#include "Window/SDLUtil.h"
#include "Render/Commands/Clear.h"

void runProgram()
{
    rt::Window window;
    window.renderer.addCommand(std::make_unique<rt::cmd::Clear>(SDL_Color{25, 25, 25, 255}));
    window.renderer.render();
    sleep(2);
}

int main(int argc, char **argv)
{
    spdlog::log(spdlog::level::info, "Starting program...");
    if (rt::initSDL())
        runProgram();
    spdlog::log(spdlog::level::info, "Exiting program...");
    return 0;
}