cmake_minimum_required(VERSION 3.18.1)

project(scop)

set(GCC_COVERAGE_COMPILE_FLAGS "-g")
set(GCC_COVERAGE_LINK_FLAGS "-g")

# Set GLFW directories
set(GLEW_ROOT "${CMAKE_SOURCE_DIR}/dependencies/glew-2.1.0")
set(glew_DIR "${GLEW_ROOT}/build/cmake")
set(GLEW_INCLUDE_DIR "${GLFW_ROOT}/include")
set(GLEW_LIBS "${GLEW_ROOT}/lib")

set(GLFW_ROOT "${CMAKE_SOURCE_DIR}/dependencies/glfw-3.3.8")
set(GLFW_INCLUDE_DIR "${GLFW_ROOT}/include")
set(GLFW_SRC_DIR "${GLFW_ROOT}/src")
set(GLFW_LIB_DIR "${GLFW_ROOT}/build/lib")

#set(CMAKE_CURRENT_SOURCE_DIR "./")

set(OpenGL_GL_PREFERENCE GLVND)

#add_subdirectory(${GLFW_ROOT})

find_package( OpenGL REQUIRED )

# Turn off compilation of docs, tests and examples for glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW lib only" FORCE)
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )


# Add executable target
add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/main.cpp)

set(CMAKE_BUILD_TYPE Debug)
include_directories(${CMAKE_SOURCE_DIR}/include ${OPENGL_INCLUDE_DIRS})

#target_include_directories(${PROJECT_NAME} 
#	${CMAKE_SOURCE_DIR}/include
#)

target_sources(${PROJECT_NAME} 
	PUBLIC "${CMAKE_SOURCE_DIR}/src/glad.c"
	PRIVATE "${CMAKE_SOURCE_DIR}/src/error_handling.cpp"
	PRIVATE "${CMAKE_SOURCE_DIR}/src/index_buffer.cpp"
	PRIVATE "${CMAKE_SOURCE_DIR}/src/vertex_buffer.cpp"
	PRIVATE "${CMAKE_SOURCE_DIR}/src/renderer.cpp"
	PRIVATE "${CMAKE_SOURCE_DIR}/src/vertex_array.cpp"
	PRIVATE "${CMAKE_SOURCE_DIR}/src/shader.cpp"
	PRIVATE "${CMAKE_SOURCE_DIR}/src/texture.cpp"
	PRIVATE "${CMAKE_SOURCE_DIR}/src/mesh.cpp"
	PRIVATE "include/vendor/stb_image/stb_image.cpp"
)

#TODO do I need src files?

target_link_libraries(${PROJECT_NAME} 
	glfw3
	OpenGL
	GL
	X11
	Xrandr
	udev
	pthread
	freetype
	${CMAKE_DL_LIBS}
)

