#pragma once
#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

enum class ShaderType
{
	NONE = -1, VERTEX = 0, FRAGMENT = 1
};

class Shader
{
public:
	Shader(const std::string& filePath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//This would be a template set uniform functions pass shader source code.  Set value would set everything for you
	void SetUnform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUnform1i(const std::string& name, int value);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	const std::string& mFilePath;
	unsigned int mRendererId;
	std::unordered_map<std::string, int> mUniformLocation;

	int GetUnformLocation(const std::string& name);

	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	ShaderProgramSource  ParseShader();
};
