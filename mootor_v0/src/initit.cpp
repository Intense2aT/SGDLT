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
}

mootor::~mootor()
{
	glfwTerminate();
	std::cout << "mootor killed" << std::endl;
}

void mootor::MakeWindow(int width, int height, const char* windowTitle)
{
	window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
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

void mootor::kill()
{
	this->~mootor();
}