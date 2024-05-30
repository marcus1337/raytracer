#include "pch.h"
#include "Canvas.h"
#include "Window/Window.h"
#include "Window/SDLUtil.h"
#include "Render/Commands/Clear.h"
#include "Render/Commands/Border.h"
#include "Window/TargetTexture.h"

std::vector<std::unique_ptr<rt::RenderCommand>> getRenderCommands()
{
    std::vector<std::unique_ptr<rt::RenderCommand>> commands;
    commands.push_back(std::make_unique<rt::cmd::Clear>(SDL_Color{100, 25, 25, 255}));
    commands.push_back(std::make_unique<rt::cmd::Border>(SDL_Rect{0, 0, 100, 50}, 10, SDL_Color{125, 125, 125, 255}));
    return commands;
}

bool handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return false;
        }
    }
    return true;
}

void runProgram()
{
    rt::Window window;
    window.renderer.addCommands(getRenderCommands());
    auto targetTexture = window.renderer.makeTargetTexture(rt::Size{500, 300});
    while (handleEvents())
    {
        spdlog::log(spdlog::level::info, "WINDOW: {} {}", window.getWidth(), window.getHeight());
        window.renderer.render(targetTexture, window.getSize());
        sleep(1);
    }
}

int main(int argc, char **argv)
{
    spdlog::log(spdlog::level::info, "Starting program...");
    if (rt::initSDL())
        runProgram();
    spdlog::log(spdlog::level::info, "Exiting program...");
    return 0;
}