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
	ID = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, ss[0].str());
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, ss[1].str());

	glAttachShader(ID, vs);
	glAttachShader(ID, fs);
	glLinkProgram(ID);
	int success;
	char infoLog[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
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
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
			infoLog << std::endl;
	};
	//------------------------------
	return shaderID;
}

void Shader::use()
{
	glUseProgram(ID);
}
