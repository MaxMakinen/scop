cmake_minimum_required(VERSION 3.18.1)
project(scop)

# Set SFML directories
set(GLEW_ROOT "./dependencies/glew-2.1.0")
set(SFML_ROOT "./dependencies/SFML-2.5.1")
set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
set(SFML_SRC_DIR "${SFML_ROOT}/src")

# Add executable target
add_executable(${PROJECT_NAME}  src/main.cpp)

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

