#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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
	void setMatrix(const std::string& variable, glm::mat4 value)const;
	void setVec(const std::string& variable, glm::vec3 value)const;
};
#endif