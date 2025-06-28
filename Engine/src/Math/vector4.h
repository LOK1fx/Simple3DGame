#pragma once

#include "prerequisites.h"

namespace Engine
{
	class Vec4
	{
	public:
		Vec4()
		{

		}
		Vec4(f32 x, f32 y, f32 z, f32 w)
		{
			X = x;
			Y = y;
			Z = z;
			W = w;
		}

		~Vec4()
		{

		}

		f32 X = 0;
		f32 Y = 0;
		f32 Z = 0;
		f32 W = 0;
	};

}
