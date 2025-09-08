#include <glew.h>
#include <glfw3.h>
#include "stb_image.h"

#include <iostream>
#include <string>

#include "standardObject.h"
#include "generatePrimitives.h"

int width, height;

int main()
{
	if (!glfwInit())
	{
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
	if (!window)
	{
		return -2;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height);
	std::cout << " user resized window" << std::endl;  });

	if (glewInit() != GLEW_OK)
	{
		std::cout << "glew not working" << std::endl;
		system("pause");
		return -3;
	}

	int success;
	char infoLog[512];

	const char* vertexShader = "#version 330\n"
		"layout(location = 0) in vec3 pCords;\n"
		"layout(location = 1) in vec3 colorInfo;\n"
		"out vec3 colors;\n"
		"void main() {\n"
		"	gl_Position = vec4(pCords, 1.0f);\n"
		"	colors = colorInfo;\n"
		"}\0";

	const char* fragmentShader = "#version 330\n"
		"out vec4 color;\n"
		"in vec3 colors;\n"
		"void main() {\n"
		"	color = vec4(0.5f, 0.1f, 0.7f, 1.0f);\n"
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

	float positions[18] = {
		-0.5f, -0.5f, 1.0f, //1.0f, 0.0f, 0.0f,
		 0.0f,  0.5f, 1.0f, //0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, 1.0f, //0.0f, 0.0f, 1.0f
	};

	//float* testArray = new float[12] {0};
	//unsigned int* testArray2 = new unsigned int[6] {0};
	//genSquare(testArray, testArray2, 0.5f, 0.5f, -1.0, -1.0);

	//for (int i = 0; i < 12; i++)
	//{
	//	std::cout << *(testArray + i) << std::endl;
	//}

	//std::cout << std::endl << std::endl << std::endl;

	//for (int i = 0; i < 6; i++)
	//{
		//std::cout << *(testArray2 + i) << std::endl;
	//}

	//standardObject indexBufferTest;
	//indexBufferTest.addData(testArray, 12 * sizeof(float), testArray2, 6 * sizeof(unsigned int));


	//MAKE SURE TO CHANGE TRIANGLE DEGREES IN BOTH clacCircleVBufferSize and genCircle func or it will cause memory problems
	int vBufferSize = calcCircleVBufferSize(6.0f);
	float* testArray3 = new float[vBufferSize] {0};
	unsigned int* testArray4 = new unsigned int[vBufferSize - 3] {0};
	genCircle(testArray3, testArray4, 6.0f, 0.5f, 0.0f, 0.0f);

	int vBufferSize2 = calcCircleVBufferSize(7.5f);
	float* testArray1 = new float[vBufferSize2] {0};
	unsigned int* testArray2 = new unsigned int[vBufferSize2 - 3] {0};
	genCircle(testArray1, testArray2, 7.5f, 0.5f, -1.0f, 0.0f);

	for (int i = 1; i < vBufferSize + 1; i++)
	{
		std::cout << *(testArray3 + i - 1) << " ";
		if (i % 3 == 0)
		{
			std::cout << std::endl;
		}
	}

	for (int i = 1; i < vBufferSize - 2; i++)
	{
		std::cout << *(testArray4 + i - 1) << " ";
		if (i % 3 == 0)
		{
			std::cout << std::endl;
		}
	}

	std::cout << vBufferSize * sizeof(float) + (vBufferSize - 3) + sizeof(unsigned int) << std::endl;

	standardObject circleObject;
	circleObject.addData(testArray3, vBufferSize * sizeof(float), testArray4, (vBufferSize - 3) * sizeof(unsigned int));

	standardObject circleObject2;
	circleObject2.addData(testArray1, vBufferSize2 * sizeof(float), testArray2, (vBufferSize2 - 3) * sizeof(unsigned int));

	/*
	unsigned int vbo, vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	*/

	//standardObject anotherObject;
	//anotherObject.addData(testArray, 18 * sizeof(float));
	//anotherObject.BindObject();

	//standardObject newObject;
	//newObject.addData(positions, 18 * sizeof(float));
	//newObject.BindObject();

	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//newObject.Draw(3);
		//anotherObject.Draw(6);
		circleObject.Draw();
		circleObject2.Draw();
		//indexBufferTest.Draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	delete[] testArray1;
	delete[] testArray2;
	delete[] testArray4;
	delete[] testArray3;

	glfwTerminate();

	system("pause");
	return 0;
}