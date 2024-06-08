/*
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include "shader.h"



// functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
//unsigned int makeModule(const std::string& path, unsigned int module_type);
//unsigned int makeProgram(unsigned int vertex, unsigned int fragment);

// main
int main()
{
	// init

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}
	GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Test", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	// viewport

	glViewport(0, 0, 640, 480);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	// vertex definition and compilation

	//unsigned int vertexShader = makeModule(RESOURCES_PATH "vertex.vert", GL_VERTEX_SHADER);

	//// fragment definition and compilation

	//unsigned int fragmentShader1 = makeModule(RESOURCES_PATH "fragment1.frag", GL_FRAGMENT_SHADER);
	//unsigned int fragmentShader2 = makeModule(RESOURCES_PATH "fragment2.frag", GL_FRAGMENT_SHADER);

	//// shader program

	//unsigned int shaderProgram1 = makeProgram(vertexShader, fragmentShader1);
	//unsigned int shaderProgram2 = makeProgram(vertexShader, fragmentShader2);

	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader1);
	//glDeleteShader(fragmentShader2);

	Shader shaderProgram1(RESOURCES_PATH "vertex.vert", RESOURCES_PATH "fragment1.frag");
	Shader shaderProgram2(RESOURCES_PATH "vertex.vert", RESOURCES_PATH "fragment2.frag");

	// triangle corners

	float triangle1[] = {
			-0.8f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,
			 0.0f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,
			-0.4f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f
	};
	float triangle2[] = {
			 0.4f, -0.5f, 0.0f,
			 0.8f,  0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
	};
	unsigned int indices[] = {
		0, 1, 2,
		3, 4, 5
	};

	// Vertex Buffer Object, Vertex Array Object and Element Buffer Object

	unsigned int VBOs[2], VAOs[2];
	glGenBuffers(2, VBOs);
	glGenVertexArrays(2, VAOs);
	//glGenBuffers(1, &EBO);

	glBindVertexArray(VAOs[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// link vertex attributes

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// unbind VBO and VAO

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// polygon mode: drawing lines

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//
	
	


	// render loop
	
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.25f, 0.5f, 0.75f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		

		shaderProgram1.use();
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		shaderProgram2.use();

		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		
		shaderProgram2.setFloat("ourColor", 0.0f, greenValue, 1.0f, 1.0f);
		//int vertexColorLocation = glGetUniformLocation(shaderProgram2, "ourColor");
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 1.0f, 1.0f);
		//glUniform4f(glGetUniformLocation(shaderProgram2.ID, "ourColor"), 0.0f, greenValue, 1.0f, 1.0f);

		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);

		
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glDeleteProgram(shaderProgram1.ID);
	glDeleteProgram(shaderProgram2.ID);

	glfwTerminate();
	return 0;
}


// callback on window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// process escape input to close window
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

/*

unsigned int makeModule(const std::string& path, unsigned int module_type)
{
	std::string line;
	std::stringstream text;
	std::ifstream file;

	file.open(path);
	if (!file) std::cout << "File couldn't be opened" << std::endl;

	while (std::getline(file, line))
	{
		text << line << "\n";
	}
	
	std::string sourceStr = text.str();
	const char* source = sourceStr.c_str();
	text.str("");
	file.close();

	unsigned int shaderModule = glCreateShader(module_type);
	glShaderSource(shaderModule, 1, &source, NULL);
	glCompileShader(shaderModule);

	int success;
	char infoLog[512];
	glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderModule, 512, NULL, infoLog);
		std::cout << "Failed to compile module from " << path << "\n" << infoLog << std::endl;
	}

	return shaderModule;
}

unsigned int makeProgram(unsigned int vertex, unsigned int fragment)
{
	unsigned int program = glCreateProgram();

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);

	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(program, 512, NULL, infoLog);
		std::cout << "Failed to link program\n" << infoLog << std::endl;
	}

	return program;
}

*/