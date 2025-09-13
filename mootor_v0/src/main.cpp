#include <glew.h>
#include <glfw3.h>

#include "initit.h"

#include <iostream>
#include <string>

#include "standardObject.h"
#include "generatePrimitives.h"
#include "shaderLoader.h"

int width, height;
int colorUniform;

void SetDrawingColor(float* color);

int main()
{
	mootor mootor;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mootor.MakeWindow(800, 600, "Window Title");

	glfwSetFramebufferSizeCallback(mootor.window, [](GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height);
	std::cout << " user resized window" << std::endl;  });

	shaderManager base;
	base.UseBaseShaders();
	//base.LoadShader("C:/dev_kaust/mootor_v0/mootor_v0/src/shaders/testShaderFrag.shader", 'F');
	//base.CreateProgram();
	//base.UseProgram();

	int colorUniform = glGetUniformLocation(base.program, "colors\0");
	float color1[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	float color2[4] = { 1.0f, 0.0f, 0.0f, 1.0f };

	standardObject circleObject(0.0f, 0.0f);
	circleObject.MakeCircle(0.5f);

	standardObject squareObject(0.0f, -0.5f);
	squareObject.MakeSquare(0.5f, 1.0f);

	while (!glfwWindowShouldClose(mootor.window))
	{
		/* Render here */
		glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		SetDrawingColor(color1);
		circleObject.Draw();
		SetDrawingColor(color2);
		squareObject.Draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(mootor.window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	base.Destroy();
	mootor.Destroy();
	return 0;
}

void SetDrawingColor(float *color)
{
	glUniform4f(colorUniform, color[0], color[1], color[2], color[3]);
}