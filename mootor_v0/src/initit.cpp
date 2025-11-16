#include <glew.h>
#include <glfw3.h>

#include "initit.h"
#include <iostream>

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
	//disabling vsync to uncap framerate!!! NEED DELTA TIME IMPLEMENTATION
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

void mootor::printFps()
{
	timeValuesForFps[0] = timeValuesForFps[1];
	timeValuesForFps[1] = this->getTime();

	std::cout << 1 / (timeValuesForFps[1] - timeValuesForFps[0]) << std::endl;
}

void mootor::printFpsInt()
{
	timeValuesForFps[0] = timeValuesForFps[1];
	timeValuesForFps[1] = this->getTime();

	std::cout << int(1 / (timeValuesForFps[1] - timeValuesForFps[0])) << std::endl;
}

void mootor::Destroy()
{
	this->~mootor();
}

float* mootor::GetGlobalPosition()
{
	return m_globalPosition;
}
