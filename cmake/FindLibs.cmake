

set(MIMALLOC_BUILD_SHARED OFF CACHE BOOL "" FORCE)

find_package(mimalloc REQUIRED)
find_package(spdlog REQUIRED)
find_package(TBB REQUIRED)
find_package(glm REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

list(APPEND EXTRA_LIBS mimalloc)
list(APPEND EXTRA_LIBS spdlog::spdlog)
list(APPEND EXTRA_LIBS TBB::tbb)
list(APPEND EXTRA_LIBS SDL2::SDL2 SDL2_image::SDL2_image)

if(UNIX)
find_program(CCACHE_PROGRAM ccache)
find_program(LLD_PROGRAM lld)

    if(CCACHE_PROGRAM)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
        message(STATUS "ccache found: ${CCACHE_PROGRAM}")
    else()
        message(STATUS "ccache not found")
    endif()
    if(LLD_PROGRAM)
        message(STATUS "lld found: ${LLD_PROGRAM}")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld")
    else()
        message(STATUS "lld not found")
    endif()
endif()
