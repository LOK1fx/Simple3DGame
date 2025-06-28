#pragma once

#include "prerequisites.h"

namespace Engine
{
	class UniformBuffer
	{
	public:
		UniformBuffer(const UniformBufferDesc& desc);
		~UniformBuffer();

		ui32 GetId() const { return m_id; }

		void SetData(void* data);
	private:
		ui32 m_id = 0;
		ui32 m_size = 0;
	};

}

