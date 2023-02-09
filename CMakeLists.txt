cmake_minimum_required(VERSION 3.18.1)
project(scop)

set(GCC_COVERAGE_COMPILE_FLAGS "-g")
set(GCC_COVERAGE_LINK_FLAGS "-g")

# Set SFML directories
set(GLEW_ROOT "./dependencies/glew-2.1.0")
set(SFML_ROOT "./dependencies/SFML-2.5.1")
set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
set(SFML_SRC_DIR "${SFML_ROOT}/src")
set(CMAKE_CURRENT_SOURCE_DIR "./src")

# Add executable target
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

target_sources(${PROJECT_NAME} 
	PRIVATE "$<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/error_handling.cpp>"
	PRIVATE "$<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/index_buffer.cpp>"
	PRIVATE "$<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/vertex_buffer.cpp>"
	PRIVATE "$<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/renderer.cpp>"
	PRIVATE "$<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/vertex_array.cpp>"
)

set(CMAKE_BUILD_TYPE Debug)

# add_subdirectory(dependencies/SFML-2.5.1)

target_include_directories(${PROJECT_NAME} 
	PRIVATE ${SFML_ROOT}/include
	PRIVATE ${GLEW_ROOT}/include
	PRIVATE include
)

target_link_directories(${PROJECT_NAME} 
	PRIVATE ${SFML_ROOT}/build/lib
	PRIVATE ${SFML_ROOT}/src
	PRIVATE ${GLEW_ROOT}/lib
	PRIVATE ${GLEW_ROOT}/src
	PRIVATE include
)

target_link_libraries(${PROJECT_NAME} 
	sfml-window-s-d
	sfml-system-s-d
	GLEW
	GL
	X11
	Xrandr
	udev
	pthread
	freetype
)

