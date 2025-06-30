#pragma once

#include "prerequisites.h"

namespace Engine
{
	class EntitySystem;

	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		void Release();

		EntitySystem* GetEntitySystem() const { return m_entitySystem; }

	protected:
		virtual void OnCreate() { }
		virtual void OnUpdate(f32 deltaTime) { }

		size_t m_id = 0;
		EntitySystem* m_entitySystem = nullptr;

		friend class EntitySystem;
	};

}
