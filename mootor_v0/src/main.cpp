#include <glew.h>
#include <glfw3.h>
#include "stb_image/stb_image.h"

#include "initit.h"

#include <iostream>
#include <string>

#include "standardObject.h"
#include "generatePrimitives.h"
#include "shaderLoader.h"

int width = 800, height = 600;
int colorUniform;

void SetDrawingColor(float* color);
//cant be bothered to texture right now so will do conversion from pixel to opengl cordinates
//type is 'H' for height conversion and 'W' for width conversion
float pixelToGLCords(int position, char type); 

int main()
{
	mootor mootor;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mootor.MakeWindow(width, height, "Window Title");

	glfwSetFramebufferSizeCallback(mootor.window, [](GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height);
	std::cout << " user resized window" << std::endl;  });

	shaderManager base;
	base.UseBaseShadersTextured();
	//base.UseBaseShaders();
	//base.LoadShader("C:/dev_kaust/mootor_v0/mootor_v0/src/shaders/testShaderFrag.shader", 'F');
	//base.CreateProgram();
	//base.UseProgram();

	int colorUniform = glGetUniformLocation(base.program, "colors\0");
	float color1[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	float color2[4] = { 1.0f, 0.0f, 0.0f, 1.0f };

	
	int projectionMatLoc = glGetUniformLocation(base.program, "projectionMat");
	//Remember this is column first matrix
	float value[] = {0.75f, 0.0f, 0.0f, 0.0f,
					 0.0f, 1.0f, 0.0f, 0.0f,
					 0.0f, 0.0f, 1.0f, 0.0f,
					 0.0f, 0.0f, 0.0f, 1.0f };
	
	glUniformMatrix4fv(projectionMatLoc, 1, GL_FALSE, value);

	standardObject circleObject(pixelToGLCords(400, 'W'), pixelToGLCords(300, 'H'), true);
	circleObject.MakeCircle(0.5f);
	circleObject.addTexture("src/textures/test.jpg");

	standardObject squareObject(0.0f, 0.0f, true);
	squareObject.MakeSquare(1.0f, 1.0f);
	squareObject.addTexture("src/textures/test.jpg");

	while (!glfwWindowShouldClose(mootor.window))
	{
		/* Render here */
		glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//SetDrawingColor(color1);
		circleObject.Draw();
		//SetDrawingColor(color2);
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

float pixelToGLCords(int position, char type)
{
	if (type == 'H')
	{
		return position / ((float)height / 2.0f) - 1.0f;
	}
	else if (type == 'W')
	{
		return position / ((float)width / 2.0f) - 1.0f;
	}
}