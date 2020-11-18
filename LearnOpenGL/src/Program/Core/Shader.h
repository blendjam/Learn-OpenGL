#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h> 
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
class Shader
{
private:
	unsigned int compileShader(const unsigned int& type, const std::string& source);
public:
	unsigned int m_ID;
	Shader(const std::string& vertexName, const std::string& fragmentName);
	void use();
	void setBool(const std::string& variable, bool value) const;
	void setInt(const std::string& variable, int value) const;
	void setFloat(const std::string& variable, float value) const;
};
#endif