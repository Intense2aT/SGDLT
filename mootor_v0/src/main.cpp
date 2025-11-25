#include <glew.h>
#include <glfw3.h>
#include "stb_image/stb_image.h"

#include "initit.h"
#include "input.h"

#include <iostream>
#include <string>
#include <chrono>

#include "standardObject.h"
#include "generatePrimitives.h"
#include "shaderLoader.h"

//what were you thinking using this???
//#include <Windows.h> 

static int width = 1280, height = 720;
int colorUniform;

void SetDrawingColor(float* color, shaderManager* base);

void updateMatrixOnResize(int matrixLocation, int width, int height, float *projMat)
{
	projMat[0] = 2.0f / ((float)width - 0.0f);
	projMat[5] = 2.0f / ((float)height - 0.0f);
	projMat[10] = 2.0f / (0.0f - 100.0f);
	projMat[15] = 1.0f;

	for (int i = 0; i < 16; i++)
	{
		std::cout << *(projMat + i) << " ";
		if (i % 4 == 3)
		{
			std::cout << std::endl;
		}
	}
	
	glUniformMatrix4fv(matrixLocation, 1, GL_TRUE, projMat);
}

int main()
{
	mootor mootor;
	
	mootor.MakeWindow(width, height, "Window Title");
	mootor.SetWindowResizable(false);

	shaderManager base;
	base.UseBaseShadersTextured();
	//base.UseBaseShaders();
	//base.LoadShader("C:/dev_kaust/mootor_v0/mootor_v0/src/shaders/testShaderFrag.shader", 'F');
	//base.CreateProgram();
	//base.UseProgram();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	 
	float color1[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	float color2[4] = { 1.0f, 0.0f, 0.0f, 1.0f };

	static int projectionMatLoc = glGetUniformLocation(base.program, "projectionMat");

	glUniformMatrix4fv(projectionMatLoc, 1, GL_TRUE, mootor.projMat);
	updateMatrixOnResize(projectionMatLoc, width, height, mootor.projMat);

	//FIX LATER (move to mootor class)
	//glfwSetFramebufferSizeCallback(mootor.window, [](GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height);
	//std::cout << "window resized " << width << height << std::endl; updateMatrixOnResize(projectionMatLoc, width, height, mootor.projMat);});

	float radius = 48.0f;
	standardObject circleObject((float)(-width/2+radius), (float)(-height/2+radius), true);
	circleObject.MakeCircle(radius);
	circleObject.addTexture("src/textures/heartPixel1.png");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	

	//standardObject squareObject(0.0f, 0.0f, true);
	//squareObject.MakeSquare(200.0f, 200.0f);
	//squareObject.addTexture("src/textures/test.jpg");

	//TMouse::SetMouseStatus(mootor.window, "hidden");
	
	//Creating delta time
	const double deltaTimeConstant = 1.0 / 60.0;
	double deltaTimeValue = glfwGetTime();
	//

	while (!glfwWindowShouldClose(mootor.window))
	{
		//std::cout << TMouse::GetMousePos(mootor.window).xPos << " " << TMouse::GetMousePos(mootor.window).yPos << std::endl;
		mootor.printFpsSmoothed();

		/* Render here */
		glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//SetDrawingColor(color1, &base);
		circleObject.Draw();
		//SetDrawingColor(color2);
		//squareObject.Draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(mootor.window);

		/* Poll for and process events */
		glfwPollEvents();

		bool printed = false;
		while (mootor.getTime() - deltaTimeValue < deltaTimeConstant)
		{
			if (!printed)
			{
				std::cout << "frame done, on break til next" << "\n";
				printed = true;
			}
		}

		deltaTimeValue = mootor.getTime();
	}

	base.Destroy();
	mootor.Destroy();
	return 0;
}

void SetDrawingColor(float *color, shaderManager* base)
{
	int colorUniform = glGetUniformLocation(base->program, "colors");
	if (colorUniform == -1) {
		std::cout << "ERROR: Uniform 'colors' not found!" << std::endl;
	}
	glUniform4f(colorUniform, color[0], color[1], color[2], color[3]);
}