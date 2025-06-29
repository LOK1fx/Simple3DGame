#pragma once

#include "Math/rect.h"
#include "prerequisites.h"

namespace Engine
{
	class WindowsWindow
	{
	public:
		WindowsWindow();
		~WindowsWindow();

		void MakeCurrentContext();
		void Present(bool vsync);

		Rect GetInnerSize() const
		{
			return Rect(m_width, m_height);
		}
	private:
		ui32 m_width = 1024;
		ui32 m_height = 768;

		void* m_handle = nullptr;
		void* m_context = nullptr;
	};
}

