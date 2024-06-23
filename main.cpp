
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0,0,width,height);
}

void processInput(GLFWwindow* window){
	
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window,true);
	}
}

int main() {

	std::cout << "Program Started" << std::endl;
    
	// Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

	//Using opengl 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "PixelSmith", NULL, NULL);
    
	if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	

    // Set the viewport size and the callback function for window resizing
    glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
		
		processInput(window);

        // Render here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set the clear color
        glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

        // Poll for and process events
        glfwPollEvents();
        // Swap front and back buffers
        glfwSwapBuffers(window);
    }

    // Clean up and exit
    glfwTerminate();
    return 0;
}
