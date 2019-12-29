#include "Renderer.h"
#include "GL/glew.h"
#include <iostream>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

bool Renderer::Initialize()
{
	//TODO: Guard against multiple initializations
	// Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error initializing GLEW" << std::endl;
		return false;
	}
	std::cout << glGetString(GL_VERSION) << std::endl;
	return true;
}

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const
{
	vertexArray.Bind();
	indexBuffer.Bind();
	shader.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr));

	vertexArray.Unbind();
	indexBuffer.Unbind();
	shader.Unbind();
}

void Renderer::GLClearError()
{
	while (glGetError() != GL_NO_ERROR) {};
}

void Renderer::GLAssertError(const char* funcName, const char* fileName, unsigned int lineNum)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL error]: " << std::hex << error << ", " << funcName << ", " << fileName << ":" << lineNum << std::endl;
		ASSERT(error == GL_NO_ERROR);
	}
}