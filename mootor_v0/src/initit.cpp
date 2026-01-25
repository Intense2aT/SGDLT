#include <glew.h>
#include <glfw3.h>

#include "initit.h"
#include "input.h"
#include <iostream>
#include <chrono>

mootor::mootor()
{
	if (!glfwInit())
	{
		std::cout << "were cooked" << std::endl;
	}

	//setting up hints here (make doable without modifying motoor.cpp manually later)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwSwapInterval(0);
}

mootor::~mootor()
{
	glfwTerminate();
	std::cout << "mootor killed" << std::endl;
}

void mootor::MakeWindow(int width, int height, const char* windowTitle)
{
	window = glfwCreateWindow(width, height, windowTitle, NULL, NULL);
	if (!window)
	{
		std::cout << "no window" << std::endl;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "glew not working" << std::endl;
	}
}

void mootor::SetWindowResizable(bool value)
{
	if (value == true)
	{
		glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_TRUE);
	}
	else
	{
		glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);
	}
}

double mootor::getTime()
{
	return glfwGetTime();
}

double mootor::printFps()
{
	timeValuesForFps[0] = timeValuesForFps[1];
	timeValuesForFps[1] = this->getTime();

	//tempfix
	//std::cout << 1 / (timeValuesForFps[1] - timeValuesForFps[0]) << std::endl;

	return 1 / (timeValuesForFps[1] - timeValuesForFps[0]);
}

void mootor::printFpsInt()
{
	timeValuesForFps[0] = timeValuesForFps[1];
	timeValuesForFps[1] = this->getTime();

	std::cout << int(1 / (timeValuesForFps[1] - timeValuesForFps[0])) << std::endl;
}

void mootor::printFpsSmoothed()
{
	timeValuesForFps[0] = timeValuesForFps[1];
	timeValuesForFps[1] = this->getTime();

	FpsHolderCount++;
	if (FpsHolderCount == 100)
	{
		FpsHolderCount = 0;
	}

	FpsHolder[FpsHolderCount] = 1 / (timeValuesForFps[1] - timeValuesForFps[0]);

	double total = 0;
	for (int i = 0; i < 100; i++)
	{
		total += FpsHolder[i];
	}

	std::cout << total / 100 << " " << int(1 / (timeValuesForFps[1] - timeValuesForFps[0])) << " " << FpsHolderCount << std::endl;
}

void mootor::Destroy()
{
	this->~mootor();
}

float* mootor::GetGlobalPosition()
{
	return m_globalPosition;
}

void mootor::UpdateViewMat(shaderManager base)
{
	viewMat[3] = this->m_globalPosition[0];
	viewMat[7] = this->m_globalPosition[1];

	static int loc = glGetUniformLocation(base.program, "viewMat");
	glUniformMatrix4fv(loc, 1, GL_TRUE, viewMat);
}

//bad code bad code patch later
void mootor::RefreshMousePosition()
{
	m_mousePosition[0] = GetMousePosition()[0];
	m_mousePosition[1] = GetMousePosition()[2];
}

//also patch later
double* mootor::GetMousePosition()
{
	double positionPtr[2] = {TMouse::GetMousePos(window).xPos, TMouse::GetMousePos(window).yPos};
	return positionPtr;
}
