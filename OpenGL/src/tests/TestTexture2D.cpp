#include "TestTexture2D.h"

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"

#include "Shader.h"

#include "imgui/imgui.h"
#include "imgui/examples/imgui_impl_opengl3.h"
#include "imgui/examples/imgui_impl_glfw.h"

namespace test
{
	TestTexture2D::TestTexture2D()
	{
		//Initialize the vertex buffer
		float positions[16] =
		{
			-100.0f * 0.25f, -150.0f * 0.25f, 0.0f, 0.0f,
			100.0f*0.25f, -150.0f * 0.25f, 1.0f, 0.0f,
			100.0f*0.25f, 150.0f*0.25f, 1.0f, 1.0f,
			-100.0f * 0.25f, 150.0f*0.25f, 0.0f, 1.0f
		};

		unsigned int indices[6] =
		{
			0,1,2,
			2,3,0
		};

		VertexBuff = std::make_unique<VertexBuffer>(positions, sizeof(positions));
		
		VertexLayout = std::make_unique<VertexBufferLayout>();
		VertexLayout->PushFloat(2);
		VertexLayout->PushFloat(2);

		VertexArr = std::make_unique<VertexArray>();
		VertexArr->AddBuffer(*VertexBuff, *VertexLayout);

		IndexBuff = std::make_unique<IndexBuffer>(indices, std::size(indices));

		ShaderProgram = std::make_unique<Shader>("res/shaders/Basic.shader");

		ProjectionMatrix = glm::ortho(0.0f, 100.0f, 0.0f, 150.0f);
		ViewMatrix = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0, 0, 0));

		Tex = std::make_unique<Texture>("res/textures/cherno_logo.png");
		Tex->Bind();
		ShaderProgram->SetUniform1i("u_Texture", Tex->GetBindedSlot());

		Unbind();
		
		Position = glm::vec3(0, 0, 0);
	}

	void TestTexture2D::OnRender(const Renderer& renderer)
	{
		Bind();

		glm::mat4 model = glm::translate(glm::identity<glm::mat4>(), Position);
		glm::mat4 mvp = ProjectionMatrix * ViewMatrix * model;

		ShaderProgram->SetUniformMat4f("u_MVP", mvp);

		renderer.Draw(*VertexArr, *IndexBuff, *ShaderProgram);
	}

	void TestTexture2D::OnImGUIRender()
	{
		ImGui::SliderFloat3("Texture Position", &Position.x, -600.0f, 600.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

	void TestTexture2D::Bind() const
	{
		VertexArr->Bind();
		IndexBuff->Bind();
		ShaderProgram->Bind();
	}

	void TestTexture2D::Unbind() const
	{
		VertexArr->Unbind();
		IndexBuff->Unbind();
		ShaderProgram->Unbind();
	}
}
