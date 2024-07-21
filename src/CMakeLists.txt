file(GLOB_RECURSE CPP_FILES *.cpp)
include_directories(${PROJECT_SOURCE_DIR}/src)
add_executable(${PROJECT_NAME} ${CPP_FILES})

# Set the path to your custom clang-tidy configuration file
set(CLANG_TIDY_CONFIG_FILE ${PROJECT_SOURCE_DIR}/.clang-tidy)

# Check if clang-tidy is available
find_program(CLANG_TIDY_EXE NAMES "clang-tidy")

if(CLANG_TIDY_EXE)
    # Set the clang-tidy command with the custom configuration file
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE};-config-file=${CLANG_TIDY_CONFIG_FILE}")
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    message(STATUS "Using clang-tidy configuration: ${CLANG_TIDY_CONFIG_FILE}")
else()
    message(WARNING "clang-tidy not found!")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
    Boost::numeric_ublas
)

if (WIN32)
    target_link_libraries(
        ${PROJECT_NAME} PRIVATE SDL3main
    )
endif()

target_include_directories(
    GameOne PRIVATE
    lib/SDL/include
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}")
