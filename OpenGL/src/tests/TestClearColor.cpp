#include "TestClearColor.h"
#include "GL/glew.h"
#include "Renderer.h"
#include "imgui/imgui.h"

namespace test
{
	TestClearColor::TestClearColor()
		: ClearColor{ 0.0f, 0.0f, 1.0f, 1.0f }
	{
	}

	TestClearColor::~TestClearColor()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	}

	void TestClearColor::OnRender(const Renderer& renderer)
	{
		Test::OnRender(renderer);
		GLCall(glClearColor(ClearColor[0], ClearColor[1], ClearColor[2], ClearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestClearColor::OnImGUIRender()
	{
		Test::OnImGUIRender();
		ImGui::ColorEdit4("ClearColor", ClearColor);
	}
}