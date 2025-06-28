#pragma once

#include "prerequisites.h"

namespace Engine
{
	class Rect
	{
	public:
		Rect() { }
		Rect(i32 width, i32 height) : Width(width), Height(height) { }
		Rect(i32 left, i32 top, i32 width, i32 height)
		{
			Left = left;
			Top = top;
			Width = width;
			Height = height;
		}
		Rect(const Rect& rect)
		{
			Left = rect.Left;
			Top = rect.Top;
			Width = rect.Width;
			Height = rect.Height;
		}

		int Width = 0;
		int Height = 0;
		int Left = 0;
		int Top = 0;
	};
}