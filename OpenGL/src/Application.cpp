#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

int main()
{
	//Init the Window api, create windows + create context
	if (!glfwInit())
	{
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	//END

	// Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error initializing GLEW" << std::endl;
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	//Initialize the vertex buffer
	float positions[6] =
	{
		-0.5f, -0.5f,
		0.0f, 0.5f,
		0.5f, -0.5f
	};

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	//Defining position data layout
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);//(index, count, type, normalized?, size in bytes of the vertex, index of the type inside the vertex); 
	//END definint position data layout
	//END

	//Application Loop
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		//Rendering
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//END Rendering

		glfwSwapBuffers(window);

		//Process events
		glfwPollEvents();
	}

	glfwTerminate();
}
