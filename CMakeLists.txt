cmake_minimum_required(VERSION 3.10)
project(RefactoredMinecraft)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/)

include_directories(include vendor/GLAD/include)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/imgui)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "vendor/FastNoiseLite.h" "vendor/glad.c" "vendor/stb_image.h")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw)