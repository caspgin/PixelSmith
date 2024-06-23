cmake_minimum_required(VERSION 3.30.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(PixelSmith)

#Add external libraries
add_subdirectory(thirdParty/glad)
add_subdirectory(external/glfw)

#Add executable
add_executable(${PROJECT_NAME} main.cpp)

#Include directories
target_include_directories(${PROJECT_NAME} 
	PUBLIC external/glfw/include
)

target_link_libraries(${PROJECT_NAME} glad glfw)
