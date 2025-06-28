#pragma once

#include "prerequisites.h"

namespace Engine
{
	constexpr auto SHADERS_LEN = 2;

	class ShaderProgram
	{
	public:
		ShaderProgram(const ShaderProgramDesc& desc);
		~ShaderProgram();
	
		ui32 GetId() const { return m_programId; }

		void SetUniformBufferSlot(const char* name, ui32 slot);
	private:
		void Attach(const wchar_t* shaderFilePath, const ShaderType& type);
		void Link() const;

		ui32 m_programId = 0;
		ui32 m_attachedShaders[SHADERS_LEN] = {};
	};

}
