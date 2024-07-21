file(GLOB_RECURSE CPP_FILES *.cpp)
include_directories(${PROJECT_SOURCE_DIR}/src)
add_executable(${PROJECT_NAME} ${CPP_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf)
if (WIN32)
	target_link_libraries(
		${PROJECT_NAME} PRIVATE SDL3main
	)
endif()

target_include_directories(
	GameOne PRIVATE
	lib/SDL/include
)
