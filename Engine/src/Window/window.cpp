#include "window.h"

#include "glad/glad_wgl.h"
#include <glad/glad.h>

#include <Windows.h>
#include <assert.h>

namespace Engine
{
	LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_DESTROY:
		{
			WindowsWindow* window = (WindowsWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			break;
		}
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
		}

		return NULL;
	}


	WindowsWindow::WindowsWindow()
	{
		WNDCLASSEX wc = { };

		const wchar_t *className = L"3DGameWindow";
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.lpszClassName = className;
		wc.lpfnWndProc = &WndProc;
		wc.style = CS_OWNDC;

		auto classId = RegisterClassEx(&wc);
		assert(classId);

		long wProps = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
		RECT rect = { 0, 0, m_width, m_height };
		AdjustWindowRect(&rect, wProps, false);

		m_handle = CreateWindowEx(NULL, MAKEINTATOM(classId), L"3D OpenGL Game", wProps,
			CW_USEDEFAULT, CW_USEDEFAULT, m_width, m_height, NULL, NULL, NULL, NULL);

		assert(m_handle);

		SetWindowLongPtr((HWND)m_handle, GWLP_USERDATA, (LONG_PTR)this);

		ShowWindow((HWND)m_handle, SW_SHOW);
		UpdateWindow((HWND)m_handle);


		HDC deviceContext = GetDC(HWND(m_handle));
		int pixelFormatAttributes[] = {
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_COLOR_BITS_ARB, 32,
			WGL_DEPTH_BITS_ARB, 24,
			WGL_STENCIL_BITS_ARB, 8,
			0
		};
		int pixelFormat = 0;
		UINT numFormats = 0;

		wglChoosePixelFormatARB(deviceContext, pixelFormatAttributes, nullptr, 1, &pixelFormat, &numFormats);
		assert(numFormats);

		PIXELFORMATDESCRIPTOR pixelDescriptor = {};

		DescribePixelFormat(deviceContext, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pixelDescriptor);
		SetPixelFormat(deviceContext, pixelFormat, &pixelDescriptor);

		int openGLAttributes[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
			WGL_CONTEXT_MINOR_VERSION_ARB, 6,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};

		m_context = wglCreateContextAttribsARB(deviceContext, 0, openGLAttributes);
		assert(m_context);
	}

	WindowsWindow::~WindowsWindow()
	{
		wglDeleteContext(HGLRC(m_context));
		DestroyWindow((HWND)m_handle);
	}

	void WindowsWindow::MakeCurrentContext()
	{
		wglMakeCurrent(GetDC(HWND(m_handle)), HGLRC(m_context));
	}
	void WindowsWindow::Present(bool vsync)
	{
		wglSwapIntervalEXT(vsync);
		wglSwapLayerBuffers(GetDC(HWND(m_handle)), WGL_SWAP_MAIN_PLANE);
	}

	Rect WindowsWindow::GetInnerSize()
	{
		RECT rect = {};
		GetClientRect((HWND)m_handle, &rect);

		return Rect(rect.right-rect.left, rect.bottom-rect.top);
	}
}
