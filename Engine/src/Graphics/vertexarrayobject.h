#pragma once

#include "prerequisites.h"

namespace Engine
{
	class VertexArrayObject
	{
	public:
		VertexArrayObject(const VertexBufferData& data);
		~VertexArrayObject();

		ui32 GetId() const { return m_vertexArrayObjectId; }
		ui32 GetVertexBufferSize() const { return m_vertexBufferData.listSize; }
		ui32 GetVertexSize() const { return m_vertexBufferData.vertexSize; }
	private:
		ui32 m_vertexBufferId = 0;
		ui32 m_vertexArrayObjectId = 0;
		VertexBufferData m_vertexBufferData;
	};

}
