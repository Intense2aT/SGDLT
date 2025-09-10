#pragma once

class mootor
{
private:

public:
	GLFWwindow* window;

	mootor();
	~mootor();

	void MakeWindow(int width, int height, const char* windowTitle);

	void kill();
};