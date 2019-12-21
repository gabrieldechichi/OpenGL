#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct ShaderProgramSource
{
	const std::string VertexSource;
	const std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath)
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

static unsigned int CompileShader(unsigned int type, const std::string& source)
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

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
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

int main()
{
	//Init the Window api, create windows + create context
	if (!glfwInit())
	{
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	//END

	// Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error initializing GLEW" << std::endl;
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	//Initialize the vertex buffer
	float positions[6] =
	{
		-0.5f, -0.5f,
		0.0f, 0.5f,
		0.5f, -0.5f
	};

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	//Defining position data layout
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);//(index, count, type, normalized?, size in bytes of the vertex, index of the type inside the vertex); 
	//END defining position data layout

	// Setup shader
	ShaderProgramSource shaderSrc = ParseShader("res/shaders/Basic.shader");
	unsigned int shader = CreateShader(shaderSrc.VertexSource, shaderSrc.FragmentSource);
	glUseProgram(shader);

	//END

	//Application Loop
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		//Rendering
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//END Rendering

		glfwSwapBuffers(window);

		//Process events
		glfwPollEvents();
	}

	glDeleteProgram(shader);

	glfwTerminate();
}
