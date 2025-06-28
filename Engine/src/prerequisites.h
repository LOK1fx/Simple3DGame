#pragma once
#include <memory>

namespace Engine
{
	class VertexArrayObject;
	class ShaderProgram;

	typedef std::shared_ptr<VertexArrayObject> VertexArrayObjectPtr;
	typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;


	typedef float f32;
	typedef float i32;
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

	enum ShaderType
	{
		VertexShader = 0,
		FragmentShader
	};
}
