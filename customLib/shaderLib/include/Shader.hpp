#ifndef SHADER_H
#define SHADER_H


#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <filesystem>
#include <glm/glm.hpp>

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
	void setFloat(const std::string& name, float value) const;
	void setInt(const std::string& name, int value) const;
	void setVec2(const std::string &name, const glm::vec2 &value) const;
	void setVec2(const std::string &name, float x, float y) const;
	void setMat4(const std::string &name, const glm::mat4 &mat) const;
	void setMat3(const std::string &name, const glm::mat3 &mat) const;
	void setMat2(const std::string &name, const glm::mat2 &mat) const;
	void setVec4(const std::string &name, float x, float y, float z, float w) const;
	void setVec4(const std::string &name, const glm::vec4 &value) const;
	void setVec3(const std::string &name, float x, float y, float z) const;
	void setVec3(const std::string &name, const glm::vec3 &value) const;

};


#endif
