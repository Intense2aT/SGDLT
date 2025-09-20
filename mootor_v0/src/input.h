#pragma once

struct position
{
	double xPos, yPos;
};

//T stands for trinket
namespace TMouse
{
	//these values here should not be changed manually
	const char* mousePos = "enabled";
	//

	position GetMousePos(GLFWwindow* window);

	//enabled, disabled or hidden
	void SetMouseStatus(GLFWwindow* window, const char* value);
	const char* GetMouseStatus();
}

namespace TBoard
{

}