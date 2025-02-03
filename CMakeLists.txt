cmake_minimum_required(VERSION 3.10)

project(RefactoredMinecraft)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/glm)

add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/vendor)

target_link_libraries(${PROJECT_NAME} 
    OpenGL::GL
    glfw
    glad
    glm
    imgui)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/shader
    ${CMAKE_BINARY_DIR}/bin/$<CONFIG>/shader
)