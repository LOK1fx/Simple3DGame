#include "vertexarrayobject.h"

#include <glad/glad.h>

namespace Engine
{
	VertexArrayObject::VertexArrayObject(const VertexBufferDesc& data)
	{
		glGenVertexArrays(1, &m_vertexArrayObjectId);
		glBindVertexArray(m_vertexArrayObjectId);

		glGenBuffers(1, &m_vertexBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
		glBufferData(GL_ARRAY_BUFFER, data.vertexSize*data.listSize, data.verticesList, GL_STATIC_DRAW);

		
		for (ui32 i = 0; i < data.attributesListSize; i++)
		{
			void* attributeOffset = (void*)((i == 0) ? 0 : data.attributeList[i - 1].numElements * sizeof(f32));

			glVertexAttribPointer(i, data.attributeList[i].numElements,
				GL_FLOAT, GL_FALSE, data.vertexSize, attributeOffset);
			glEnableVertexAttribArray(i);
		}
		

		glBindVertexArray(0);

		m_vertexBufferData = data;
	}

	VertexArrayObject::~VertexArrayObject()
	{
		glDeleteBuffers(1, &m_vertexBufferId);
		glDeleteVertexArrays(1, &m_vertexArrayObjectId);
	}
}

