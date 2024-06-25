
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/trigonometric.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glad/glad.h>
#include <stb_image.h>
#include <GLFW/glfw3.h>
#include <Shader.hpp>
#include <iostream>
#include <glm/glm.hpp>


void framebuffer_size_callback(GLFWwindow * window, int width, int height);
void processInput(GLFWwindow * window);
void textureGenNLoad( unsigned int & texture, std::string imageFileName, GLenum dtype  );


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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
	
    GLFWwindow * window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "PixelSmith", NULL, NULL);
    
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
    /* glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); */

	glEnable(GL_DEPTH_TEST);

	//Create Shaders and link them
	//-------------------------------------------------------------------------------------
	//Create a vertex Shader Object
	fs::path shaderDir = SHADER_DIR;
	fs::path vertexPath = shaderDir / "example5/Texture_VS.glsl";
	fs::path fragmentPath = shaderDir / "example5/Texture_FS.glsl";
	Shader shaderProgram(vertexPath, fragmentPath);

	//Texture generation
	//------------------------------------------------------------------------------------------------
	unsigned int texture[2];
	glGenTextures(2, texture);

	textureGenNLoad(texture[0], "/container.jpg", GL_RGB);
	textureGenNLoad(texture[1], "/awesomeface.png", GL_RGBA);

	shaderProgram.use();
	shaderProgram.setInt("texture1", 0);
	shaderProgram.setInt("texture2", 1);
	
	//Vertex Data, Buffers and attribute linking
	//-------------------------------------------------------------------------------------------------

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

	//Generate a vertex buffer object and vertex array object
	unsigned int VBO, VAO ;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	/* glGenBuffers(1, &BO); */
	
	//Bind the vertex arrray object
	glBindVertexArray(VAO);

	//Bind the buffer object 
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	/* glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BO); */
	/* glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); */

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	

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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color & depth buffer
		
		//Draw a triangle
		//----------------------------------------------

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		

		shaderProgram.use();
		
		glm::mat4 model			= glm::mat4(1.0f);
		glm::mat4 view			= glm::mat4(1.0f);
		glm::mat4 projection	= glm::mat4(1.0f);
		model = glm::rotate(model, (float) glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f,1.0f,0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		/* projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/ (float) SCR_HEIGHT, 0.1f, 100.0f); */
		projection = glm::ortho(-1.0f,1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
		shaderProgram.setMat4("model", model);
		shaderProgram.setMat4("view", view);
		shaderProgram.setMat4("projection", projection);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		/* glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); */
		
		
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
	/* glDeleteBuffers(1, &BO,); */
	shaderProgram.deleteProgram();
    glfwTerminate();

    return 0;
}


void framebuffer_size_callback(GLFWwindow * window, int width, int height){
	glViewport(0,0,width,height);
} 

void processInput(GLFWwindow * window){
	
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window,true);
	}
}

void textureGenNLoad( unsigned int & texture, std::string imageFileName, GLenum dtype  ){
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	std::string imageFilePath = std::string(TEXTURE_DIR) + imageFileName;
	stbi_set_flip_vertically_on_load(true);
	unsigned char * data = stbi_load(imageFilePath.c_str(), &width, &height, &nrChannels, 0);
	if(data){
		glTexImage2D(GL_TEXTURE_2D, 0, dtype, width, height, 0, dtype, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}else{
		std::cout << "Failed to load texture " << std::endl;
	}
	stbi_image_free(data);
}
