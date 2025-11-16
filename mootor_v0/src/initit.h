#pragma once

class mootor
{
private:
	double timeValuesForFps[2] = { 0.0f, 0.0f };

	float m_globalPosition[2] = {0.0f, 0.0f}; //use for player position
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
	void printFps();
	void printFpsInt();

	void Destroy();

	//to get/modify player position
	float* GetGlobalPosition();
	void SetGlobalPosition(float x, float y) { m_globalPosition[0] = x; m_globalPosition[1] = y; };
};