#ifndef SHADER_H_
#define SHADER_H_

#include <unordered_map>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct ShaderProgramSource {
public:
	std::string vertexShader;
	std::string fragmentShader;

	ShaderProgramSource(const std::string& verShader, const std::string& fragShader):
		vertexShader(verShader), fragmentShader(fragShader) {}
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
	std::string m_vsFilePath;
	std::string m_fsFilePath;

	std::unordered_map<std::string, int> uniformLocationsMap;

	unsigned int shaderID;
public:
	Shader(const std::string& vsFilePath, const std::string& fsFilePath);
	~Shader();

	void Bind() const;
	void UnBind() const;
	void SetUniform1i(const std::string& name, int layer);
	void SetUniform1f(const std::string& name, float v);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform3f(const std::string& name, glm::vec3 v);
	void SetUniformMat4f(const std::string& name, glm::mat4& matrix);

private://functions
	int GetUniformLocation(const std::string& name);

	ShaderProgramSource ParseShader(const std::string& vsFilePath, const std::string& fsFilePath);

	unsigned int CompileShader(unsigned int shaderType, const std::string& sourceShaderCode);

	unsigned int CreateShader(const std::string& VertexShader, const std::string& FragmentShader);
};

#endif // !SHADER_H_
