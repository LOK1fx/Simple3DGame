#pragma once

#include "vector3.h"

namespace Engine
{
	class Transform
	{
	public:
		inline Transform()
			: m_translation(Vec3(0, 0, 0))
			, m_eulerAngles(Vec3(0, 0, 0))
			, m_scale(1.0f, 1.0f, 1.0f)
		{}

		inline Transform(const Vec3& translation, const Vec3& eulerAngles, const Vec3& scale)
		{
			m_translation = translation;
			m_eulerAngles = eulerAngles;
			m_scale = scale;
		}

		inline void SetTranslation(const Vec3& translation)
		{
			m_translation = translation;
		}

		inline void SetEulerAngles(const Vec3& eulerAngles)
		{
			m_eulerAngles = eulerAngles;
		}

		inline void SetScale(const Vec3& scale)
		{
			m_scale = scale;
		}

		Vec3 GetPosition() const { return m_translation; }
		Vec3 GetEulerAngles() const { return m_eulerAngles; }
		Vec3 GetScale() const { return m_scale; }

	private:
		Vec3 m_translation;
		Vec3 m_eulerAngles;
		Vec3 m_scale;
	};

	typedef std::shared_ptr<Transform> TransformPtr;
}