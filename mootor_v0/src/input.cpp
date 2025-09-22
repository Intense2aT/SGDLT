#include <glfw3.h>

#include "input.h"
#include "initit.h"
 
#include <iostream>

//these values here should not be changed manually
const char* TMouse::mouseStatus = "enabled";
//

position TMouse::GetMousePos(GLFWwindow* window)
{
	position mousePos;
	glfwGetCursorPos(window, &mousePos.xPos, &mousePos.yPos);

	return mousePos;
}

void TMouse::SetMouseStatus(GLFWwindow* window, const char* value)
{
	if (value == "enabled")
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else if (value == "disabled")
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else if (value == "hidden")
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
	else
	{
		std::cout << "SetMouseStatus() function error. Input.cpp/Input.h" << std::endl;
	}

	mouseStatus = value;
}

const char* TMouse::GetMouseStatus()
{
	return mouseStatus;
}