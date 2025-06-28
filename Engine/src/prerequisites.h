#pragma once
#include <memory>
#include "core.h"

namespace Engine
{


	class VertexArrayObject;
	class UniformBuffer;
	class ShaderProgram;

	typedef std::shared_ptr<VertexArrayObject> VertexArrayObjectPtr;
	typedef std::shared_ptr<UniformBuffer> UniformBufferPtr;
	typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;


	typedef float f32;
	typedef int i32;
	typedef unsigned int ui32;
	typedef unsigned char uc16;

	struct VertexAttribute
	{
		ui32 numElements = 0;
	};

	struct VertexBufferDesc
	{
		void* verticesList = nullptr;
		ui32 vertexSize = 0;
		ui32 listSize = 0;

		VertexAttribute* attributeList = nullptr;
		ui32 attributesListSize = 0;
	};

	struct ShaderProgramDesc
	{
		const wchar_t* vertexShaderFilePath;
		const wchar_t* fragmentShaderFilePath;
	};

	struct UniformBufferDesc
	{
		ui32 size = 0;
	};

	enum TriangleType
	{
		TriangleList = 0,
		TriangleStrip,
	};

	enum ShaderType
	{
		VertexShader = 0,
		FragmentShader
	};
}
