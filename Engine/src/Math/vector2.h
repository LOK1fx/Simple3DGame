#pragma once

#include "prerequisites.h"

namespace Engine
{
	class Vec2
	{
	public:
		Vec2()
		{

		}
		Vec2(f32 x, f32 y)
		{
			X = x;
			Y = y;
		}

		f32 X = 0;
		f32 Y = 0;
	};

}
