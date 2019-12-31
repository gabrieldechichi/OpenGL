#pragma once

#include <string>
#include "glm/glm.hpp"

struct ShaderProgramSource
{
	const std::string VertexSource;
	const std::string FragmentSource;
};

class Shader
{
private:
	unsigned int RendererId;

public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform1i(const std::string& name, int v0);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);


private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	int GetUniformLocation(const std::string& name);
};