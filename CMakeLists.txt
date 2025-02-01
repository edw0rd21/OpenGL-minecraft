cmake_minimum_required(VERSION 3.10)

# Project name and version
project(RefactoredMinecraft)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/)
set(GLFW_LIB "${CMAKE_SOURCE_DIR}/vendor/GLFW/lib/glfw3.lib")

include_directories(${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/vendor
	${CMAKE_SOURCE_DIR}/vendor/GLAD/include
	${CMAKE_SOURCE_DIR}/vendor/GLFW/include
	${CMAKE_SOURCE_DIR}/vendor/glm)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp"
	"vendor/imgui/*cpp"
	"src/glad.c")


find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} OpenGL::GL ${GLFW_LIB})