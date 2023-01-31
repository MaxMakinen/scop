cmake_minimum_required(VERSION 3.0)
project(scop)

# Set SFML directories
set(SFML_ROOT "/SFML-2.5.1")
set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
set(SFML_SRC_DIR "${SFML_ROOT}/src")

# Build SFML statically
add_library(sfml-static STATIC 
    "${SFML_SRC_DIR}/SFML/Window/*.cpp"
  #  "${SFML_SRC_DIR}/SFML/System/InputStream.cpp"
    # ... # Add other required SFML source files here
)

# Include SFML headers
target_include_directories(sfml-static PUBLIC "${SFML_INCLUDE_DIR}")

# Link SFML libraries
target_link_libraries(sfml-static
    # ... # Add any required system libraries here
)

# Add executable target
add_executable(scop src/main.cpp)

# Link target with SFML static library
target_link_libraries(scop sfml-static)