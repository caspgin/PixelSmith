add_library(shaderLib ./src/shader.cpp)

target_include_directories(shaderLib 
	PUBLIC include
	PUBLIC ../../thirdParty/glad/include
	PUBLIC ../../external/glm
)

