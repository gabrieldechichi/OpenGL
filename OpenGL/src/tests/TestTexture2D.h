#pragma once

#include "Test.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class VertexBuffer;
class VertexArray;
class VertexBufferLayout;
class IndexBuffer;
class Shader;
class Texture;

namespace test
{
	class TestTexture2D : public Test
	{
	private:
		std::unique_ptr<VertexBuffer> VertexBuff;
		std::unique_ptr<VertexBufferLayout> VertexLayout;
		std::unique_ptr<VertexArray> VertexArr;
		std::unique_ptr<IndexBuffer> IndexBuff;
		std::unique_ptr<Shader> ShaderProgram;
		std::unique_ptr<Texture> Tex;

		glm::vec3 Position;
		glm::mat4 ProjectionMatrix;
		glm::mat4 ViewMatrix;

	public:
		TestTexture2D();

		void OnRender(const Renderer& renderer) override;
		void OnImGUIRender() override;

	private:
		void Bind() const;
		void Unbind() const;
	};
}