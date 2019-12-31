#pragma once

#include "Test.h"

namespace test
{
	class TestClearColor : public Test
	{
	public:
		TestClearColor();
		~TestClearColor();

		void OnRender() override;
		void OnImGUIRender() override;

	private:
		float ClearColor[4];
	};
}