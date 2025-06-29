#pragma once

#include "prerequisites.h"
#include "vector3.h"
#include "vector4.h"

namespace Engine
{
	class Matrix44
	{
	public:
		Matrix44()
		{
			SetIdentity();
		}

		void SetIdentity()
		{
			::memset(Matrix, 0, sizeof(f32) * 16);
			
			Matrix[0][0] = 1;
			Matrix[1][1] = 1;
			Matrix[2][2] = 1;
			Matrix[3][3] = 1;
		}

		void SetScale(const Vec3& scale)
		{
			Matrix[0][0] = scale.X;
			Matrix[1][1] = scale.Y;
			Matrix[2][2] = scale.Z;
		}

		void SetTranslation(const Vec3& translation)
		{
			Matrix[3][0] = translation.X;
			Matrix[3][1] = translation.Y;
			Matrix[3][2] = translation.Z;
		}


		void SetRotationX(f32 x)
		{
			Matrix[1][1] = cos(x);
			Matrix[1][2] = sin(x);
			Matrix[2][1] = -sin(x);
			Matrix[2][2] = cos(x);
		}

		void SetRotationY(f32 y)
		{
			Matrix[0][0] = cos(y);
			Matrix[0][2] = -sin(y);
			Matrix[2][0] = sin(y);
			Matrix[2][2] = cos(y);
		}

		void SetRotationZ(f32 z)
		{
			Matrix[0][0] = cos(z);
			Matrix[0][1] = sin(z);
			Matrix[1][0] = -sin(z);
			Matrix[1][1] = cos(z);
		}


		void operator *=(const Matrix44& matrix)
		{
			Matrix44 out;

			for (uc16 i = 0; i < 4; i++)
			{
				for (uc16 j = 0; j < 4; j++)
				{
					out.Matrix[i][j] =
						Matrix[i][0] * matrix.Matrix[0][j] +
						Matrix[i][1] * matrix.Matrix[1][j] +
						Matrix[i][2] * matrix.Matrix[2][j] +
						Matrix[i][3] * matrix.Matrix[3][j];
				}
			}

			*this = out;
		}

		void SetOrthoLH(f32 width, f32 height, f32 nearPlane, f32 farPlane)
		{
			Matrix[0][0] = 2.0f / width;
			Matrix[1][1] = 2.0f / height;
			Matrix[2][2] = 1.0f / (farPlane - nearPlane);
			Matrix[3][2] = -(nearPlane / (farPlane - nearPlane));
		}

		f32 Matrix[4][4] = {};
	};
}
