#ifndef SHADER_H_
#define SHADER_H_


#include <iostream>

#include <unordered_map>
#include <vector>

struct ShaderProgramSource {
public:
	std::string vertexShader;
	std::string fragmentShader;

	ShaderProgramSource(std::string verShader, std::string fragShader)
	{
		vertexShader = verShader;
		fragmentShader = fragShader;
	}
};

enum ShaderType
{
	NONE = -1,
	VERTEX = 0,
	FRAGMENT = 1
};


class Shader
{
private:
	std::string filePath;

	std::unordered_map<std::string, int> uniformLocationsMap;

	std::vector<std::string> attribLocations;

	unsigned int shaderID;
public:
	Shader(const std::string& filePath, std::vector<std::string> Locations);
	~Shader();

	void Bind() const;
	void UnBind() const;

	void SetUniform1i(const std::string& name, int layer);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private://functions
	int GetUniformLocation(const std::string name);

	ShaderProgramSource ParseShader(const std::string& filePath);

	unsigned int CompileShader(unsigned int shaderType, const std::string& sourceShaderCode);

	unsigned int CreateShader(const std::string& VertexShader, const std::string& FragmentShader);

	void bindAttribLocation(const unsigned int shader_programme);
};

#endif // !SHADER_H_
