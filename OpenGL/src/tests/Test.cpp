#include "Test.h"

#include "imgui/imgui.h"

namespace test
{
	void TestMenu::OnUpdate(float deltaTime)
	{
		if (CurrentTest)
		{
			CurrentTest->OnUpdate(deltaTime);
		}
	}

	void TestMenu::OnRender(const Renderer& renderer)
	{
		if (CurrentTest)
		{
			CurrentTest->OnRender(renderer);
		}
	}

	void TestMenu::OnImGUIRender()
	{
		if (!CurrentTest)
		{
			for (auto test : AllTests)
			{
				if (ImGui::Button(test.first.c_str()))
				{
					CurrentTest = test.second();
				}
			}
		}
		else
		{
			if (ImGui::Button("<-"))
			{
				CurrentTest.reset();
			}
			else
			{
				CurrentTest->OnImGUIRender();
			}
		}
	}
}
