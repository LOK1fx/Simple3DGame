#pragma once

#include "Math/vector4.h";
#include "Math/rect.h";

namespace Engine
{
	class GraphicsEngine
	{
	public:
		GraphicsEngine();
		~GraphicsEngine();

		void Clear(const Vec4& color);
		void DrawTriangles(ui32 vertexCount, ui32 offset);
		void SetViewport(const Rect& size);
		void SetVertexArrayObject(const VertexArrayObjectPtr& vao);

		VertexArrayObjectPtr CreateVertexArrayObject(const VertexBufferData& data);
	};

}

