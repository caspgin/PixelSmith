#include <Shader.hpp>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <ostream>


void Shader::readFiles(fs::path &vertexPath, fs::path &fragmentPath,std::string& vertexCode, std::string& fragmentCode){
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	try{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream, fShaderStream;
		
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();
		
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		

	}catch(std::ifstream::failure e){
		
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n" << e.what() << std::endl;
	}

}

void checkCompileNLinkerErrors(unsigned int &shader, std::string type){
	
	int success;
	const int INFO_LOG_SIZE = 512;
	char infoLog[INFO_LOG_SIZE];

	if(type != "PROGRAM"){
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if(!success){
			glGetShaderInfoLog(shader, INFO_LOG_SIZE, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
		}
	}else{

		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if(!success){
			glGetProgramInfoLog(shader, INFO_LOG_SIZE, NULL, infoLog);
			std::cout << "ERROR::SHADER_LINK_ERROR of type: " << type << "\n" << infoLog << std::endl;
		}
	}
}

void Shader::buildNCompileShader(const char * vShaderSource, const char * fShaderSource){
	
	//Vertex Shader Building and compilation
	//--------------------------------------------------------------

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderSource, NULL);
	glCompileShader(vertexShader);
	checkCompileNLinkerErrors(vertexShader, "VERTEX");
	
	//Fragment Shader Building and Compilation
	//-------------------------------------------------------------------
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fShaderSource, NULL);
	glCompileShader(fragmentShader);
	checkCompileNLinkerErrors(fragmentShader, "FRAGMENT");

	//Shader Program
	//------------------------------------------------------------------
	this->_id = glCreateProgram();
	glAttachShader(this->_id, vertexShader);
	glAttachShader(this->_id, fragmentShader);
	glLinkProgram(this->_id);
	checkCompileNLinkerErrors(this->_id, "PROGRAM");
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

Shader::Shader(fs::path vertexPath, fs::path fragmentPath){
	
	std::string vertexCode;
	std::string fragmentCode;
	
	/* auto start = std::chrono::high_resolution_clock::now(); */
	//-------------------------------------------------------------------------
	readFiles(vertexPath, fragmentPath, vertexCode, fragmentCode);

	/* auto end = std::chrono::high_resolution_clock::now(); */
	/* std::chrono::duration<double> duration = end - start; */
	/* std::cout << "Time taken to read files together: " << duration.count() << std::endl; */

	const char * vShaderCode = vertexCode.c_str();
	const char * fShaderCode = fragmentCode.c_str();
	
	buildNCompileShader(vShaderCode, fShaderCode);
	
}

void Shader::use(){
	glUseProgram(this->_id);
}

void Shader::deleteProgram(){
	glDeleteProgram(this->_id);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(this->_id, name.c_str()), value);
}

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(this->_id, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{ 
	glUniform2fv(glGetUniformLocation(this->_id, name.c_str()), 1, &value[0]); 
}
void Shader::setVec2(const std::string &name, float x, float y) const
{  
	glUniform2f(glGetUniformLocation(this->_id, name.c_str()), x, y); 
}
// ------------------------------------------------------------------------
void Shader::setVec3(const std::string &name, const glm::vec3 &value) const 
{  
	glUniform3fv(glGetUniformLocation(this->_id, name.c_str()), 1, &value[0]); 
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const
{  
	glUniform3f(glGetUniformLocation(this->_id, name.c_str()), x, y, z); 
}
// --Shader::----------------------------------------------------------------------
void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{ 
	glUniform4fv(glGetUniformLocation(this->_id,name.c_str()), 1, &value[0]); 
}
void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const
{ 
	glUniform4f(glGetUniformLocation(this->_id, name.c_str()), x, y, z, w); 
}
// --Shader::----------------------------------------------------------------------
void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(this->_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// --Shader::----------------------------------------------------------------------
void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(this->_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// --Shader::----------------------------------------------------------------------
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(this->_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
