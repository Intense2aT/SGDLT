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

void mootor::Destroy()
{
	this->~mootor();
}