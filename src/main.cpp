#include "pch.h"
#include "Window/SDLUtil.h"
#include "Window/Loop.h"
#include "Data/Tracing/Ray.h"
#include "Tracer/RaySpawner.h"
#include "Tracer/CanvasMaker.h"

int main(int argc, char **argv)
{
    spdlog::log(spdlog::level::info, "Starting program...");
    if (rt::initSDL())
    {
        rt::Loop loop;
        loop.run();
    }
    spdlog::log(spdlog::level::info, "Exiting program...");
    return 0;
}