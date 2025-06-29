#pragma once

#include "prerequisites.h"
#include <map>
#include <set>

namespace Engine
{
	class Entity;

	class EntitySystem
	{
	public:
		EntitySystem();
		~EntitySystem();


		template <typename T>
		T* CreateEntity()
		{
			static_assert(std::is_base_of<Entity, T>::value, "Must derive from Entity class.");
			auto id = typeid(T).hash_code();
			auto e = new T();

			if (CreateEntityInternal(e, id))
				return e;

			return nullptr;
		}
	private:
		bool CreateEntityInternal(Entity* entity, size_t id);
		void RemoveEntity(Entity* entity);

		void Update(f32 deltaTime);

		std::map < size_t, std::map<Entity*, std::unique_ptr<Entity>>> m_entities;
		std::set<Entity*> m_entitiesToDestroy;

		friend class Entity;
		friend class Game;
	};

}
