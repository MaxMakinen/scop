cmake_minimum_required(VERSION 3.18.1)
project(scop)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX TRUE)
endif()

set (CMAKE_CXX_STANDARD 14)
set(GCC_COVERAGE_COMPILE_FLAGS "-g")
set(GCC_COVERAGE_LINK_FLAGS "-g")

# Set SFML directories
set(SFML_ROOT dependencies/SFML-2.5.1)
set(SFML_INCLUDE_DIR ${SFML_ROOT}/include)
set(SFML_SRC_DIR ${SFML_ROOT}/src)
set(SFML_LIBRARY_DIR ${SFML_ROOT}/build/lib)

set(GLEW_ROOT dependencies/glew-2.1.0)
set(GLEW_INCLUDE_DIR ${GLEW_ROOT}/include)
set(GLEW_SRC_DIR ${GLEW_ROOT}/src)
set(GLEW_LIBRARY_DIR ${GLEW_ROOT}/lib)

set(CMAKE_CURRENT_SOURCE_DIR ./src)
list(APPEND CMAKE_PREFIX_PATH "/Users/mmakinen/scop/dependencies/glew-2.1.0")

set(SFML_DIR ${SFML_ROOT}/build)
set(GLEW_DIR ${GLEW_ROOT})
set(GLEW_LIBRARIES ${GLEW_LIBRARY_DIR})

add_subdirectory (${SFML_ROOT})

link_directories(${SFML_LIBRARY_DIR}
	${GLEW_LIBRARY_DIR}
	${GLEW_ROOT}
	${SFML_INCLUDE_DIR}
	${GLEW_INCLUDE_DIR}
	libs
	frameworks
	include
)
include_directories(${SFML_INCLUDE_DIR}
	${GLEW_INCLUDE_DIR}
	include
)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SFML 2.5.1 COMPONENTS system window)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)


target_sources(${PROJECT_NAME} 
	PRIVATE "$<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/error_handling.cpp>"
	PRIVATE "$<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/index_buffer.cpp>"
	PRIVATE "$<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/vertex_buffer.cpp>"
	PRIVATE "$<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/renderer.cpp>"
	PRIVATE "$<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/vertex_array.cpp>"
	PRIVATE "$<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/shader.cpp>"
	PRIVATE "$<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/texture.cpp>"
	PRIVATE "$<$<CONFIG:Debug>:include/vendor/stb_image/stb_image.cpp>"
)


target_include_directories(${PROJECT_NAME} 
	PRIVATE ${SFML_INCLUDE_DIR}
	PRIVATE ${GLEW_INCLUDE_DIR}
	PRIVATE include
)

target_link_directories(${PROJECT_NAME} 
	PRIVATE ${SFML_LIBRARY_DIR}
	PRIVATE ${SFML_SRC_DIR}
	PRIVATE dependencies/SFML-2.5.1/extlibs/libs-osx/Frameworks
	PRIVATE ${GLEW_LIBRARY_DIR}
	PRIVATE ${GLEW_SRC_DIR}
	PRIVATE include
	PRIVATE libs
	PRIVATE frameworks
)

if (${MACOSX})
	target_link_libraries(${PROJECT_NAME}
		"-framework OpenGL"
		"-framework Cocoa"
		"-framework GLUT"
		"-framework IOKit"
		"-framework Carbon"
		sfml-window
		sfml-system
		GLEW
		#GLEW::GLEW
		pthread
	)
else()
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
endif()

