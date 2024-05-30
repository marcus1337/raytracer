#include "pch.h"

int main(int argc, char **argv)
{
    spdlog::log(spdlog::level::info, "Starting program...");

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cerr << "Failed to initialize SDL_image: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    glm::vec3 arr_test;

    spdlog::log(spdlog::level::info, "Exiting program...");
    return 0;
}