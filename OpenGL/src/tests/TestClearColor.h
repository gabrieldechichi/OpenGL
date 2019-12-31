#pragma once

#include "Test.h"

namespace test
{
	class TestClearColor : public Test
	{
	public:
		TestClearColor();
		~TestClearColor();

		void OnRender(const Renderer& renderer) override;
		void OnImGUIRender() override;

	private:
		float ClearColor[4];
	};
}