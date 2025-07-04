#include "uniformbuffer.h"
#include <glad/glad.h>

namespace Engine
{
	UniformBuffer::UniformBuffer(const UniformBufferDesc& desc)
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_UNIFORM_BUFFER, m_id);
		glBufferData(GL_UNIFORM_BUFFER, desc.size, nullptr, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		m_size = desc.size;
	}

	UniformBuffer::~UniformBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}

	void UniformBuffer::SetData(void* data)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_id);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, m_size, data);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}