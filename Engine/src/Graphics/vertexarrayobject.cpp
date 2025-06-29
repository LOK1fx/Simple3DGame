#include "vertexarrayobject.h"

#include <glad/glad.h>

namespace Engine
{
	VertexArrayObject::VertexArrayObject(const VertexBufferDesc& vbDesc)
	{
		ENGINE_ASSERT(vbDesc.listSize, "listSize is NULL");
		ENGINE_ASSERT(vbDesc.vertexSize, "vertexSize is NULL");
		ENGINE_ASSERT(vbDesc.verticesList, "verticesList is NULL");

		glGenVertexArrays(1, &m_vertexArrayObjectId);
		glBindVertexArray(m_vertexArrayObjectId);

		glGenBuffers(1, &m_vertexBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
		glBufferData(GL_ARRAY_BUFFER, vbDesc.vertexSize*vbDesc.listSize, vbDesc.verticesList, GL_STATIC_DRAW);

		
		for (ui32 i = 0; i < vbDesc.attributesListSize; i++)
		{
			void* attributeOffset = (void*)((i == 0) ? 0 : vbDesc.attributeList[i - 1].numElements * sizeof(f32));

			glVertexAttribPointer(i, vbDesc.attributeList[i].numElements,
				GL_FLOAT, GL_FALSE, vbDesc.vertexSize, attributeOffset);
			glEnableVertexAttribArray(i);
		}
		

		glBindVertexArray(0);

		m_vertexBufferData = vbDesc;
	}

	VertexArrayObject::VertexArrayObject(const VertexBufferDesc& vbDesc, const IndexBufferDesc& ibDesc)
		: VertexArrayObject(vbDesc)
	{
		ENGINE_ASSERT(ibDesc.listSize, "listSize is NULL");
		ENGINE_ASSERT(ibDesc.indicesList, "indicesList is NULL");

		glBindVertexArray(m_vertexArrayObjectId);

		glGenBuffers(1, &m_elementBufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibDesc.listSize, ibDesc.indicesList, GL_STATIC_DRAW);


		glBindVertexArray(0);
	}

	VertexArrayObject::~VertexArrayObject()
	{
		glDeleteBuffers(1, &m_elementBufferId);
		glDeleteBuffers(1, &m_vertexBufferId);
		glDeleteVertexArrays(1, &m_vertexArrayObjectId);
	}
}

