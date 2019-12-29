#pragma once

class VertexArray;
class IndexBuffer;
class Shader;

#define ASSERT(x) if (!(x)) { __debugbreak(); }
#define GLCall(f) \
	Renderer::GLClearError();\
	f;\
	Renderer::GLAssertError(#f, __FILE__, __LINE__)

class Renderer
{
public:
	bool Initialize();
	void Clear() const;
	void Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const;

	static void GLClearError();
	static void GLAssertError(const char* funcName, const char* fileName, unsigned int lineNum);
};