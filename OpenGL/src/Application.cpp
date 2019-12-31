#include "GLFW/glfw3.h"

#include <iostream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"

#include "Shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/examples/imgui_impl_opengl3.h"
#include "imgui/examples/imgui_impl_glfw.h"

#include "tests/TestClearColor.h"

int main()
{
	//Init the Window api, create windows + create context
	if (!glfwInit())
	{
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	const float WindowWidth = 640.0f;
	const float WindowHeight = 480.0f;
	GLFWwindow* window = glfwCreateWindow((int) WindowWidth, (int) WindowHeight, "Hello World", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	//END

	Renderer renderer;
	renderer.Initialize();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();
	 
	{
		//Initialize the vertex buffer
		float positions[16] =
		{
			-WindowWidth*0.25f, -WindowHeight*0.25f, 0.0f, 0.0f,
			WindowWidth*0.25f, -WindowHeight*0.25f, 1.0f, 0.0f,
			WindowWidth*0.25f, WindowHeight*0.25f, 1.0f, 1.0f,
			-WindowWidth*0.25f, WindowHeight*0.25f, 0.0f, 1.0f
		};

		unsigned int indices[6] =
		{
			0,1,2,
			2,3,0
		};

		VertexBuffer vertexBuffer(positions, sizeof(positions));
		VertexBufferLayout vertexLayout;
		vertexLayout.PushFloat(2);
		vertexLayout.PushFloat(2); 
		VertexArray vertexArray;
		vertexArray.AddBuffer(vertexBuffer, vertexLayout);

		IndexBuffer indexBuffer(indices, std::size(indices));

		Shader shader("res/shaders/Basic.shader");
		shader.SetUniform4f("u_Color", 0.0f, 0.0f, 1.0f, 1.0f);

		glm::mat4 proj = glm::ortho(0.0f, WindowWidth, 0.0f, WindowHeight);
		glm::mat4 view = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0, 0, 0));

		Texture tex("res/textures/cherno_logo.png");
		tex.Bind();
		shader.SetUniform1i("u_Texture", tex.GetBindedSlot());

		//Unbind everything
		vertexArray.Unbind();
		indexBuffer.Unbind();
		shader.Unbind();

		glm::vec3 translation = glm::vec3(0, 0, 0);

		test::TestMenu testMenu;
		testMenu.RegisterTest<test::TestClearColor>("Clear Color");

		//Application Loop
		while (!glfwWindowShouldClose(window))
		{
			renderer.Clear();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			
			/*ImGui::SliderFloat3("Model matrix", &translation.x, 0.0f, WindowWidth);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			glm::mat4 model = glm::translate(glm::identity<glm::mat4>(), translation);
			glm::mat4 mvp = proj * view * model;

			shader.Bind();
			shader.SetUniformMat4f("u_MVP", mvp);*/

			testMenu.OnUpdate(0.0f);
			testMenu.OnRender();
			
			renderer.Draw(vertexArray, indexBuffer, shader);

			testMenu.OnImGUIRender();
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);

			//Process events
			glfwPollEvents();
		}
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}
