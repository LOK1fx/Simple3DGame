#include "GraphicsEngine.h"

#include <glad/glad_wgl.h>
#include <glad/glad.h>
#include <assert.h>
#include <stdexcept>

#include "Graphics/vertexarrayobject.h"
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
			throw std::runtime_error("failed gladLoadWGL");

		if (!gladLoadGL())
			throw std::runtime_error("failed gladLoadGL");

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

	void GraphicsEngine::DrawTriangles(ui32 vertexCount, ui32 offset)
	{
		glDrawArrays(GL_TRIANGLES, offset, vertexCount);
	}

	void GraphicsEngine::SetViewport(const Rect& size)
	{
		glViewport(size.Left, size.Top, size.Width, size.Height);
	}

	void GraphicsEngine::SetVertexArrayObject(const VertexArrayObjectPtr& vao)
	{
		glBindVertexArray(vao->GetId());
	}

	void GraphicsEngine::SetShaderProgram(const ShaderProgramPtr& program)
	{
		glUseProgram(program->GetId());
	}

	VertexArrayObjectPtr GraphicsEngine::CreateVertexArrayObject(const VertexBufferDesc& data)
	{
		return std::make_shared<VertexArrayObject>(data);
	}

	ShaderProgramPtr GraphicsEngine::CreateShaderProgram(const ShaderProgramDesc& desc)
	{
		return std::make_shared<ShaderProgram>(desc);
	}
}