file(GLOB_RECURSE CPP_FILES *.cpp)
include_directories(${PROJECT_SOURCE_DIR}/src/include)
add_executable(${PROJECT_NAME} ${CPP_FILES})

# third party libs
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
    SDL3_mixer::SDL3_mixer
    Boost::geometry
    Boost::property_tree
)
# clang-tidy setup
find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if(CLANG_TIDY_EXE)
    set(CLANG_TIDY_CONFIG_FILE ${PROJECT_SOURCE_DIR}/.clang-tidy)
    # --extra-arg-before=-Wno-missing-template-arg-list-after-template-kw need for lint boost without error
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE};-config-file=${CLANG_TIDY_CONFIG_FILE};--extra-arg-before=-Wno-missing-template-arg-list-after-template-kw")
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    message(STATUS "Using clang-tidy configuration: ${CLANG_TIDY_CONFIG_FILE}")
else()
    message(WARNING "clang-tidy not found!")
endif()

if(CHECK_TIDY)
    message(STATUS "clang-tidy active")
    set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}")
elseif()
    message(WARNING "clang-tidy lint skipped")
endif()
