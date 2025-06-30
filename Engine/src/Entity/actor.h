#pragma once

#include "entity.h"

namespace Engine
{
	class Actor : public Entity
	{
	public:
		Actor() = default;
		virtual ~Actor() = default;


	protected:
		virtual void OnCreate() = 0;
		virtual void OnUpdate(float deltaTime) = 0;
	};

}