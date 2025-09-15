#include <glew.h>
#include <fstream>
#include <iostream>
#include <string>
#include "shaderLoader.h"

//Type is 'V' for vertex and 'F' for frgament
void shaderManager::LoadShader(const char* location, const char& type)
{
	std::string Shader;
	std::string lineStore;
	std::ifstream ShaderFile(location);

	while (std::getline(ShaderFile, lineStore)) {
		Shader = Shader + lineStore + '\n'; // we need newline char because apparently otherwise it wont compile
		//std::cout << lineStore << std::endl;
	}

	const char* shader = Shader.c_str();
	//std::cout << Shader << std::endl;

	if (type == 'V')
	{
		glShaderSource(vs, 1, &shader, NULL);
		glCompileShader(vs);
	}
	else if (type == 'F')
	{
		glShaderSource(fs, 1, &shader, NULL);
		glCompileShader(fs);
	}
}

void shaderManager::CreateProgram()
{
	int success;
	char infoLog[512];

	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}

//lets load the most
shaderManager::shaderManager()
{
	vs = glCreateShader(GL_VERTEX_SHADER);
	fs = glCreateShader(GL_FRAGMENT_SHADER);
}

shaderManager::~shaderManager()
{
	glDeleteShader(vs);
	glDeleteShader(fs);
	glDeleteProgram(program);
}

void shaderManager::UseBaseShaders()
{
	LoadShader("src/shaders/vertexShader1.shader", 'V');
	LoadShader("src/shaders/fragmentShader1.shader", 'F');
	CreateProgram();
	UseProgram();
}

void shaderManager::UseProgram() const
{
	glUseProgram(program);
}

void shaderManager::Destroy()
{
	this->~shaderManager();
}