#pragma once

class mootor
{
private:

public:
	float projMat[16] = { 1.0f, 0.0f, 0.0f, 0.0f,
					  0.0f, 1.0f, 0.0f, 0.0f,
					  0.0f, 0.0f, 1.0f, 0.0f,
					  0.0f, 0.0f, 0.0f, 1.0f };
	GLFWwindow* window;

	mootor();
	~mootor();

	void MakeWindow(int width, int height, const char* windowTitle);

	void SetWindowResizable(bool value);

	double getTime();

	void Destroy();
};