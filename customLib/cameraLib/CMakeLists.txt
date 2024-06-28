add_library(camera ./src/camera.cpp)

target_include_directories(camera 
	PUBLIC ./include
	PUBLIC ../../external/glm
	PUBLIC ../../external/glfw/include
)
