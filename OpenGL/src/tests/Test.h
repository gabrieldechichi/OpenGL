#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>

class Renderer;

namespace test
{
	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender(const Renderer& renderer) {}
		virtual void OnImGUIRender() {}
	};

	class TestMenu : public Test
	{
	public:
		void OnUpdate(float deltaTime) override;
		void OnRender(const Renderer& renderer) override;
		void OnImGUIRender() override;

	private:
		std::map<std::string, std::function<std::shared_ptr<Test>()>> AllTests;
		std::shared_ptr<Test> CurrentTest;

	public:
		template<typename T>
		void RegisterTest(const std::string& testName)
		{
			AllTests.emplace(testName, []	() { return std::make_shared<T>(); });
		}
	};
}