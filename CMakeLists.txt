cmake_minimum_required(VERSION 3.16)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_STANDARD 23)

project(GameOne VERSION 0.1)

# Black magic from one internet guy, need for run SDL3_image 
# (Probably usefull only for MacOS)
enable_language(OBJC)

add_subdirectory(lib/SDL)
add_subdirectory(lib/SDL_mixer)
add_subdirectory(lib/SDL_image)
add_subdirectory(lib/SDL_ttf)
add_subdirectory(lib/boost)
add_subdirectory(src)
