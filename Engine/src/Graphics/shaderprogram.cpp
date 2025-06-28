#include "shaderprogram.h"

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <vector>

namespace Engine
{
	ShaderProgram::ShaderProgram(const ShaderProgramDesc& desc)
	{
		m_programId = glCreateProgram();

		Attach(desc.vertexShaderFilePath, VertexShader);
		Attach(desc.fragmentShaderFilePath, FragmentShader);

		Link();
	}

	ShaderProgram::~ShaderProgram()
	{
		for (ui32 i = 0; i < SHADERS_LEN; i++)
		{
			glDetachShader(m_programId, m_attachedShaders[i]);
			glDeleteShader(m_attachedShaders[i]);
		}

		glDeleteProgram(m_programId);
	}

	void ShaderProgram::SetUniformBufferSlot(const char* name, ui32 slot)
	{
		ui32 index = glGetUniformBlockIndex(m_programId, name);
		
		glUniformBlockBinding(m_programId, index, slot);
	}

	void ShaderProgram::Attach(const wchar_t* shaderFilePath, const ShaderType& type)
	{
		std::string shaderCode;
		std::ifstream shaderStream(shaderFilePath);

		if (shaderStream.is_open())
		{
			std::stringstream sstr;
			sstr << shaderStream.rdbuf();
			shaderCode = sstr.str();
			shaderStream.close();
		}
		else
		{
			OGL3D_WARNING("ShaderProgram::Attach | " << shaderFilePath << " not found");

			return;
		}

		ui32 shaderId = 0;
		switch (type)
		{
		case VertexShader:
		{
			shaderId = glCreateShader(GL_VERTEX_SHADER);
			break;
		}
		case FragmentShader:
		{
			shaderId = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		}
		default:
			break;
		}

		auto sourcePointer = shaderCode.c_str();
		glShaderSource(shaderId, 1, &sourcePointer, NULL);
		glCompileShader(shaderId);

		i32 logLength = 0;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0)
		{
			std::vector<char> errorMessage(logLength + 1);
			glGetShaderInfoLog(shaderId, logLength, NULL, &errorMessage[0]);
			OGL3D_WARNING("ShaderProgram::Attach | " << shaderFilePath << " compiled with errors:" << std::endl << &errorMessage[0]);
			return;
		}

		glAttachShader(m_programId, shaderId);
		m_attachedShaders[type] = shaderId;

		OGL3D_INFO("ShaderProgram | " << shaderFilePath << " compiled successfully.");
	}

	void ShaderProgram::Link() const
	{
		i32 logLength = 0;
		glGetShaderiv(m_programId, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0)
		{
			std::vector<char> errorMessage(logLength + 1);
			glGetShaderInfoLog(m_programId, logLength, NULL, &errorMessage[0]);
			OGL3D_WARNING("ShaderProgram::Link | "  << &errorMessage[0]);
			return;
		}

		glLinkProgram(m_programId);
	}
}