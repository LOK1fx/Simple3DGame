#pragma once

#include "prerequisites.h"

namespace Engine
{
	class VertexArrayObject
	{
	public:
		VertexArrayObject(const VertexBufferDesc& vbDesc);
		VertexArrayObject(const VertexBufferDesc& vbDesc, const IndexBufferDesc& ibDesc);
		~VertexArrayObject();

		ui32 GetId() const { return m_vertexArrayObjectId; }
		ui32 GetVertexBufferSize() const { return m_vertexBufferData.listSize; }
		ui32 GetVertexSize() const { return m_vertexBufferData.vertexSize; }
	private:
		ui32 m_vertexBufferId = 0;
		ui32 m_vertexArrayObjectId = 0;
		ui32 m_elementBufferId = 0;

		VertexBufferDesc m_vertexBufferData;
	};

}
