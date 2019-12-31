#include "Shader.h"

#include "Renderer.h"
#include "GL/glew.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


Shader::Shader(const std::string& filepath)
{
	ShaderProgramSource shaderSrc = ParseShader(filepath);
	RendererId = CreateShader(shaderSrc.VertexSource, shaderSrc.FragmentSource);
	Bind();
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(RendererId));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(RendererId));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0,v1,v2,v3));
}

void Shader::SetUniform1i(const std::string& name, int v0)
{
	GLCall(glUniform1i(GetUniformLocation(name), v0));
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	enum class ShaderType
	{
		NONE = -1, Vertex, Fragment
	};

	std::ifstream stream(filepath);
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (std::getline(stream, line))
	{
		if (line.find("vertex") != std::string::npos)
		{
			type = ShaderType::Vertex;
		}
		else if (line.find("fragment") != std::string::npos)
		{
			type = ShaderType::Fragment;
		}
		else //copy the line
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[(int)ShaderType::Vertex].str(), ss[(int)ShaderType::Fragment].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result = GL_FALSE;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout
			<< "Failed to compile shader"
			<< (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
			<< std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	if (!vs || !fs)
	{
		return 0;
	}

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

int Shader::GetUniformLocation(const std::string& name)
{
	GLCall(int location = glGetUniformLocation(RendererId, name.c_str()));
	if (location == -1)
	{
		std::cout << "Warning: uniform '" << name << "' does not exit!" << std::endl;
	}
	return location;
}
