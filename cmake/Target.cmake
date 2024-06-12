
add_executable(${PROJECT_NAME} 
"src/main.cpp"
"src/Tracer/RaySpawner.cpp"
"src/Tracer/UV.cpp"
"src/Data/Material.cpp"
"src/Data/HittableObject.cpp"

)
target_precompile_headers(${PROJECT_NAME} PRIVATE "include/pch.h")
target_link_libraries(${PROJECT_NAME} PRIVATE "${EXTRA_LIBS}")
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
