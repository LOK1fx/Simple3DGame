#include "shaderprogram.h"

#include <glad/glad.h>
#include <fstream>
#include <sstream>

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

		glAttachShader(m_programId, shaderId);
		m_attachedShaders[type] = shaderId;
	}

	void ShaderProgram::Link()
	{
		glLinkProgram(m_programId);
	}
}