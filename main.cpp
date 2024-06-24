
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader.hpp>
#include <iostream>

void framebuffer_size_callback(GLFWwindow * window, int width, int height){
	glViewport(0,0,width,height);
}

void processInput(GLFWwindow * window){
	
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window,true);
	}
}

int main() {

	// Initialize GLFW
	// --------------------------------------------------------------------------------
	if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

	//Using opengl 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
	// ---------------------------------------------------------------------------------
    GLFWwindow * window = glfwCreateWindow(800, 600, "PixelSmith", NULL, NULL);
    
	if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

	//Use GLAD to load function pointers
	//------------------------------------------------------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
    // Set the viewport size and the callback function for window resizing
    glViewport(0, 0, 800, 600);

	//Create Shaders and link them
	//-------------------------------------------------------------------------------------
	//Create a vertex Shader Object
	fs::path shaderDir = SHADER_DIR;
	fs::path vertexPath = shaderDir / "example2/offset_VS.glsl";
	fs::path fragmentPath = shaderDir / "example2/offset_FS.glsl";
	Shader shaderProgram(vertexPath, fragmentPath);
	/* shaderProgram.use(); */
	shaderProgram.setFloat("horizontalOffset", 0.5f);
	//Vertex Data, Buffers and attribute linking
	//-------------------------------------------------------------------------------------------------
	float vertices[] = {
		0.0f, 0.5f, 0.0f, 
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	//Generate a vertex buffer object and vertex array object
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	//Bind the vertex arrray object
	glBindVertexArray(VAO);

	//Bind the buffer object 
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/* glEnableVertexAttribArray(1); */
	
	//Since glVertexAttribPointer bounds the VBO to VAO we can unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // Render loop
	// -----------------------------------------------------------------------------
    while (!glfwWindowShouldClose(window)) {
		
		//Process Input
		//----------------------------------------------
		processInput(window);

        // Render here
		// ---------------------------------------------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set the clear color
        glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
		
		//Draw a triangle
		//----------------------------------------------
		shaderProgram.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

        // Swap front and back buffers and poll events
		// ---------------------------------------------
        glfwSwapBuffers(window);
		glfwPollEvents();
    }

    // Clean up and exit
	// -----------------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	shaderProgram.deleteProgram();
    glfwTerminate();

    return 0;
}
