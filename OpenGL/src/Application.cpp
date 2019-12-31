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
	GLFWwindow* window = glfwCreateWindow(WindowWidth, WindowHeight, "Hello World", nullptr, nullptr);
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
	 
	{
		//Initialize the vertex buffer
		float positions[16] =
		{
			WindowWidth*0.25f, WindowHeight*0.25f, 0.0f, 0.0f,
			WindowWidth*0.75f, WindowHeight*0.25f, 1.0f, 0.0f,
			WindowWidth*0.75f, WindowHeight*0.75f, 1.0f, 1.0f,
			WindowWidth*0.25f, WindowHeight*0.75f, 0.0f, 1.0f
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
		glm::mat4 view = glm::translate(glm::identity<glm::mat4>(), glm::vec3(-100, 0, 0));
		glm::mat4 model = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0, 100, 0));

		glm::mat4 mvp = proj * view * model;

		shader.SetUniformMat4f("u_MVP", mvp);

		Texture tex("res/textures/cherno_logo.png");
		tex.Bind();
		shader.SetUniform1i("u_Texture", tex.GetBindedSlot());

		//Unbind everything
		vertexArray.Unbind();
		indexBuffer.Unbind();
		shader.Unbind();

		//Application Loop
		while (!glfwWindowShouldClose(window))
		{
			renderer.Clear();
			renderer.Draw(vertexArray, indexBuffer, shader);

			glfwSwapBuffers(window);

			//Process events
			glfwPollEvents();
		}
	}

	glfwTerminate();
}
