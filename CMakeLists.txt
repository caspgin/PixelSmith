cmake_minimum_required(VERSION 3.30.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(PixelSmith)

#Set c++ Standard to 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#print out c++ standard and flags
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler flags: ${CMAKE_CXX_FLAGS}")

#Set Shader dir and sent to code
set(SHADER_DIR "${CMAKE_SOURCE_DIR}/shaders" CACHE PATH "Path to shader files")
add_compile_definitions(SHADER_DIR="${SHADER_DIR}")

#Add external libraries
add_subdirectory(thirdParty/glad)
add_subdirectory(external/glfw)
add_subdirectory(customLib/shaderLib)

#Add executable
add_executable(${PROJECT_NAME} main.cpp)

#Include directories
target_include_directories(${PROJECT_NAME} 
	PUBLIC external/glfw/include
)

#Link Libraries
target_link_libraries(${PROJECT_NAME} glad glfw shaderLib)

