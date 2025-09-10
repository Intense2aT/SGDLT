#include <glew.h>
#include <glfw3.h>

#include "initit.h"

#include <iostream>
#include <fstream>
#include <string>

#include "standardObject.h"
#include "generatePrimitives.h"

int width, height;
int colorUniform;

void SetDrawingColor(float* color);

int main()
{
	mootor mootor;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mootor.MakeWindow(800, 600, "Window Title");

	glfwSetFramebufferSizeCallback(mootor.window, [](GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height);
	std::cout << " user resized window" << std::endl;  });

	int success;
	char infoLog[512];

	const char* vertexShader = "#version 330\n"
		"layout(location = 0) in vec3 pCords;\n"
		"out vec3 colors;\n"
		"void main() {\n"
		"	gl_Position = vec4(pCords, 1.0f);\n"
		"}\0";

	const char* fragmentShader = "#version 330\n"
		"out vec4 color;\n"
		"uniform vec4 colors;\n"
		"void main() {\n"
		"	color = colors;\n"
		"}\0";

	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertexShader, NULL);
	glCompileShader(vs);

	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragmentShader, NULL);
	glCompileShader(fs);

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vs);
	glAttachShader(shaderProgram, fs);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//glDeleteShader(vs);
	//glDeleteShader(fs);

	int colorUniform = glGetUniformLocation(shaderProgram, "colors\0");
	float color1[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	float color2[4] = { 1.0f, 0.0f, 0.0f, 1.0f };

	standardObject circleObject(0.0f, 0.0f);
	circleObject.MakeCircle(0.5f);

	standardObject squareObject(0.0f, -0.5f);
	squareObject.MakeSquare(0.5f, 1.0f);

	while (!glfwWindowShouldClose(mootor.window))
	{
		/* Render here */
		glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		SetDrawingColor(color1);
		circleObject.Draw();
		SetDrawingColor(color2);
		squareObject.Draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(mootor.window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	mootor.kill();

	return 0;
}

void SetDrawingColor(float *color)
{
	glUniform4f(colorUniform, color[0], color[1], color[2], color[3]);
}