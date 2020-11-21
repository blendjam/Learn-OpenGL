#include "Shader.h"

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	std::ifstream vsStream(vertexShaderPath);
	std::ifstream fsStream(fragmentShaderPath);
	std::string line;
	std::stringstream ss[2];
	while (getline(vsStream, line))
	{
		ss[0] << line << "\n";
	}
	while (getline(fsStream, line))
	{
		ss[1] << line << "\n";
	}
	m_ID = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, ss[0].str());
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, ss[1].str());

	glAttachShader(m_ID, vs);
	glAttachShader(m_ID, fs);
	glLinkProgram(m_ID);
	int success;
	char infoLog[512];
	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" <<
			infoLog << std::endl;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);
}
unsigned int Shader::compileShader(const unsigned int& type, const std::string& source)
{
	unsigned int shaderID = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shaderID, 1, &src, NULL);
	glCompileShader(shaderID);
	//-------------Error Handling for shader code--------------
	int success;
	char infoLog[512];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << type << "COMPILATION_FAILED\n" <<
			infoLog << std::endl;
	};
	//------------------------------
	return shaderID;
}

void Shader::use()
{
	glUseProgram(m_ID);
}

void Shader::setBool(const std::string& variable, bool value) const
{
	glUniform1i(glGetUniformLocation(m_ID, variable.c_str()), (int)value);
}

void Shader::setInt(const std::string& variable, int value) const
{
	glUniform1i(glGetUniformLocation(m_ID, variable.c_str()), value);
}

void Shader::setFloat(const std::string& variable, float value) const
{
	glUniform1f(glGetUniformLocation(m_ID, variable.c_str()), value);
}
void Shader::setMatrix(const std::string& variable, glm::mat4 value)const
{
	glUniformMatrix4fv(glGetUniformLocation(m_ID, variable.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::setVec(const std::string& variable, glm::vec3 value)const
{
	glUniform3fv(glGetUniformLocation(m_ID, variable.c_str()), 1, &value[0]);
}


