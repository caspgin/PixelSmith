#ifndef SHADER_H
#define SHADER_H


#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <filesystem>

namespace fs = std::filesystem;
class Shader{
	unsigned int _id; // program ID
	void readFiles(fs::path &vertexPath, fs::path &fragmentPath, std::string& vertexCode, std::string& fragmentCode);
	void buildNCompileShader(const char * vShaderSource, const char * fShaderSource);
public:
	//constructor reads the vertex and fragment shader files and builds the shader
	Shader(fs::path vertexPath, fs::path fragmentPath);
	//use/activate the shader
	void use();
	void deleteProgram();
};


#endif
