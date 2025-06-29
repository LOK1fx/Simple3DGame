#include "GraphicsEngine.h"

#include <glad/glad_wgl.h>
#include <glad/glad.h>
#include <assert.h>
#include <stdexcept>

#include "Graphics/vertexarrayobject.h"
#include "Graphics/uniformbuffer.h"
#include "Graphics/shaderprogram.h"


namespace Engine
{
	GraphicsEngine::GraphicsEngine()
	{
		WNDCLASSEX wc = { };

		const wchar_t* className = L"3DDummy";
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.lpszClassName = className;
		wc.lpfnWndProc = DefWindowProc;
		wc.style = CS_OWNDC;

		auto classId = RegisterClassEx(&wc);
		assert(classId);

		long wProps = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;

		HWND dummyWindow = CreateWindowEx(NULL, MAKEINTATOM(classId), L"3DDummy OpenGL Game", wProps,
			CW_USEDEFAULT, CW_USEDEFAULT,\
			CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, NULL, NULL);

		assert(dummyWindow);

		HDC deviceContext = GetDC(dummyWindow);
		PIXELFORMATDESCRIPTOR descriptor = { };
		descriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		descriptor.nVersion = 1;
		descriptor.iPixelType = PFD_TYPE_RGBA;
		descriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		descriptor.cColorBits = 32;
		descriptor.cAlphaBits = 8;
		descriptor.cDepthBits = 24;
		descriptor.cStencilBits = 8;
		descriptor.iLayerType = PFD_MAIN_PLANE;

		int pixelFormat =  ChoosePixelFormat(deviceContext, &descriptor);
		SetPixelFormat(deviceContext, pixelFormat, &descriptor);

		HGLRC context = wglCreateContext(deviceContext);
		assert(context);

		wglMakeCurrent(deviceContext, context);

		if (!gladLoadWGL(deviceContext))
			OGL3D_ERROR("failed gladLoadWGL");

		if (!gladLoadGL())
			OGL3D_ERROR("failed gladLoadGL");

		wglMakeCurrent(deviceContext, 0);
		wglDeleteContext(context);
		ReleaseDC(dummyWindow, deviceContext);
		DestroyWindow(dummyWindow);
	}
	
	GraphicsEngine::~GraphicsEngine()
	{
	}

	void GraphicsEngine::Clear(const Vec4& color)
	{
		glClearColor(color.X, color.Y, color.Z, color.W);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void GraphicsEngine::SetFaceCulling(const CullType& type)
	{
		auto cullType = GL_BACK;

		switch (type)
		{
		case CullType::FrontFace:
		{
			cullType = GL_FRONT;
			break;
		}
		case CullType::BackFace:
		{
			cullType = GL_BACK;
			break;
		}
		case CullType::Both:
		{
			cullType = GL_FRONT_AND_BACK;
			break;
		}
		default:
			break;
		}

		glEnable(GL_CULL_FACE);
		glCullFace(cullType);
	}

	void GraphicsEngine::SetWindingOrder(const WindingOrderType& type)
	{
		auto orderType = GL_CW;

		switch (type)
		{
		case WindingOrderType::ClockWise:
		{
			orderType = GL_CW;
			break;
		}
		case WindingOrderType::CounterClockWise:
		{
			orderType = GL_CCW;
			break;
		}
		default:
			break;
		}

		glFrontFace(orderType);
	}

	void GraphicsEngine::DrawTriangles(const TriangleType& type, ui32 vertexCount, ui32 offset)
	{
		int glTriangleType = GL_TRIANGLES;

		switch (type)
		{
		case TriangleType::TriangleList:
		{
			glTriangleType = GL_TRIANGLES;
			break;
		}
		case TriangleType::TriangleStrip:
		{
			glTriangleType = GL_TRIANGLE_STRIP;
			break;
		}
		default:
			break;
		}

		glDrawArrays(glTriangleType, offset, vertexCount);
	}

	void GraphicsEngine::DrawIndexedTriangles(const TriangleType& type, ui32 indicesCount)
	{
		int glTriangleType = GL_TRIANGLES;

		switch (type)
		{
		case TriangleType::TriangleList:
		{
			glTriangleType = GL_TRIANGLES;
			break;
		}
		case TriangleType::TriangleStrip:
		{
			glTriangleType = GL_TRIANGLE_STRIP;
			break;
		}
		default:
			break;
		}

		glDrawElements(glTriangleType, indicesCount, GL_UNSIGNED_INT, nullptr);
	}

	void GraphicsEngine::SetViewport(const Rect& size)
	{
		glViewport(size.Left, size.Top, size.Width, size.Height);
	}

	void GraphicsEngine::SetVertexArrayObject(const VertexArrayObjectPtr& vao)
	{
		glBindVertexArray(vao->GetId());
	}

	void GraphicsEngine::SetUniformBuffer(const UniformBufferPtr& buffer, ui32 slot)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, slot, buffer->GetId());
	}

	void GraphicsEngine::SetShaderProgram(const ShaderProgramPtr& program)
	{
		glUseProgram(program->GetId());
	}

	VertexArrayObjectPtr GraphicsEngine::CreateVertexArrayObject(const VertexBufferDesc& data)
	{
		return std::make_shared<VertexArrayObject>(data);
	}

	VertexArrayObjectPtr GraphicsEngine::CreateVertexArrayObject(const VertexBufferDesc& vbDesc, const IndexBufferDesc& ibDesc)
	{
		return std::make_shared<VertexArrayObject>(vbDesc, ibDesc);
	}

	UniformBufferPtr GraphicsEngine::CreateUniformBuffer(const UniformBufferDesc& desc)
	{
		return std::make_shared<UniformBuffer>(desc);
	}

	ShaderProgramPtr GraphicsEngine::CreateShaderProgram(const ShaderProgramDesc& desc)
	{
		return std::make_shared<ShaderProgram>(desc);
	}
}