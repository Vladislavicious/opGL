#include <fstream>
#include <sstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h> // подключение GLFW
#include "Shader.h"
#include "Renderer.h"

Shader::Shader(const std::string& filePath)
	: filePath(filePath), shaderID(0)
{
	ShaderProgramSource shaders = ParseShader(filePath);

	shaderID = CreateShader(shaders.vertexShader, shaders.fragmentShader);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(shaderID));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(shaderID));
}

void Shader::UnBind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int layer)
{
	int uniformLocation = GetUniformLocation(name);

	GLCall(glUniform1i(uniformLocation, layer));
}

void Shader::SetUniform1f(const std::string& name, float v)
{
	int uniformLocation = GetUniformLocation(name);

	GLCall(glUniform1f(uniformLocation, v));
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
	int uniformLocation = GetUniformLocation(name);
	GLCall(glUniform3f(uniformLocation, v0, v1, v2));
}

void Shader::SetUniform3f(const std::string& name, glm::vec3 v)
{
	int uniformLocation = GetUniformLocation(name);
	GLCall(glUniform3f(uniformLocation, v.x, v.y, v.z));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	int uniformLocation = GetUniformLocation(name);
	GLCall(glUniform4f(uniformLocation, v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string& name, glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string name)
{
	if (uniformLocationsMap.find(name) != uniformLocationsMap.end())
	{
		return uniformLocationsMap[name];
	}

	int uniformLocation;

	GLCall(uniformLocation = glGetUniformLocation(shaderID, name.c_str()));

	if (uniformLocation == -1)
		std::cout << "there's no uniform " << name << std::endl;

	uniformLocationsMap[name] = uniformLocation;
	return uniformLocation;
}

ShaderProgramSource Shader::ParseShader(const std::string& filePath)
{
	std::ifstream fstream(filePath);

	if (!fstream.is_open())
	{
		std::cout << "Could not open " << filePath;
	}

	ShaderType mode = ShaderType::NONE;

	std::string line;

	std::stringstream shaders[2];

	while (getline(fstream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				mode = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				mode = ShaderType::FRAGMENT;
			}
		}
		else
		{
			shaders[(int)mode] << line << "\n";
		}
	}

	ShaderProgramSource outputShaders(shaders[0].str(), shaders[1].str());

	return outputShaders;
}

unsigned int Shader::CompileShader(unsigned int shaderType, const std::string& sourceShaderCode)
{
	unsigned int shaderId = glCreateShader(shaderType);
	const char* sourceCode = sourceShaderCode.c_str();
	GLCall(glShaderSource(shaderId, 1, &sourceCode, nullptr));
	GLCall(glCompileShader(shaderId));

	int result;
	GLCall(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result));

	if (result == GL_FALSE)
	{
		int errorLength;
		GLCall(glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &errorLength));
		char* errorMessage = (char*)alloca(sizeof(char) * errorLength);
		GLCall(glGetShaderInfoLog(shaderId, errorLength, &errorLength, errorMessage));

		std::cout << "failed to compile " << (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
		std::cout << errorMessage << std::endl;

		GLCall(glDeleteShader(shaderId));
		return 0;
	}

	return shaderId;
}

unsigned int Shader::CreateShader(const std::string& VertexShader, const std::string& FragmentShader)
{
	unsigned int vertexShaderIndex = CompileShader(GL_VERTEX_SHADER, VertexShader);
	unsigned int fragmentShaderIndex = CompileShader(GL_FRAGMENT_SHADER, FragmentShader);

	auto programIndex = glCreateProgram();

	GLCall(glAttachShader(programIndex, vertexShaderIndex));
	GLCall(glAttachShader(programIndex, fragmentShaderIndex));

	GLCall(glLinkProgram(programIndex));
	GLCall(glValidateProgram(programIndex));

	GLCall(glDeleteShader(vertexShaderIndex));
	GLCall(glDeleteShader(fragmentShaderIndex));

	return programIndex;
}
