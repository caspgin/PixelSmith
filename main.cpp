
#include "glm/trigonometric.hpp"
#include <cmath>
#include <glm/ext/matrix_transform.hpp>
#include <glad/glad.h>
#include <stb_image.h>
#include <GLFW/glfw3.h>
#include <Shader.hpp>
#include <iostream>
#include <glm/glm.hpp>

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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
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
	fs::path vertexPath = shaderDir / "example5/Texture_VS.glsl";
	fs::path fragmentPath = shaderDir / "example5/Texture_FS.glsl";
	Shader shaderProgram(vertexPath, fragmentPath);
	Shader shader2(shaderDir / "example8/Texture_VS.glsl", shaderDir / "example8/Texture_FS.glsl");

	//Texture generation
	//------------------------------------------------------------------------------------------------
	unsigned int texture[2];
	glGenTextures(2, texture);

	textureGenNLoad(texture[0], "/container.jpg", GL_RGB);
	textureGenNLoad(texture[1], "/awesomeface.png", GL_RGBA);

	shaderProgram.use();
	shaderProgram.setInt("texture1", 0);
	shaderProgram.setInt("texture2", 1);

	shader2.use();
	shader2.setInt("texture1", 0);
	shader2.setInt("texture2", 1);


	//Vertex Data, Buffers and attribute linking
	//-------------------------------------------------------------------------------------------------
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f, 
		 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 0.0f,	0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};


	//Generate a vertex buffer object and vertex array object
	unsigned int VBO[2], VAO[2], EBO[2];
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);
	glGenBuffers(2, EBO);
	
	//Bind the vertex arrray object
	glBindVertexArray(VAO[0]);

	//Bind the buffer object 
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//Since glVertexAttribPointer bounds the VBO to VAO we can unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
	
	//Bind the vertex arrray object
	glBindVertexArray(VAO[1]);

	//Bind the buffer object 
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	  
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
	glEnableVertexAttribArray(2);

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

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.5f,-0.5f,0.0f));
		transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f,0.0f,1.0f));

		shaderProgram.use();
		shaderProgram.setMat4("transform", transform);

		glBindVertexArray(VAO[0]);
		/* glDrawArrays(GL_TRIANGLES, 0, 3); */
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		
		
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(-0.5f,0.5f, 0.0f));
		trans = glm::scale(trans, glm::vec3(-abs(sin((float)glfwGetTime())*0.5),-abs(sin((float)glfwGetTime())*0.5),1.0f) - glm::vec3(0.05f,0.05f,0.0f));
		shaderProgram.setMat4("transform", trans);		
		glBindVertexArray(VAO[1]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
        // Swap front and back buffers and poll events
		// ---------------------------------------------
        glfwSwapBuffers(window);
		glfwPollEvents();
    }

    // Clean up and exit
	// -----------------------------------------------------------------------------------
	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
	glDeleteBuffers(2, EBO);
	shaderProgram.deleteProgram();
    glfwTerminate();

    return 0;
}
