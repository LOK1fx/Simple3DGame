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

		void SetFaceCulling(const CullType& type);
		void SetWindingOrder(const WindingOrderType& type);

		void DrawTriangles(const TriangleType& type, ui32 vertexCount, ui32 offset);
		void DrawIndexedTriangles(const TriangleType& type, ui32 indicesCount);

		void SetViewport(const Rect& size);

		void SetVertexArrayObject(const VertexArrayObjectPtr& vao);
		void SetUniformBuffer(const UniformBufferPtr& buffer, ui32 slot);
		void SetShaderProgram(const ShaderProgramPtr& program);

		VertexArrayObjectPtr CreateVertexArrayObject(const VertexBufferDesc& data);
		VertexArrayObjectPtr CreateVertexArrayObject(const VertexBufferDesc& vbDesc, const IndexBufferDesc& ibDesc);
		UniformBufferPtr CreateUniformBuffer(const UniformBufferDesc& desc);
		ShaderProgramPtr CreateShaderProgram(const ShaderProgramDesc& desc);
	};

}

