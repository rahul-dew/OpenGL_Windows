#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <openglDebug.h>
#include <shaderHelper.h>
#include <iostream>

#define USE_GPU_ENGINE 0
extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = USE_GPU_ENGINE;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = USE_GPU_ENGINE;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const GLint SCR_WIDTH = 600, SCR_HEIGHT = 600;

int main(void)
{
	if (!glfwInit())
		return -1;

#pragma region report opengl errors to std
	//enable opengl debugging output.
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#pragma endregion

	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //you might want to do this when testing the game for shipping

	GLFWwindow* window = window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	int bufferWidth = 0, bufferHeight = 0;
	glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	glViewport(0, 0, bufferWidth, bufferHeight);

#pragma region report opengl errors to std
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(glDebugOutput, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
#pragma endregion

	//shader loading example
	Shader shader;
	shader.loadShaderProgramFromFile(RESOURCES_PATH "vertex.vert", RESOURCES_PATH "fragment.frag");

	//define vertices for the circle
	const int numSegments = 25;
	float innerRadius = 0.25f;
	float outerRadius = 0.30f;
	float centerPoint[3] = { 0.0f, 0.0f, 0.0f };
	float verticesInner[numSegments * 3];
	float verticesOuter[numSegments * 3];

	//Generate vertices
	for (int i = 0; i < numSegments; i++) {
		float theta = 2.0f * 3.14159 * static_cast<float>(i) / static_cast<float>(numSegments);
		verticesInner[3 * i] = centerPoint[0] + innerRadius * cos(theta);
		verticesInner[3 * i + 1] = centerPoint[1] + innerRadius * sin(theta);
		verticesInner[3 * i + 2] = centerPoint[2];

		verticesOuter[3 * i] = centerPoint[0] + outerRadius * cos(theta);
		verticesOuter[3 * i + 1] = centerPoint[1] + outerRadius * sin(theta);
		verticesOuter[3 * i + 2] = centerPoint[2];
	}

	//combine vertices
	float vertices[6 * numSegments + 6];
	for (int i = 0; i < numSegments; i++) {
		vertices[6 * i] = verticesInner[3 * i];
		vertices[6 * i + 1] = verticesInner[3 * i + 1];
		vertices[6 * i + 2] = verticesInner[3 * i + 2];
		vertices[6 * i + 3] = verticesOuter[3 * i];
		vertices[6 * i + 4] = verticesOuter[3 * i + 1];
		vertices[6 * i + 5] = verticesOuter[3 * i + 2];
	}
	vertices[6 * numSegments] = vertices[0];
	vertices[6 * numSegments + 1] = vertices[1];
	vertices[6 * numSegments + 2] = vertices[2];
	vertices[6 * numSegments + 3] = vertices[3];
	vertices[6 * numSegments + 4] = vertices[4];
	vertices[6 * numSegments + 5] = vertices[5];

	unsigned int VBO, VAO;
	//bind the vertex array object first, then bind and set vertex buffer(s)
	//then configure vertex attribute(s)
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//render loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//draw triangle
		shader.bind();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 2 * numSegments + 2);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//cleaning
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	//shader.clear();

	//there is no need to call the clear function for the libraries since the os will do that for us.
	//by calling this functions we are just wasting time.
	//glfwDestroyWindow(window);
	//glfwTerminate();
	return 0;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
