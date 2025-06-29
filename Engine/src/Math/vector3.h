#pragma once

#pragma once

#include "prerequisites.h"

namespace Engine
{
	class Vec3
	{
	public:
		Vec3()
		{

		}
		Vec3(f32 x, f32 y, f32 z)
		{
			X = x;
			Y = y;
			Z = z;
		}

		f32 X = 0;
		f32 Y = 0;
		f32 Z = 0;
	};

}
