#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>


class Shader
{
public:
	unsigned int ID;

	Shader(const std::string& vertexPath, const std::string& fragmentPath)
	{
		std::string vertexCode, fragmentCode;
		std::stringstream vertexStream, fragmentStream;
		std::ifstream vertexFile, fragmentFile;

		// modules

		vertexFile.open(vertexPath);
		vertexStream << vertexFile.rdbuf();
		vertexCode = vertexStream.str();
		const char* vCode = vertexCode.c_str();
		vertexFile.close();

		fragmentFile.open(fragmentPath);
		fragmentStream << fragmentFile.rdbuf();
		fragmentCode = fragmentStream.str();
		const char* fCode = fragmentCode.c_str();
		fragmentFile.close();

		int success;
		char infoLog[512];

		unsigned int vertexModule = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexModule, 1, &vCode, NULL);
		glCompileShader(vertexModule);

		glGetShaderiv(vertexModule, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexModule, 512, NULL, infoLog);
			std::cout << "Failed to compile module from " << vertexPath << "\n" << infoLog << std::endl;
		}

		unsigned int fragmentModule = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentModule, 1, &fCode, NULL);
		glCompileShader(fragmentModule);

		glGetShaderiv(fragmentModule, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentModule, 512, NULL, infoLog);
			std::cout << "Failed to compile module from " << fragmentPath << "\n" << infoLog << std::endl;
		}

		// program

		ID = glCreateProgram();

		glAttachShader(ID, vertexModule);
		glAttachShader(ID, fragmentModule);
		glLinkProgram(ID);

		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(ID, 512, NULL, infoLog);
			std::cout << "Failed to link program\n" << infoLog << std::endl;
		}

		glDeleteShader(vertexModule);
		glDeleteShader(fragmentModule);
	}

	void use()
	{
		glUseProgram(ID);
	}

	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string& name, float value0, float value1, float value2, float value3) const
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), value0, value1, value2, value3);
	}
};

#endif // !SHADER_H
