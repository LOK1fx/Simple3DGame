#pragma once
#include <memory>

namespace Engine
{
	class VertexArrayObject;

	typedef std::shared_ptr<VertexArrayObject> VertexArrayObjectPtr;


	typedef float f32;
	typedef float i32;
	typedef unsigned int ui32;
	typedef unsigned char uc16;

	struct VertexBufferData
	{
		void* verticesList = nullptr;
		ui32 vertexSize = 0;
		ui32 listSize = 0;
	};
}
