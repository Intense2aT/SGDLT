//test

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
	base.UseBaseShadersTexmap();
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

	// SHOULDNT BE USING A CIRCLE FOR A TEXTURED OBJECT
	// SEE ON PRAGUE ULDINE TESTOBJEKT, mitte lihtsalt ring
	float radius = 100.0f;
	standardObject circleObject(-640.0f, 360.0f, &mootor ,true);
	circleObject.MakeSquare(radius, radius);
	circleObject.addTexture("src/textures/heartPixel1.png", 1, 1, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	float position[2] = { -540, 260 };
	tilemap map(100, 50, 50, position);
	map.addTexture("src/textures/texmap1.png", 2, 2, 4);
	//map.addTexture("src/textures/simpleCandle1.jpg", 1, 1, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//glDisable(GL_CULL_FACE);

	//standardObject squareObject(0.0f, 0.0f, true);
	//squareObject.MakeSquare(200.0f, 200.0f);
	//squareObject.addTexture("src/textures/test.jpg");

	//TMouse::SetMouseStatus(mootor.window, "hidden");
	
	//Creating delta time
	const double deltaTimeConstant = 1.0 / 120.0 - 0.00001f;
	double deltaTimeValue = glfwGetTime();
	//

	/* fps measurment variables for testing
	int ticks = 50000;
	double magic = 0;
	int x = 0;
	*/
	while (!glfwWindowShouldClose(mootor.window))
	{
		//std::cout << TMouse::GetMousePos(mootor.window).xPos << " " << TMouse::GetMousePos(mootor.window).yPos << std::endl;
		//magic += mootor.printFps(); redo later

		mootor.UpdateViewMat(base);

		//input
		//looks ever so slightly better than before
		//could make it with callback functions later
		if (TBoard::isKeyPressed(mootor.window, GLFW_KEY_LEFT))
		{
			mootor.SetGlobalPosition(mootor.GetGlobalPosition()[0] + 5, mootor.GetGlobalPosition()[1]);
		}
		if (TBoard::isKeyPressed(mootor.window, GLFW_KEY_RIGHT))
		{
			mootor.SetGlobalPosition(mootor.GetGlobalPosition()[0] - 5, mootor.GetGlobalPosition()[1]);
		}
		if (TBoard::isKeyPressed(mootor.window, GLFW_KEY_UP))
		{
			mootor.SetGlobalPosition(mootor.GetGlobalPosition()[0], mootor.GetGlobalPosition()[1] - 5);
		}
		if (TBoard::isKeyPressed(mootor.window, GLFW_KEY_DOWN))
		{
			mootor.SetGlobalPosition(mootor.GetGlobalPosition()[0], mootor.GetGlobalPosition()[1] + 5);
		}
		std::cout << mootor.GetGlobalPosition()[0] << " " << mootor.GetGlobalPosition()[1] << "\n";
		//

		/* Render here */
		glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//SetDrawingColor(color1, &base);

		map.Draw(base);
		//system("pause");
		circleObject.Draw(base);
		//SetDrawingColor(color2);
		//squareObject.Draw();

		/* Swap front and back buffers */
		glfwSwapInterval(0); //kuradima vsync
		glfwSwapBuffers(mootor.window);

		/* Poll for and process events */
		glfwPollEvents();

		bool printed = false;
		//deltaTimeConstant - 0.00001f to get it over the set fps by a slim margin (looks prettier, likely dumb waste of resources and should be precomputed)
		//unnecessary edit> now precomputed, likely still inefficient and bad
		/*
		while (mootor.getTime() - deltaTimeValue < deltaTimeConstant)
		{
			if (!printed)
			{
				std::cout << "frame done, on break til next" << "\n";
				printed = true;
			}
		}
		*/

		deltaTimeValue = mootor.getTime();
		/*
		if (x >= ticks)
		{
			break;
		}
		x++;
		*/
	}

	//std::cout << "\n" << "average fps was: " << magic / ticks << "\n";
	//system("pause");

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