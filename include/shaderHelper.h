#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

struct Shader
{
	GLuint id = 0;

	bool loadShaderProgramFromData(const char *vertexShaderData, const char *fragmentShaderData);
	bool loadShaderProgramFromData(const char *vertexShaderData,
		const char *geometryShaderData, const char *fragmentShaderData);

	bool loadShaderProgramFromFile(const char *vertexShader, const char *fragmentShader);
	bool loadShaderProgramFromFile(const char *vertexShader,
		const char *geometryShader, const char *fragmentShader);

	void bind();

	void clear();

	void setBoolean(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
	void setVec2(const std::string& name,  const glm::vec2& value);
	void setVec2(const std::string& name,  float x, float y);
	void setVec3(const std::string& name,  const glm::vec3& value);
	void setVec3(const std::string& name,  float x, float y, float z);
	void setVec4(const std::string& name, const glm::vec4& value);
	void setVec4(const std::string& name,  float x, float y, float z, float w);
	void setMat2(const std::string& name, const glm::mat2& mat);
	void setMat3(const std::string& name, const glm::mat3& mat);
	void setMat4(const std::string& name, const glm::mat4& mat);
	
};
